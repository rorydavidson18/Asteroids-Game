CXX = g++
CFLAGS = -std=c++14 -g -Wall

%.o : %.cpp %.hpp
	$(CXX) -c $(CFLAGS) $<

test-material.exe: test-material.o material.o gold.o silver.o titanium.o
	$(CXX) -o $@ $^

clean:
	$(RM) test-material.exe $(OBJECTS)
