#!/bin/sh

# Script to generate configure script and Makefile.in files

echo "Running aclocal..."
aclocal
echo "Running autoconf to set macros..."
autoconf
echo "Creating config.h header with autoheader..."
autoheader
echo "Invoking automake..."
automake --add-missing
echo "Running autoconf to generate ./configure script"
autoconf
echo "Now type ./configure to create build scripts"
