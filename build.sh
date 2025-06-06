#!/bin/bash

~/src/emsdk/emsdk activate latest
source ~/src/emsdk/emsdk_env.sh

export ASYNCIFY_IMPORTS=$'["__syscall_fcntl64"]'

emcc main.c \
	-o test.js \
	-s ASYNCIFY=1 \
	-s ASYNCIFY_IMPORTS="$ASYNCIFY_IMPORTS" \
	-s ASYNCIFY_IGNORE_INDIRECT=1 \
	-O0 \
	-g3 \
	--js-library library.js \
	-D__x86_64__ \
	-lproxyfs.js \
	-lnodefs.js \
	-s WASM_BIGINT=1 \
	-s MIN_NODE_VERSION=200900 \
	-s INITIAL_MEMORY=1024MB \
	-s ALLOW_MEMORY_GROWTH=1 \
	-s ASSERTIONS=0 \
	-s ERROR_ON_UNDEFINED_SYMBOLS=1 \
	-s NODEJS_CATCH_EXIT=0 \
	-s NODEJS_CATCH_REJECTION=0 \
	-s EXIT_RUNTIME=1 \
	-Wl,--wrap=select \
	-s FORCE_FILESYSTEM=1 \
	-s ENVIRONMENT=node \
	# 	/root/lib/libphp.a \
	# 	/root/proc_open.c \
	# 	/root/php_wasm.c \
	# 	$(cat /root/.emcc-php-wasm-sources) \
	#-s INVOKE_RUN=0 \


