#!/bin/bash


for i in 2 4 8 16 32 64 128 256 512 1024 2048 4096 8192
do	
	./6o_erwthma_steady_filter << EOF
$i
EOF
done
