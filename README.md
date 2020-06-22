# Thendrall Tales

A dwarf fortress clone.  

## Building

On Windows:
Set the `VCVARSALL` env variable. (Make it point to your vcvarsall)  
Set the `BAZEL_LLVM` env variable.  

run `scripts\build.ps1`
The script can be passed a compiler flag:
`scripts\build.ps1 -Compiler Clang`
