# Task 1: Graphic application

This simple application just draws moving all over the screen circles.

## Build

```console
$ meson build
$ meson compile -C build
```
 
# Task 2: Implement trace loging pass

Pass that allows to obtain instruction trace during application execution.
You can analys the obtained trace with `parser.py` script.

## Build

Build a graphic application and a libPass.so first:
```console
$ CC=clang CXX=clang++ meson build
$ CC=clang CXX=clang++ meson compile -C build
```

Build your application with `-fpass-plugin=` flag:
```console
$ clang -fpass-plugin=build/passes/libPass.so src/app.c -Iinclude -I/usr/include/SDL2 -lSDL2 -O2 -c -o app.o
$ clang src/log.c src/sim.c src/main.c app.o -Iinclude -I/usr/include/SDL2 -lSDL2 -O2 -o app
```
Now you can run `./app` to get a desired trace.

## Get statistic

You can pass a file conatining the trace to a `parser.py` script to get instruction statistic:

```console
$ python3 parser.py trace.txt 3
```

## Results

I've got the following charts:

Window size = 1                                                                     |  Window size = 3                                                                     |  Window size = 5
:----------------------------------------------------------------------------------:|:------------------------------------------------------------------------------------:|:----------------------------------------------------------------------------------:
![](https://github.com/realFrogboy/llvm-cource/blob/master/1/samples/window_1.png)  |  ![](https://github.com/realFrogboy/llvm-cource/blob/master/1/samples/window_3.png)  |  ![](https://github.com/realFrogboy/llvm-cource/blob/master/1/samples/window_5.png)

# Task 3: Implement IR Generator

## Build

```console
$ CC=clang CXX=clang++ meson build
$ CC=clang CXX=clang++ meson compile -C build
```

```console
$ ./build/src/ir_creator
```

