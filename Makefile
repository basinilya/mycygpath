# -L /usr/lib64 
#LDFLAGS = 
TARGET = mycygpath
OFILES = mycygpath.o  path.o  strfuncs.o

LINK.o = $(LINK.cc)

$(TARGET): $(OFILES)

*.o: mycygpath.h

clean:
	rm -f *.o

