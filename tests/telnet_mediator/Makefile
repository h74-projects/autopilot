#telnet mediator makefile

CXX = g++
CC = $(CXX)

CXXFLAGS = -pedantic -Wall -Werror -Wextra -g3 -std=c++17
CPPFLAGS = -DDEBUG -I$(INCLUDES_DIR) -I$(SOURCES_DIR) 

INCLUDES_DIR = ../../inc
SOURCES_DIR = ../../src

OBJS = utest.o $(SOURCES_DIR)/mediator_telnet.o $(SOURCES_DIR)/telnet_client.o
TARGET = utest

all: $(TARGET)

check: $(TARGET)
#5401 is the port number! change accordingly in utest if changed here
	gnome-terminal -e "fgfs ..... --telnet=foo,bar,100,foo,5401,bar"
	@./$(TARGET) -v

recheck: clean check

clang_check: CXX = clang++
clang_check: check

clean:
	@$(RM) $(TARGET) $(OBJS)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET) -lpthread

utest.o: $(INCLUDES_DIR)/mu_test.h

$(SOURCES_DIR)/mediator_telnet.o: $(INCLUDES_DIR)/mediator_telnet.hpp $(INCLUDES_DIR)/mediator.hpp $(INCLUDES_DIR)/telnet_client.hpp

$(SOURCES_DIR)/telnet_client.o: $(INCLUDES_DIR)/telnet_client.hpp

.PHONY: all check recheck clang_check clean