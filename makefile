# Compileur
CC = g++
# Flags compileur 
CCFLAGS = -Wall -g 
# Debogueur
DEBOGUEUR = gdb

# Dossiers
SRCFILE = .
BUILDFILE = bin

# Fichiers compile
SRC = matrixLib.cpp test.cpp

EXENAME = test.out

#à modifié
SOURCES = $(patsubst %.c,$(SRCFILE)/%.c,$(SRC))

# Fichier objet
OBJECTS = $(patsubst %.c,$(BUILDFILE)/%.o,$(SRC))
# Nom executable
EXECUTABLE = $(BUILDFILE)/$(EXENAME)
#Arguments executables
ARG =



all: $(EXECUTABLE)


valgrind: $(EXECUTABLE)
	valgrind --leak-check=full --show-leak-kinds=all $(EXECUTABLE) $(ARG)


run : $(EXECUTABLE)
	@echo run $(EXECUTABLE) $(ARG)
	./$(EXECUTABLE) $(ARG)


debug : $(EXECUTABLE)
	@gdb $(EXECUTABLE) $(ARG)

# création des executables
$(EXECUTABLE): $(OBJECTS)
	@mkdir -p $(BUILDFILE)
	$(CC) $(CCFLAGS) $(OBJECTS) -o $@


# compilation des objets
$(BUILDFILE)/%.o: $(SRCFILE)/%.c
	@mkdir -p $(BUILDFILE)
	$(CC) $(CCFLAGS) -c $< -o $@

# nettoyage
clear:
	@echo nettoyage
	@rm -rf $(BUILDFILE) 
	@rm -rf *.pdf 
	@rm -rf *.dot

