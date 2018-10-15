#!/bin/bash

# This script manages remote dependencies
# ONLY SUPPORTS HEADER FILES

for par in "$@"; do
	dep=($par)

	name="include/${dep[0]}"
	target=("${dep[@]:1}")

	if [ ! -d $name ]; then
        echo "=> Dependency not found!"
		mkdir $name
		cd $name

		for url in "${target[@]}"; do
            echo "==> Downloading $(basename $url)..."
			curl -O -L $url
            echo
		done

        echo "=> Finished downloading '${dep[0]}'!"
        echo
		cd ../..
	fi
done
