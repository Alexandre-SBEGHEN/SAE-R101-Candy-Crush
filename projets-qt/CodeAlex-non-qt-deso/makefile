CXX = g++
CXXFLAGS = -Wall -std=c++17 -Iinclude
TARGET = main

SRCDIR = src
BUILDDIR = build

# Trouve tous les .cpp dans src/
SRC_FILES = $(wildcard $(SRCDIR)/*.cpp)
# Ajoute main.cpp
SOURCES = main.cpp $(SRC_FILES)
# Crée les noms des .o dans build/
OBJECTS = $(BUILDDIR)/main.o $(SRC_FILES:$(SRCDIR)/%.cpp=$(BUILDDIR)/%.o)

all: $(BUILDDIR) $(TARGET)

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)

# Compile main.cpp
$(BUILDDIR)/main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile les .cpp de src/
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILDDIR) $(TARGET)

.PHONY: all clean