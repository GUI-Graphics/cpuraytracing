#! /bin/bash
make
if [[ $? == 0 ]]; then
	echo "---start rendering---"
	time ./a.out
	display image.ppm
fi
