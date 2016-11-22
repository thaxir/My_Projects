#!/bin/bash
COUNTER=32

while [ $COUNTER -le 4096 ]
do
	COUNTER=$(( $COUNTER + $COUNTER ))
	./7o_erwthma << EOF
	$COUNTER
EOF
done
