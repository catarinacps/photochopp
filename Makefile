#	-- photochopp --
#
#	Makefile do projeto photochopp
#
#	@param target
#		"all" - compila
#		"clean" - limpa os binários gerados na compilação
#		"redo" - limpa binários e então compila
#		"test" - compila e realiza testes
#
#	Se make não recebe parâmetros, a ação default é all

####################################################################################################
#	Definições:

#	Diretorios do projeto
INC_DIR = include
OBJ_DIR = bin
OUT_DIR = build
SRC_DIR = src
LIB_DIR = lib

DFLAG = 

#	Flags de compilaçao. Debug para uso no GDB
CXX = g++ -std=c++17
DEBUG = $(if $(DFLAG),-g -fsanitize=address)
CXXFLAGS =\
	-Wall \
	-Wextra \
	-Wshadow \
	-Wunreachable-code
OPT = $(if $(DFLAG),-O0,-O3)
LIB = $(shell pkg-config --cflags --libs gtk+-3.0)\
	-L$(LIB_DIR)\
	-lpthread\
	-lm\
	-L/usr/X11R6/lib\
	-lX11
INC = -I$(INC_DIR)

####################################################################################################
#	Arquivos:

#	Fonte da main
MAIN = $(wildcard src/*.cpp)

#	Caminho do arquivo estático final
TARGET = $(patsubst %.cpp, $(OUT_DIR)/%, $(notdir $(MAIN)))

#	Outros arquivos fonte
SRC = # $(wildcard src/client/*.cpp)

#	Objetos a serem criados
OBJ = $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(notdir $(SRC)))

####################################################################################################
#	Regras:

#	Binarios
$(TARGET): $(OUT_DIR)/%: $(SRC_DIR)/%.cpp $(OBJ)
	$(CXX) -o $@ $^ $(INC) $(LIB) $(DEBUG) $(OPT)

$(OBJ_DIR)/%.o: $(SRC_DIR)/*/%.cpp
	$(CXX) -c -o $@ $< $(INC) $(CXXFLAGS) $(DEBUG) $(OPT)

####################################################################################################
#	Alvos:

.DEFAULT_GOAL = all

all: $(TARGET)

clean:
	rm -f $(OBJ_DIR)/*.o $(INC_DIR)/*~ $(TARGET) *~ *.o

redo: clean all

#	Debug de variaveis da make
print-%:
	@echo $* = $($*)

.PHONY: all clean redo test