# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/Users/alexbeck/Documents/CLionProjects/spartan-hero/cmake-build-debug/_deps/spartanhero-resources-src"
  "/Users/alexbeck/Documents/CLionProjects/spartan-hero/cmake-build-debug/_deps/spartanhero-resources-build"
  "/Users/alexbeck/Documents/CLionProjects/spartan-hero/cmake-build-debug/_deps/spartanhero-resources-subbuild/spartanhero-resources-populate-prefix"
  "/Users/alexbeck/Documents/CLionProjects/spartan-hero/cmake-build-debug/_deps/spartanhero-resources-subbuild/spartanhero-resources-populate-prefix/tmp"
  "/Users/alexbeck/Documents/CLionProjects/spartan-hero/cmake-build-debug/_deps/spartanhero-resources-subbuild/spartanhero-resources-populate-prefix/src/spartanhero-resources-populate-stamp"
  "/Users/alexbeck/Documents/CLionProjects/spartan-hero/cmake-build-debug/_deps/spartanhero-resources-subbuild/spartanhero-resources-populate-prefix/src"
  "/Users/alexbeck/Documents/CLionProjects/spartan-hero/cmake-build-debug/_deps/spartanhero-resources-subbuild/spartanhero-resources-populate-prefix/src/spartanhero-resources-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/alexbeck/Documents/CLionProjects/spartan-hero/cmake-build-debug/_deps/spartanhero-resources-subbuild/spartanhero-resources-populate-prefix/src/spartanhero-resources-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/Users/alexbeck/Documents/CLionProjects/spartan-hero/cmake-build-debug/_deps/spartanhero-resources-subbuild/spartanhero-resources-populate-prefix/src/spartanhero-resources-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
