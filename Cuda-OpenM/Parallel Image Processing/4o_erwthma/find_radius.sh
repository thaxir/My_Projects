#!/bin/bash


for i in `seq 1 32`;
do
	./5o_erwthma_modified_for_script_use << EOF
$i
EOF
	done