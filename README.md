# RayTracer
A simple ray tracer written in C++, Licensed under [Apache 2.0](https://www.apache.org/licenses/LICENSE-2.0 "Apache License") (see LICENSE file)

#### Description
Generates an image of consisting of spheres and planes, with planned support for triangle meshes (limited .obj files)

#### Build instructions
This project includes a makefile with targets all and clean. If you know how to use a makefile, stop reading this section.

If you don't know how to use a makefile, you need to open a terminal (don't do this for the first time on windows) and change directory to the directory of this project (containing the makefile) using the `cd` command. Then type `make all` this will start compiling the project. Wait until it has finished compiling (when it finishes, the terminal prints a line start marker such as `>>>` or `[computer name]:[working directory] [user name] $`) run the program by typing `./Raytracer.o`.

#### Miscellaneous
Uses C++11 features, such as std::vector, so a C++11 compatible compiler is required. Incorporates the C++ Eigen Library, licensed under [MPL2.0](https://www.mozilla.org/en-US/MPL/2.0/ "Mozilla Public License")
