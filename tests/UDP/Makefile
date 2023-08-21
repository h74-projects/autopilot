CXX = g++
CC = $(CXX)

CXXFLAGS = -pedantic -Wall -Werror -Wextra -g3 -std=c++17
CPPFLAGS = -DDEBUG -I$(INCLUDES_DIR) -I$(SOURCES_DIR) 

INCLUDES_DIR = ../../inc
SOURCES_DIR = ../../src

OBJS = utest.o udp_server.o udp_client.o
TARGET = utest

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET) -lpthread

utest.o: utest.cpp $(INCLUDES_DIR)/udp_server.hpp $(INCLUDES_DIR)/udp_client.hpp $(INCLUDES_DIR)/mu_test.h
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c utest.cpp -o utest.o

udp_server.o: $(SOURCES_DIR)/udp_server.cpp $(INCLUDES_DIR)/udp_server.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $(SOURCES_DIR)/udp_server.cpp -o udp_server.o

udp_client.o: $(SOURCES_DIR)/udp_client.cpp $(INCLUDES_DIR)/udp_client.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $(SOURCES_DIR)/udp_client.cpp -o udp_client.o

check: $(TARGET)
	@./$(TARGET) -v

recheck: clean check

clang_check: CXX = clang++
clang_check: check

clean:
	@$(RM) $(TARGET) $(OBJS)

.PHONY: all check recheck clang_check clean