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