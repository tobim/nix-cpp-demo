# Nix skeleton for compiler, cmake, boost.
# Dependencies (boost and others you specify) are getting built with selectec compiler (for ABI compatibility).
# Examples:
#   nix-shell --argstr compiler gcc5 --run 'mkdir build && cd build && cmake .. && cmake --build .'
#   nix-shell --argstr compiler gcc6 --run 'mkdir build && cd build && cmake .. && cmake --build .'
#   nix-shell --argstr compiler clang_5 --run 'mkdir build && cd build && cmake .. && cmake --build .'

{ compiler ? "gcc7" }:

let
  tb = builtins.fetchTarball
    https://github.com/NixOS/nixpkgs/archive/18.03-beta.tar.gz;

  pkgs_ = import tb { };

  stdenv_ = if builtins.match "clang.*" "${compiler}" == null then pkgs_.stdenv else pkgs_.clangStdenv;
  stdenv = pkgs_.overrideCC stdenv_ pkgs_.${compiler};

  #cpp_overlay = import (../nixpkgs-c++) { inherit stdenv; };
  cpp_overlay = import (builtins.fetchTarball
    https://github.com/tobimpub/nixpkgs-cpp/archive/master.tar.gz) { inherit stdenv; };

  pkgs = import tb {
    config = {};
    overlays = [ cpp_overlay ];
  };

in with pkgs; {
  nix_cpp_demo = stdenv.mkDerivation {
    name = "nix-c++-demo";
    nativeBuildInputs = [ cmake ];
    buildInputs = [ range-v3 MPark_Variant platform ];
    LANG = "en_US.UTF-8";
  };
}
