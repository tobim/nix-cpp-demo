# nix-c++-demo

This is an example to show how to manage a development environment for c++ project with the nix package manager and cmake.

# requirements

nix, make (optional), bash

## usage
#### recommended:

Use the convenience Makefile in the top level directory to build.

make [targets]
  optional variables:
  attr      comma-separated list of compiler attributes from nixpkgs (currently only gcc and clang)
  variant   comma-separated list of build variants (release,debug,profile)



