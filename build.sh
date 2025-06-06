#!/bin/bash

~/src/emsdk/emsdk activate latest
source ~/src/emsdk/emsdk_env.sh

export ASYNCIFY_IMPORTS=$'["__syscall_fcntl64"]'

emcc main.c \
	-o test.js \
	-s ASYNCIFY=1 \
	-s ASYNCIFY_IMPORTS="$ASYNCIFY_IMPORTS" \
	--js-library library.js


