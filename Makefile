#makefile for hdmiLCD
exe=display
CXX = g++
CXXFLAGS = --std=c++11
objects=build/main.o build/hdmiI2Cdriver.o build/hdmiLCD.o build/i2c_LCD.o

exe: $(objects)
	g++ $(objects) -o $(exe)
#%.o:%.cpp
#	$(CXX) -c $(CXXFLAGS) $^
build/%.o: src/%.cpp 
	$(CXX) -c $(CXXFLAGS) $^ -o $@
clean:
	rm $(exe) $(objects)
