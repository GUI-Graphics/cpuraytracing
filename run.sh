#! /bin/bash
make
if [[ $? == 0 ]]; then
	time ./a.out
	display image.ppm
fi
