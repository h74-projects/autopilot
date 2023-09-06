#presentation makefile

CXX = g++
CC = $(CXX)

CXXFLAGS = -pedantic -Wall -Werror -Wextra -g3 -std=c++17
CPPFLAGS = -DDEBUG -I$(INCLUDES_DIR)

INCLUDES_DIR = ../../inc
SOURCES_DIR = ../../src

LDFLAGS= -I/usr/local/include/Poco

OBJS = utest.o $(SOURCES_DIR)/telemetry.o $(SOURCES_DIR)/server_udp.o $(SOURCES_DIR)/protocol.o $(SOURCES_DIR)/variables.o $(SOURCES_DIR)/client_telnet.o $(SOURCES_DIR)/middle_man.o\
 $(SOURCES_DIR)/variables_environment.o

TARGET = utest

LDLIBS = -lpthread -lPocoFoundation -lPocoNet -lpugixml -L/usr/local/lib

VALGRIND = valgrind

VFLAGS= --leak-check=full --track-origins=yes -s

all: $(TARGET)

check: $(TARGET)
#5401 is the port number! change accordingly in utest if changed here
	sudo rm /usr/share/games/flightgear/Protocol/generic_small.xml
	sudo cp generic_small.xml /usr/share/games/flightgear/Protocol/generic_small.xml
	@ gnome-terminal -- fgfs --telnet=foo,bar,200,foo,5401,bar --generic=socket,out,5,127.0.0.1,49002,udp,generic_small
	sleep 60
	@./$(TARGET) -v

recheck: clean check

clean:
	@$(RM) $(TARGET) $(OBJS)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET) $(LDLIBS)

lib:
	export LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH

utest.o: $(INCLUDES_DIR)/mu_test.h

.PHONY: all check recheck clang_check clean

valgrind:
	$(VALGRIND) $(VFLAGS) ./utest

hell:
	valgrind --tool=helgrind -s ./$(TARGET) 2> hell.log


#dependencies
$(SOURCES_DIR)/telemetry.o: $(INCLUDES_DIR)/telemetry.hpp

$(SOURCES_DIR)/protocol.o: $(INCLUDES_DIR)/protocol.hpp

$(SOURCES_DIR)/server_udp.o: $(INCLUDES_DIR)/server.hpp $(INCLUDES_DIR)/server_udp.hpp

$(SOURCES_DIR)/variables.o: $(INCLUDES_DIR)/variables.hpp $(INCLUDES_DIR)/blocking_map.hpp

$(SOURCES_DIR)/client_telnet.o: $(INCLUDES_DIR)/client.hpp $(INCLUDES_DIR)/client_telnet.hpp

$(SOURCES_DIR)/middle_man.o: $(INCLUDES_DIR)/middle_man.hpp $(INCLUDES_DIR)/blocking_map.hpp

$(SOURCES_DIR)/variables_environment.o: $(INCLUDES_DIR)/variables_environment.hpp