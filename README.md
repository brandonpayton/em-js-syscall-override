# Testing async syscall overrides with Emscripten

This is a simple project to try to reproduce the following error when overriding the fcntl() system call with an async JS version in Emscripten.

```
Error: null function or function signature mismatch
```