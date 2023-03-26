# Fence Insertion for LLVM

A modification of the LLVM compiler infrastructure for automatically inserting fences in weak memory model concurrent programs.

## Building and Running Instructions
First clone this repository, you can set the `--depth` to `1` to get only the most recent version. 

Then you need to compile the project. The first thing to do is make a `build` directory inside the repository. 
Then go inside `build` and run 
```bash 
$ cmake ../ -DCMAKE_BUILD_TYPE=Release -DLLVM_USE_LINKER=lld -DLLVM_PARALLEL_LINK_JOBS=1
```
The above command will generate the build files. **Note** that it assumes you have `lld` installed, if not you can remove that argument (at the cost of slower linking) or use your favorite linker. Additionally note that in the above command we set the threshold for parallel linking jobs to 1 (so no parallelism). This is because typically linking takes a lot of memory. Feel free to change the value based on how much memory your system have. 

Now that we have the build files it is time to compile. The first time of compiling LLVM will take a lot of time so be prepared to wait for a few hours. Still inside `build` do:
```bash
$ cmake --build .
```

Once the process has completed go back to the main directory of the repository. Now we can test that our pass works. Run:
```bash
$ ./build/bin/opt -load ./build/lib/FenceInsertion.so -FenceInsertion < ./testPrograms/dummy.bc > /dev/null
```
The above will run the `FenceInsertion` pass on a simple input. You should see the following on the console: 
```bash
Fence Insertion: main
Fence Insertion: dummy
```

## Adding test programs
To add a test program first go inside the `testPrograms` directory. In there you can add your `c` file. Then you need to generate the LLVM bitcode. Since we are using LLVM-10 you need to use `clang-10`, so make sure you have that installed. After that simply run:
```bash
$ clang-10 -emit-llvm -c myFile.c
```
