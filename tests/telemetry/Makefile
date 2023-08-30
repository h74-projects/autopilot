#telemetry makefile

CXX = g++
CC = $(CXX)

CXXFLAGS = -pedantic -Wall -Werror -Wextra -g3 -std=c++17
CPPFLAGS = -DDEBUG -I$(INCLUDES_DIR)

INCLUDES_DIR = ../../inc
SOURCES_DIR = ../../src

LDFLAGS= -I/usr/local/include/Poco

OBJS = utest.o $(SOURCES_DIR)/telemetry.o $(SOURCES_DIR)/server_udp.o $(SOURCES_DIR)/protocol.o $(SOURCES_DIR)/variables.o $(SOURCES_DIR)/telnet_client.o
TARGET = utest

LDLIBS = -lpthread -L/usr/local/lib/poco -lPocoNet -lPocoFoundation -lpugixml

all: $(TARGET)

check: $(TARGET)
#5401 is the port number! change accordingly in utest if changed here
	@ sudo rm /usr/share/games/flightgear/Protocol/generic_small.xml
	@ sudo cp generic_small.xml /usr/share/games/flightgear/Protocol/generic_small.xml
	@ gnome-terminal -- fgfs --telnet=foo,bar,200,foo,5401,bar --generic=socket,out,5,127.0.0.1,49002,udp,generic_small
	sleep 60
	@./$(TARGET) -v

recheck: clean check

clean:
	@$(RM) $(TARGET) $(OBJS)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET) $(LDLIBS)

utest.o: $(INCLUDES_DIR)/mu_test.h

.PHONY: all check recheck clang_check clean

#dependencies
$(SOURCES_DIR)/telemetry.o: $(INCLUDES_DIR)/telemetry.hpp

$(SOURCES_DIR)/protocol.o: $(INCLUDES_DIR)/protocol.hpp

$(SOURCES_DIR)/server_udp.o: $(INCLUDES_DIR)/server.hpp $(INCLUDES_DIR)/server_udp.hpp

$(SOURCES_DIR)/variables.o: $(INCLUDES_DIR)/variables.hpp $(INCLUDES_DIR)/blocking_map.hpp

$(SOURCES_DIR)/telnet_client.o: $(INCLUDES_DIR)/telnet_client.hpp
