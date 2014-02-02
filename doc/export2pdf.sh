#!/bin/bash

echo "Compiling Markdown documents to PDF..."
if ! [ -z "`which pandoc 2>> /dev/null`" ]; then
	for f in `ls *.md 2>> /dev/null`; do
		echo -n " * $f ... "
		pandoc $f -o `basename $f .md`.pdf >> /dev/null 2>&1
		if [ $? -eq 0 ]; then
			echo "[DONE]"
		else
			echo "[FAIL]"
		fi
	done;
else
	echo "pandoc is not installed"
fi;
