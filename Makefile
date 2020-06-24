# Définition des variables

EXT = c
CXX = gcc
EXEC = main.exe

CXXFLAGS = -g
LDFLAGS = -lm


OBJDIR = .
SRC = $(wildcard *.$(EXT))
OBJ = $(SRC:.$(EXT)=.o)
OBJ := $(addprefix $(OBJDIR)/, $(OBJ))

all: $(EXEC)

$(EXEC): $(OBJ)
	@$(CXX) -o $@ $^ $(LDFLAGS)

$(OBJDIR)/%.o: %.$(EXT)
	@$(CXX) -o $@ -c $< $(CXXFLAGS)

clean:
	@rm -rf $(OBJDIR)/*.o
	@rm -f $(EXEC)

run: $(EXEC)
	./$(EXEC)
	gnuplot 'draw'

debug: $(EXEC)
	gdb -tui ./$(EXEC)
	
verif: $(EXEC)
	valgrind ./$(EXEC)
