#!/bin/bash
clear
echo "The experiment starts now "

echo "Check if any user uses the server first"

w
echo "Type yes if you are ready to start the experiments"
read answer
S='yes'
if [ $answer=$S ];
then
	echo 'starting experiment ... '
	make all
fi



sleep 3
for i in `seq 1 17`;
	do
	echo "what code should i run 12 times??"
	read code
	echo   >> apotelesmata2.txt
	echo "$code" >> apotelesmata2.txt
	for i in `seq 1 12`;
        do
	./$code >> apotelesmata2.txt
	done
done

