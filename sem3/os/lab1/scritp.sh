#!/bin/bash

mins=$1
maxs=$2
way=$3

for f in $way/*; do
	filen=$(basename $f)
	sizef=$(stat -c %s $f)
	if [ $sizef>$mins ]; then
		echo $file
	fi
done


