CC=g++
CFLAGS=-c -Wall

LDFLAGS = -framework OpenGL -framework GLUT -Wno-deprecated

SOURCES=main.cpp display.cpp background.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=project 

$(EXECUTABLE): $(OBJECTS)
	$(CC) $^ -o $@ $(LDFLAGS) $(INSTALLED_DEPS)

main.o: main.cpp display.hpp util.hpp background.hpp
	$(CC) $(CFLAGS) $< $(LDFLAGS) $(INSTALLED_DEPS)

display.o :display.cpp display.hpp util.hpp background.hpp
	$(CC) $(CFLAGS) $< $(LDFLAGS) $(INSTALLED_DEPS)

background.o:background.cpp background.hpp
	$(CC) $(CFLAGS) $< $(LDFLAGS) $(INSTALLED_DEPS)

clean:
	rm *.o project 
