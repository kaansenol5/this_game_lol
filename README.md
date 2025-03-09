note from 2025: i dont remember what this was. made it public.

# Dependencies

SDL2

SDL2_image

SDL2_ttf

EnTT (in include/)

Json For Modern C++ (in include/)

Compiler that supports C++17 or above (i use clang)


# Compiling

Run

~~~
cmake . -DCMAKE_C_COMPILER=clang DCMAKE_CXX_COMPILER=clang++
make
~~~

You don't *have* to use clang, but other compilers are not tested.
q
