cxx = g++
cxxflags = -g


main: Setting.cpp Setting.hpp main.cpp
	$(cxx) $(cxxflags) Setting.cpp -c
	$(cxx) $(cxxflags) main.cpp -c
	$(cxx) $(cxxflags) Setting.o main.o -o main
