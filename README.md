libmozjemalloc 57.0
===================

This is the `mozjemalloc` allocator that Firefox uses by default
(unless the `--disable-jemalloc` flag is specified in a Mozconfig).
All source files are unmodified from the Firefox 57.0 source tarball.

It is built as a linux shared library, usable as a replacement allocator by:

```sh
$ LD_PRELOAD=libmozjemalloc.so $CMD
```

Build and install it the usual way:

```sh
$ ./configure --optimize
$ make
$ sudo make install
```
