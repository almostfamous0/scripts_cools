#!/usr/bin/env bash
max_jobs=4
pids=()

process_pdf() {
  f="$1"
  [ -f "$f" ] || return 0
  size=$(wc -c < "$f")
  [ "$size" -le $((20*1024*1024)) ] && return 0

  dir=$(dirname -- "$f")
  base=$(basename -- "$f" .pdf)

  if command -v qpdf >/dev/null 2>&1; then
    qpdf --linearize "$f" "$dir/normalized_$base.pdf" && src="$dir/normalized_$base.pdf"
  else
    src="$f"
  fi

  gs -sDEVICE=pdfwrite -dCompatibilityLevel=1.4 \
     -dPDFSETTINGS=/ebook \
     -dDetectDuplicateImages=true \
     -dDownsampleColorImages=true -dColorImageResolution=150 \
     -dDownsampleGrayImages=true  -dGrayImageResolution=150 \
     -dDownsampleMonoImages=true  -dMonoImageResolution=300 \
     -dSAFER -dNOPAUSE -dQUIET -dBATCH \
     -sOutputFile="$dir/tmp_$base.pdf" "$src" || return 0

  if [ $(wc -c < "$dir/tmp_$base.pdf") -gt $((12*1024*1024)) ]; then
    gs -sDEVICE=pdfwrite -dCompatibilityLevel=1.4 \
       -dPDFSETTINGS=/screen \
       -dDetectDuplicateImages=true \
       -dDownsampleColorImages=true -dColorImageResolution=96 \
       -dDownsampleGrayImages=true  -dGrayImageResolution=96 \
       -dDownsampleMonoImages=true  -dMonoImageResolution=300 \
       -dSAFER -dNOPAUSE -dQUIET -dBATCH \
       -sOutputFile="$dir/tmp2_$base.pdf" "$dir/tmp_$base.pdf" && \
    mv -f "$dir/tmp2_$base.pdf" "$f" && rm -f "$dir/tmp_$base.pdf"
  else
    mv -f "$dir/tmp_$base.pdf" "$f"
  fi

  [ -f "$dir/normalized_$base.pdf" ] && rm -f "$dir/normalized_$base.pdf"
}

export -f process_pdf

while IFS= read -r -d '' f; do
  process_pdf "$f" &
  pids+=($!)

  # limita concorrência
  while [ "${#pids[@]}" -ge "$max_jobs" ]; do
    wait -n
    # remove pids finalizados
    alive=()
    for pid in "${pids[@]}"; do
      kill -0 "$pid" 2>/dev/null && alive+=("$pid")
    done
    pids=("${alive[@]}")
  done
done < <(find . -type f -name "*.pdf" -print0)

wait
