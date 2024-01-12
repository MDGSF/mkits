# mkits

A collections of C language module, from go, nginx, redis, etc. With many
comments and unit test.

## architecture

- mckits
  - mstl: only use libc
    - array
    - string
    - hashmap
    - rbtree
    - heap
    - list
    - skiplist
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
    - hash
    - time
  - web server
  - tools
  - other module

## build

```sh
cmake -S . -B build; cmake --build build
```

or

```sh
mkdir build
cd build
cmake ..
make
```

## code of conduct

- pre-commit: <https://github.com/pre-commit/pre-commit>
