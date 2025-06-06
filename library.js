const LibraryForFileLocking = {
	// Place the builtin fcntl64 implementation in an object so it is left
	// intact even if the function is not referenced by C/C++ code.
	// Ref: https://emscripten.org/docs/porting/connecting_cpp_and_javascript/Interacting-with-code.html#javascript-limits-in-library-files
	// TODO: Would "builtin" be better than "default"?
	$default_fcntl64__deps: LibraryManager.library.__syscall_fcntl64__deps,
	$default_fcntl64: {
		fn: LibraryManager.library.__syscall_fcntl64,
	},

	__syscall_fcntl64__deps: [
		...LibraryManager.library.__syscall_fcntl64__deps,
		'$default_fcntl64',
	],
	__syscall_fcntl64__sig: LibraryManager.library.__syscall_fcntl64__sig,
	__syscall_fcntl64: async function __syscall_fcntl64(fd, cmd, varargs) {
		return Asyncify.handleAsync(async () => {
			return Promise.resolve(
				default_fcntl64.fn(fd, cmd, varargs)
			);
		});
	},
};

autoAddDeps(LibraryForFileLocking, '$default_fcntl64');
autoAddDeps(LibraryForFileLocking, '__syscall_fcntl64');
mergeInto(LibraryManager.library, LibraryForFileLocking);
