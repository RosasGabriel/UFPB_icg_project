# Nome do projeto
PROJ_NAME=icg_project

# Diretórios
SRC_DIR=src
INC_DIR=include
OBJ_DIR=objects

# Arquivos .hpp
HPP_SOURCE=$(wildcard $(INC_DIR)/*.hpp)

# Arquivos .cpp
CPP_SOURCE=$(wildcard $(SRC_DIR)/*.cpp)

# Arquivos objeto
OBJ=$(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(CPP_SOURCE))

# Compilador e linker
CXX=g++
GL_LIBS=-lGL -lGLU -lglut

# Flags do compilador
CXXFLAGS= -Wall -Wextra --std=c++20 -g -I$(INC_DIR)

# Regra padrão
all: objFolder $(PROJ_NAME)

# Regra para construir o executável
$(PROJ_NAME): $(OBJ)
	@echo 'Building binary using G++ linker: $@'
	$(CXX) $^ -o $@ $(GL_LIBS)
	@echo 'Finished building binary: $@'
	@echo ' '

# Regra para construir os arquivos objeto
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(HPP_SOURCE)
	@echo 'Building target using G++ compiler: $<'
	$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo ' '

# Regra para criar o diretório de objetos
objFolder:
	@mkdir -p $(OBJ_DIR)

# Limpeza dos arquivos gerados
clean:
	@echo 'Cleaning up...'
	@$(RM) $(OBJ_DIR)/*.o $(PROJ_NAME) *~
	@rmdir $(OBJ_DIR)

.PHONY: all clean objFolder
