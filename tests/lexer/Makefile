CXX = g++
CC = $(CXX)

CXXFLAGS = -pedantic -Wall -Werror -Wextra -g3 -std=c++17
CPPFLAGS = -DDEBUG -I$(INCLUDES_DIR) -I$(SOURCES_DIR) 

INCLUDES_DIR = ../../inc
SOURCES_DIR = ../../src

LDFLAGS= -I/usr/local/include/Poco 

OBJS = utest.o $(SOURCES_DIR)/lexer.o $(SOURCES_DIR)/parser.o
TARGET = utest

LDLIBS = -lpthread -lpthread -lboost_system -lboost_thread

all: $(TARGET)

check: $(TARGET)
	@./$(TARGET) -v

recheck: clean check

clean:
	@$(RM) $(TARGET) $(OBJS)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(OBJS) -o $(TARGET) $(LDLIBS)

utest.o: $(INCLUDES_DIR)/mu_test.h $(INCLUDES_DIR)/lexer.hpp 

.PHONY: all check recheck clang_check clean

#dependencies

$(SOURCES_DIR)/lexer.o: $(INCLUDES_DIR)/lexer.hpp 

$(SOURCES_DIR)/parser.o: $(INCLUDES_DIR)/parser.hpp $(INCLUDES_DIR)/ast_node.hpp




