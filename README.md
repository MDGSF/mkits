# mkits

A collections of C language module, from go, nginx, redis, etc. With many
comments and unit test.

## architecture

- mckits
  - mlibc: libc wrapper, only use libc, don't call system api in mstl.
  - mstl: only use libc, don't call system api in mstl.
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
  - core
    - log
    - encoding
    - abstract data structure
    - color
    - math
    - meta
    - time
    - os
    - file
    - thread
  - web server
  - tools
  - other module

## build

```sh
sudo apt install gcc g++ cmake lcov

./build_clang.sh
./build_gcc.sh
./build_gcc_release.sh
./build_coverage.sh
```

## code of conduct

### pre-commit

- pre-commit: <https://github.com/pre-commit/pre-commit>

```sh
pip install -i https://pypi.tuna.tsinghua.edu.cn/simple pre-commit
pre-commit install
pre-commit run --all-files
```

### cpplint

```sh
pip install -i https://pypi.tuna.tsinghua.edu.cn/simple cpplint
```

### cppcheck

```sh
sudo apt-get install cppcheck
```

### clang-tidy

```sh
pip install -i https://pypi.tuna.tsinghua.edu.cn/simple clang-tidy
```
