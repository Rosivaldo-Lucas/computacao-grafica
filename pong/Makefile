# Configurações
CXX = g++
CXXFLAGS = -std=c++11 -Wall
SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin

# Lista de arquivos fonte (todos os arquivos .cpp dentro da pasta src)
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)

# Lista de objetos (um para cada arquivo fonte)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SOURCES))

# Nome do executável
EXECUTABLE = $(BIN_DIR)/my_program

# Comando padrão (gerar o executável)
all: $(EXECUTABLE)

# Regra para compilar um objeto a partir de um arquivo fonte
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regra para gerar o executável a partir dos objetos
$(EXECUTABLE): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@ -lglut -lGLU -lGL -lm -lopenal -lsndfile -pthread -g -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

# Regra para limpar os arquivos intermediários e o executável
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

.PHONY: all clean
