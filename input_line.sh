 head -n $(grep -n 'ss' oi |cut -d ":" -f1) oi |cat - <(echo 123896123) <(tail -n $(($(wc -l oi | awk '{print $1}') - $(grep -n 'ss' oi |cut -d : -f1))) oi) > _ && mv _ oi
XIXI
123896123
123896123
123896123
123896123
123896123
123896123
123896123
123896123
123896123
