CXX = g++
CC = $(CXX)

CXXFLAGS = -pedantic -Wall -Werror -Wextra -g3 -std=c++17
CPPFLAGS = -DDEBUG -I$(INCLUDES_DIR) -I$(SOURCES_DIR) 

INCLUDES_DIR = ../../inc
SOURCES_DIR = ../../src

OBJS = utest.o $(SOURCES_DIR)/udp_server.o $(SOURCES_DIR)/udp_client.o $(SOURCES_DIR)/flight_gear.o
TARGET = utest

all: $(TARGET)

check: $(TARGET)
	@./$(TARGET) -v

recheck: clean check

clang_check: CXX = clang++
clang_check: check

clean:
	@$(RM) $(TARGET) $(OBJS)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET) -lpthread

utest.o: utest.cpp $(INCLUDES_DIR)/udp_server.hpp $(INCLUDES_DIR)/udp_client.hpp $(INCLUDES_DIR)/blocking_map.hpp $(INCLUDES_DIR)/mu_test.h

$(SOURCES_DIR)/udp_server.o: $(SOURCES_DIR)/udp_server.cpp $(INCLUDES_DIR)/udp_server.hpp

$(SOURCES_DIR)/udp_client.o: $(SOURCES_DIR)/udp_client.cpp $(INCLUDES_DIR)/udp_client.hpp

$(SOURCES_DIR)/flight_gear.o: $(INCLUDES_DIR)/flight_gear.hpp 


.PHONY: all check recheck clang_check clean