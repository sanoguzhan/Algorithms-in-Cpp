#!/bin/bash

model_1="knn"
model_2="kmeans"

echo -n "Enter model name (knn or kmeans) [ENTER]: "
read NAME

if [[ -z $ENVIRONMENT ]]; then
    export ENVIRONMENT=$PWD
    export IMPORT_ROOT=$PWD/import

    if [[ $model_1 == $NAME ]]; then
        echo "Running KNN alogithm "
        cd import && make clean; make
        cd ../algorithms/KNN && make clean; make
        ./knn
    fi
    if [[ $model_2 == $NAME ]]; then
        echo "Running KMEANS alogithm "
        cd import && make clean; make
        cd ../algorithms/KMEANS && make clean; make
        ./kmeans
    fi
    
fi

