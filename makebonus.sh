#!/bin/bash
for FILE in $1/*
do
    bname=$(basename "$FILE")
    extension="${bname##*.}"
    filenamewoext="${bname%.*}"
    newfilename="${filenamewoext}_bonus.${extension}"
    cp ${FILE} $2/${newfilename}
done
