
##############################################################
#
#   make file template for me
#
##############################################################
CC=gcc
XX=g++

CFLAGS=-Wall\
    -O \
    -g \
	-DUTTEST

# include path
INCLUDE=-I. \
		-I../../../src/ \
		-I../../../thirdsrc/gtest/include/

# lib 
LIB=-lpthread \
	-lgtest \

# lib path 
LIBPATH=-L../../../thirdsrc/gtest/lib/ \
		-L../../../

default: closure_test time_debugger_test

%.o:%.cpp
	$(XX) $(CFLAGS) $(INCLUDE) -c $^ -o $@
%.o:%.c
	$(XX) $(CFLAGS) $(INCLUDE) -c $^ -o $@
%.o:%.cc
	$(XX) $(CFLAGS) $(INCLUDE) -c $^ -o $@

closure_test : closure_test.o
	$(XX) $^ -o closure_test $(LIB) $(LIBPATH)

time_debugger_test : time_debugger_test.o
	$(XX) $^ -o time_debugger_test $(LIB) $(LIBPATH)

.PHONY: clean
clean:
	@rm -rf *.o closure_test time_debugger_test
