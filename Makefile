
## Created by Anjuta

CC = g++
CXXFLAGS = -Wall
OBJECTS = nets.o dialgauge.o znak.o objects.o vars.o setings.o carpanel.o
INCFLAGS = 
LDFLAGS =
LIBS = -lGL -lGLU -lglut -lpng -lfreeimage -liniparser -lpthread

all: carpanel

carpanel: $(OBJECTS)
	$(CC) $(CXXFLAGS) -o carpanel $(OBJECTS) $(LDFLAGS) $(LIBS)

.SUFFIXES:
.SUFFIXES:	.c .cc .C .cpp .o

.c.o :
	$(CC) -o $@ -c $(CXXFLAGS) $< $(INCFLAGS)

count:
	wc *.c *.cc *.C *.cpp *.h *.hpp

clean:
	rm -f *.o

.PHONY: all
.PHONY: count
.PHONY: clean
