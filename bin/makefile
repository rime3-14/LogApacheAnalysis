# Variables de compilation
CXX = g++
CXXFLAGS = -ansi -pedantic -Wall -std=c++11
TARGET = analog
SOURCES = main.cpp Graphe.cpp Lecture.cpp
OBJECTS = $(SOURCES:.cpp=.o)
MAP ?= 0  # Pour activer ou désactiver la MAP, cleanall puis make avec l'option MAP=1 ou MAP=0 (0 par défaut).

# Compilation de l'exécutable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# Compilation de chaque fichier source en objet
%.o: %.cpp %.h
	$(CXX) $(CXXFLAGS) -c -g -DMAP=$(MAP) $<

# Nettoyage des fichiers objets
clean:
	rm -f  *.o

# Nettoyage des fichiers objets et de l'exécutable
cleanall:
	echo Nettoyage
	rm -f $(TARGET) *.o