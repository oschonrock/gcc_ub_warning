# -Wstringop-overflow warning in fmtlib with LTO under gcc 16.1

This is suspected to be a **false positive**. 

Has been reported to gcc as: https://gcc.gnu.org/bugzilla/show_bug.cgi?id=125187

To reproduce, clone this repo and:

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release && cmake --build build -v
```

This results in the following warning at link time 
```
...
[100%] Linking CXX executable ub
/usr/bin/cmake -E cmake_link_script CMakeFiles/ub.dir/link.txt --verbose=1
/usr/bin/c++ -O3 -DNDEBUG -flto=auto -fno-fat-lto-objects -Wl,--dependency-file=CMakeFiles/ub.dir/link.d CMakeFiles/ub.dir/ub.cpp.o -o ub  _deps/fmt-build/libfmt.a
In function ‘write2digits’,
    inlined from ‘write_significand’ at /home/oliver/Projects/ub/build/_deps/fmt-src/include/fmt/format.h:2415:17,
    inlined from ‘write_significand’ at /home/oliver/Projects/ub/build/_deps/fmt-src/include/fmt/format.h:2407:13,
    inlined from ‘write_significand’ at /home/oliver/Projects/ub/build/_deps/fmt-src/include/fmt/format.h:2434:31,
    inlined from ‘write_significand’ at /home/oliver/Projects/ub/build/_deps/fmt-src/include/fmt/format.h:2461:20,
    inlined from ‘operator()’ at /home/oliver/Projects/ub/build/_deps/fmt-src/include/fmt/format.h:2539:33,
    inlined from ‘write_padded’ at /home/oliver/Projects/ub/build/_deps/fmt-src/include/fmt/format.h:1701:9,
    inlined from ‘write_padded’ at /home/oliver/Projects/ub/build/_deps/fmt-src/include/fmt/format.h:1710:43,
    inlined from ‘write_fixed’ at /home/oliver/Projects/ub/build/_deps/fmt-src/include/fmt/format.h:2536:44:
/home/oliver/Projects/ub/build/_deps/fmt-src/include/fmt/format.h:1209:11: warning: writing 2 bytes into a region of size 0 -Wstringop-overflow=]
 1209 |     memcpy(out, digits2(value), 2);
      |           ^
/home/oliver/Projects/ub/build/_deps/fmt-src/include/fmt/format.h: In function ‘write_fixed’:
/home/oliver/Projects/ub/build/_deps/fmt-src/include/fmt/format.h:2433:8: note: at offset [-11, -1] into destination object buffer’ of size 11
 2433 |   Char buffer[digits10<UInt>() + 2];
      |        ^

...
```

Note that `-flto=auto` and `-DCMAKE_BUILD_TYPE=Release` are required to reproduce. 

