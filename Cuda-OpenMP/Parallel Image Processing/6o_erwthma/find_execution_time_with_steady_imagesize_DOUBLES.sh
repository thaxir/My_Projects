#!/bin/bash


for i in 1 2 3 4 5 6 7 8 9 10 12 16 20 32 50 64 128 256 512 1024
do	
	./6o_erwthma_steady_imagesize  << EOF
$i
EOF
done
