TARGET = main

CXX = g++
CXXFLAGS = -std=c++11 -g -O2

SRCDIR = ./src
INCLUDE = -I./include
OBJDIR = ./obj

SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(addprefix $(OBJDIR)/, $(notdir $(SOURCES:.cpp=.o)))
DEPENDS = $(OBJECTS:.o=.d)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	-mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@ 

clean:
	$(RM) $(OBJECTS) $(DEPENDS)

start:
	$(TARGET)

debug:
	gdb $(TARGET)

-include $(DEPENDS)