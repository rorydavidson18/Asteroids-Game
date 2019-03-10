CXX = g++
CFLAGS = -std=c++14 -g -Wall

%.o : %.cpp %.hpp
	$(CXX) -c $(CFLAGS) $<

test-ship.exe: test-ship.o ship.o ../materials/material.o ../asteroids/asteroid.o ../materials/gold.o ../materials/silver.o ../materials/titanium.o
	$(CXX) -o $@ $^

clean:
	$(RM) test-ship.exe $(OBJECTS)
