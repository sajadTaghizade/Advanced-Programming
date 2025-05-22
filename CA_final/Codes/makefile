CXX = g++
CXXFLAGS = -std=c++20 -g -Wall -Wextra -pedantic -I./include #-fsanitize=address -fsanitize=undefined
SRCDIRS = server utils examples ./
INCLUDEDIR = includes
OBJDIR = objects
BINDIR = .
EXECUTABLE = $(BINDIR)/utms.out

SOURCES := $(wildcard $(SRCDIRS:%=%/*.cpp))
OBJECTS := $(patsubst $(SRCDIRS)/%.cpp, $(OBJDIR)/%.o, $(SOURCES))

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(wildcard $(INCLUDEDIR)/*.hpp)
	mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/template_parser.o: utils/template_parser.cpp utils/template_parser.hpp utils/request.cpp utils/request.hpp utils/utilities.hpp utils/utilities.cpp utils/strutils.hpp utils/strutils.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/response.o: utils/response.cpp utils/response.hpp utils/include.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/request.o: utils/request.cpp utils/request.hpp utils/include.hpp utils/utilities.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/utilities.o: utils/utilities.cpp utils/utilities.hpp utils/strutils.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/strutils.o: utils/strutils.cpp utils/strutils.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/server.o: server/server.cpp server/server.hpp server/route.hpp utils/utilities.hpp utils/strutils.hpp utils/response.hpp utils/request.hpp utils/include.hpp utils/template_parser.hpp utils/template_parser.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/route.o: server/route.cpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/main.o: src/main.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR)/*.o $(EXECUTABLE)