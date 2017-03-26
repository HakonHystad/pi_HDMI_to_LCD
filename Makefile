#makefile for hdmi_i2c
exe=display
CXX = g++
CXXFLAGS = --std=c++11
objects=build/main.o build/hdmiI2C.o

exe: $(objects)
	g++ $(objects) -o $(exe)
%.o:%.cpp
	$(CXX) -c $(CXXFLAGS) $^
build/%.o: %.cpp 
	$(CXX) -c $(CXXFLAGS) $^ -o $@
clean:
	rm $(exe) $(objects)
