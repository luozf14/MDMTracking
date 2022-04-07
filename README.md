# MDMTracking
An example shows how to do MDM tracking.

## Features
The example `TrackingExample.C` shows you how to define a MDMTraceFit, input the real run PPAC data (X1, Y1, X2, Y2) to MDMTraceFit, set up minimizer, and get the minimization results.  
By understanding this example, you will be able to create tracking code for your own PPAC data analysis. You should also understand the `CMakeList.txt`.


## How to compile

### Prerequisites

- CMake >= 3.5
- ROOT >= 6.16
- g++, gfortran

### Compiling

Make a build directory and enter it.
```
$ mkdir build && cd build
```

cmake 
```
$ cmake ../
```
make
```
$ make
```
Now you will have one executable file `MDMTracking` and `rayin.dat` in `build/`.  
Please be aware that `rayin.dat` is required input file for MDMTrace. Its location is hard-coded at line 99 in `src/RAYTKIN1.F`. By default, it is the same directory in which the executable file locates. For convenience, I add some commands in `CMakeList.txt` so that the `rayin.dat` will be automatically copied from `dat/` to `build/`.

## How to use
For this example, simply execute
```
$ ./MDMTracking
```
For your real run data analysis, you should read `TrackingExample.C` and `CMakeList.txt` and fully understand them. Then you will be able to write code for your case. 

