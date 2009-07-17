#!/bin/sh

# Script to generate configure script and Makefile.in files

aclocal
autoconf
automake --add-missing
autoconf
