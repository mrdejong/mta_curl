#### Start of system configuration section ####

CC = g++
LD = g++
PROG = ml_curl.so
ILOC = ../server/mods/deathmatch/modules/ml_curl.so
CXX = g++
CPP = g++

# Compiler flags
# NOTE: add -g for debug, remove for release!
CPPFLAGS = -fPIC -O2 -Wall -I./ -I/usr/include
LDFLAGS = -fPIC -shared -Wl,-soname,$(PROG).1,-R./
LIBS = -lpthread -lstdc++ -L./lib -llua -lcurl

#### End of system configuration section ####

#### Source and object files

SRC_LOCAL =		$(wildcard ./*.cpp ./extra/*.cpp)
OBJ_LOCAL =		$(patsubst %.cpp,%.o,$(SRC_LOCAL))
OBJS	  =     $(OBJ_LOCAL)
SRCS	  =     $(SRC_LOCAL)
DEPS	  =     $(patsubst %.o,%.d,$(OBJS))

#### Make rules

all : ml_curl

ml_curl : $(OBJS)
	$(CC) $(CPPFLAGS) $(LDFLAGS) -o $(PROG) $(OBJS) $(LIBS)

install :
	cp ./$(PROG) $(ILOC)

clean :
	@rm *.o
	@rm extra/*.o
	@rm $(PROG)
	@rm $(ILOC)

-include $(DEPS)
