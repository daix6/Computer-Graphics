CC := g++

SOURCE_DIR := src
OBJ_DIR := obj

_OBJS := main.o modelReader.o Point.o
OBJS := $(patsubst %, $(OBJ_DIR)/%, $(_OBJS))

CFLAGS := -g -Iinclude
LDFLAGS := -Llib
LDFLAGS += -static-libgcc

ifeq ($(OS), Windows_NT) # Enviroment Variables
	LDFLAGS += -lfreeglut -lglu32 -lopengl32
	EXECUTABLE := main.exe
else
	LDFLAGS += -lGL -lGLU -lglut
	EXECUTABLE := main
endif

all: $(EXECUTABLE)

$(OBJ_DIR)/%.o: $(SOURCE_DIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(EXECUTABLE): $(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS)

.PHONY: clean, report

clean:
	rm -f $(OBJ_DIR)/*.o $(EXECUTABLE)
	rm -rf report/*.aux report/*.log report/*.out report/*.toc report/*.gz

report:
	pdflatex -synctex=1 -quiet -aux-directory=doc/ ./doc/report.tex 