PROGRAM = code

CXX = g++
CXXFLAGS = -g -std=c++17

CPP_FILES = $(wildcard bookstore/bookstore/*.cpp)
H_FILES = $(wildcard bookstore/bookstore/*.h)

LDOPTIONS = -L.

$(PROGRAM): $(CPP_FILES) $(H_FILES) 
	$(CXX) -o $(PROGRAM) $(CXXFLAGS) $(LDOPTIONS) $(CPP_FILES) $(H_FILES)
