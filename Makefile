CXX = g++

CXXFLAGS = -Ofast -std=c++14

# Include flags
INCFLAGS  = -I./src

# C sources compille
c_src=$(wildcard ./src/*.cpp)

# Deps
obj=$(c_src:.cpp=.o)
dep=$(obj:.o=.d)

exampleMain=example.cpp
timedExampleMain=timedExample.cpp

execExamp = example.ex
execTimed = timedExample.ex

.PHONY: all example timedExample

all: example timedExample

example: $(execExamp)
timedExample: $(execTimed)

$(execExamp): $(obj) $(exampleMain)
	$(CXX) $(CXXFLAGS) $(INCFLAGS) -o $@ $^

$(execTimed): $(obj) $(timedExampleMain)
	$(CXX) $(CXXFLAGS) $(INCFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCFLAGS) -o $@ -c $<

%.d: %.o
	$($CXX) $(CXXFLAGS) $< -MM -MT $(@:.d=.o) >$@

.PHONY: clean
clean:
	rm -f $(obj)

.PHONY: cleandep
cleandep:
	rm -f $(dep)

.PHONY: pristine
pristine:
	rm -f $(obj) $(dep) *.ex


