# Snake game in C++ using SFML library

This is a simple version of the popular game 'snake' that I 
made to learn how to use classes and the SFML graphics library in C++

It is currently only compiled for Ubuntu but I hope to be able to 
compile it for windows as well.

---

# How to use the sfml++ 'compiler'
When you compile C++ code files that use any of the headers from the
SFML library, you must always include various options, so to make it
a bit simpler to write, I made my own program that uses the g++ compiler
and some arguments that can be passed to it in order to make compilation commands simpler to write

It can be used as follows:

`./sfml++ -n <filename.cc> -o <execname> -<sfml_options>`

> The -<sfml_options> tag can be one or more of the following:
> SFML system header (-lsfml-system): `-sys`
> SFML window header (-lsfml-window): `-win`
> SFML graphics header (-lsfml-graphics): `-gra`
> SFML network header (-lsfml-network): `-net`
> SFML audio header (-lsfml-audio): `-aud`
> OpenGL library (-lGL): `-opengl`
