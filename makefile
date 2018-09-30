#!/usr/bin/env make

PROG = mwserial

SRCDIR = ./src
OBJDIR = ./obj

SRCS = src/main.cpp \
	src/socket.cpp \
	src/serialport.cpp \

HEADERS = src/socket.hpp \
	src/serialport.hpp \
	src/utils.hpp \

OBJS = obj/main.o \
	obj/socket.o \
	obj/serialport.o \

# boost setting
BOOSTDIR = /Users/kshibata/boost/1.68.0
BOOSTSUFFIX = -xgcc42-mt-x64-1_68
BOOSTLIBS = -lboost_system
BOOSTLIBS := $(addsuffix $(BOOSTSUFFIX), $(BOOSTLIBS))
BOOSTINC = -I$(BOOSTDIR)/include/boost-1_68

CXX = clang++
LD = clang++

INC = $(BOOSTINC)
LIBDIR = -L$(BOOSTDIR)/lib
LIBS = -dn $(BOOSTLIBS)

LDFLAGS = $(LIBDIR)
CXXFLAGS = -O2 -Wall -std=c++11 $(INC) 

$(PROG): $(OBJS)
	$(LD) $(LDFLAGS) $(LIBS) -o $@ $^

$(OBJS): $(HEADERS)

${OBJDIR}/%.o: ${SRCDIR}/%.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

.PHONY: all clean

all: $(PROG)

clean:
	$(RM) $(PROG)
	$(RM) $(OBJS)

test: all
	./$(PROG)
