#blocking map makefile

CXX = g++
CC = $(CXX)

INCLUDE_PATH= ../../inc
INLLUDE_PATH+= ../../inc/inl
SOUREC_PATH= ../../src

CFLAGS = -Wall -Werror
CFLAGS+= -Wextra
CFLAGS+= -pedantic
CFLAGS+= -g3
CFLAGS+= -DDEBUG
CFLAGS += -pthread


CXXFLAGS = $(CFLAGS)
CXXFLAGS += -std=c++17

# flags for preprocessor

LDLIBS = -lpthread
CPPFLAGS= -I$(INCLUDE_PATH)
CPPFLAGS+= -I$(INLLUDE_PATH)

VALGRIND = valgrind

VFLAGS= --leak-check=full --track-origins=yes -s

OBJECTS = utest.o

TARGET= utest

all: utest 

utest: $(OBJECTS) 

check: utest
	@./utest -v

clean:
	@$(RM) all $(OBJECTS)

.PHONY: clean all

valgrind:
	$(VALGRIND) $(VFLAGS) ./utest

hell:
	valgrind --tool=helgrind -s ./$(TARGET) 2> hell.log

# dependencies

utest.o: $(INCLUDE_PATH)/var.hpp $(INLLUDE_PATH)/var.hxx