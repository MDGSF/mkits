# mkits

A collections of C language module, from go, nginx, redis, etc. With many
comments and unit test.

## architecture

- mckits
  - mlibc: libc wrapper
  - mstl: only use libc
    - hash
    - hashmap
    - heap
    - list
    - nlist
    - rbtree
    - ring
    - skiplist
    - array
    - string
    - vector
  - platform
    - os
    - file
    - thread
  - core
    - log
    - encoding
    - abstract data structure
    - color
    - math
    - meta
    - time
  - web server
  - tools
  - other module

## build

```sh
./build_clang.sh
./build_gcc.sh
./build_gcc_release.sh
```

## code of conduct

- pre-commit: <https://github.com/pre-commit/pre-commit>
