#!/bin/bash
find . agmgen
### $? = 0 encontrou arquivo
if [[ $? > 0 ]]; then
    echo "Making executable"
    make agmgen2
fi
parentdir="$(dirname "$(pwd)")"
echo "$parentdir"
cp examples/agmgen2/agmgen $parentdir


##### DO THE SAME FOR BIGCLAM  


find . bigclam
### $? = 0 encontrou arquivo
if [[ $? > 0 ]]; then
    echo "Making executable"
    make bigclam
fi
parentdir="$(dirname "$(pwd)")"
echo "$parentdir"
cp examples/bigclam/bigclam $parentdir