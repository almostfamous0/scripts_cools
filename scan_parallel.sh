#!/bin/bash

HOST="192.168.0.1"  # Substitua pelo IP ou hostname desejado

seq 1 10000 | parallel -j12 "timeout 1 bash -c 'echo > /dev/tcp/$HOST/{}' 2>/dev/null && echo Porta {} está aberta"
