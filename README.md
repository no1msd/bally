# bally

bally is a simple ray tracer written in C++. It's nothing more than a fun hobby 
project, so don't expect anything fancy. It's slow and inefficient, but it does 
support texture mapping, soft shadows and depth of field, which is nice. It's 
hardcoded to render the image below:

![image](http://i.imgur.com/tBlABcK.png)

With default settings, it takes about a minute to render on a Core i5-4200M.

It's using [LodePNG](http://lodev.org/lodepng/), included in the repo to write 
the resulting image to ```bally.png``` in the current directory. It will 
overwrite any previous files with the same name.

## Building

A compiler supporting C++11, and CMake 2.8+ is required for building:

```bash
 $ mkdir build
 $ cd build
 $ cmake ..
 $ make
```
