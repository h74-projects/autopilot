#telnet mediator makefile

CXX = g++
CC = $(CXX)

CXXFLAGS = -pedantic -Wall -Werror -Wextra -g3 -std=c++17
CPPFLAGS = -DDEBUG -I$(INCLUDES_DIR) -I$(SOURCES_DIR) 

INCLUDES_DIR = ../../inc
SOURCES_DIR = ../../src

OBJS = utest.o $(SOURCES_DIR)/mediator_telnet.o $(SOURCES_DIR)/telnet_client.o $(SOURCES_DIR)/udp_server.o
TARGET = utest

all: $(TARGET)

check: $(TARGET)
#5401 is the port number! change accordingly in utest if changed here
	@ sudo rm /usr/share/games/flightgear/Protocol/generic_small.xml
	@ sudo cp generic_small.xml /usr/share/games/flightgear/Protocol/generic_small.xml
	@ gnome-terminal -- fgfs --telnet=foo,bar,200,foo,5401,bar --generic=socket,out,5,127.0.0.1,49002,udp,generic_small
	sleep 60
	@./$(TARGET) -v

recheck: clean check

clang_check: CXX = clang++
clang_check: check

clean:
	@$(RM) $(TARGET) $(OBJS)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET) -lpthread -lpugixml

utest.o: $(INCLUDES_DIR)/mu_test.h

.PHONY: all check recheck clang_check clean

#dependencies
$(SOURCES_DIR)/mediator_telnet.o: $(INCLUDES_DIR)/mediator_telnet.hpp $(INCLUDES_DIR)/mediator.hpp $(INCLUDES_DIR)/telnet_client.hpp

$(SOURCES_DIR)/telnet_client.o: $(INCLUDES_DIR)/telnet_client.hpp

$(SOURCES_DIR)/udp_server.o: $(INCLUDES_DIR)/udp_server.hpp
