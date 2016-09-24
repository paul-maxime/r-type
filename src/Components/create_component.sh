#!/usr/bin/env bash

set -e
usage="usage: $0 name

	This will create the directory and its two files cpp and hpp."

if [ ! ${1+x} ];then
    echo "$usage"
    exit
fi

mkdir $1 && cp TemplateComponent.cpp TemplateComponent.hpp $1 && mv $1/TemplateComponent.cpp $1/$1Component.cpp && mv $1/TemplateComponent.hpp $1/$1Component.hpp \
    || exit

OLD="Template"
NEW=$1
OLDHEADER="TEMPLATE"
NEWHEADER="${1^^}"
DPATH="$1/*"
TFILE="/tmp/out.tmp.$$"
for f in $DPATH
do
    if [ -f $f -a -r $f ]; then
	sed "s/$OLD/$NEW/g" "$f" > $TFILE && mv $TFILE "$f"
	sed "s/$OLDHEADER/$NEWHEADER/g" "$f" > $TFILE && mv $TFILE "$f"
    else
	echo "Error: Cannot read $f"
    fi
done
/bin/rm -f $TFILE
