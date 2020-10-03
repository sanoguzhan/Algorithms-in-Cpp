#! /bin/bash
if [[ -z $ENVIRONMENT ]]; then
    echo "ROOT is not define"
    exit 1
fi

dir=$(echo "$@" | tr a-z A-Z)
name=$(echo "$@" | tr a-z A-Z)

mkdir -p $ENVIRONMENT/
