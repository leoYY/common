
##############################################################
#
#   make file template for me
#
##############################################################
CC=gcc
XX=g++

CFLAGS=-Wall\
    -O\
    -g

# include path
INCLUDE=-I. \
		-I../../../src/ \
		-I../../../thirdsrc/gtest/output/include/

# lib 
LIB=-lpthread \
	-lgtest \

# lib path 
LIBPATH=-L../../../thirdsrc/gtest/output/lib/

default: closure_test

closure_test : closure_test.cpp
	$(XX) $(CFLAGS) $(INCLUDE) closure_test.cpp -o closure_test $(LIB) $(LIBPATH)

.PHONY: clean
clean:
	@rm closure_test
