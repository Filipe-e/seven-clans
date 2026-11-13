# Nome do compilador - gemine
CXX = g++

# Flags (opções) de compilação
# -Wall e -Wextra: ativam alertas úteis para ajudar a encontrar erros
# -std=c++11: garante que usamos C++11 (ou mais recente, pode mudar para c++17 se quiser)
CXXFLAGS = -Wall -Wextra -std=c++11

# Pasta de destino
BUILD_DIR = build

# Nome do executável final (no Windows, usamos .exe)
# Se estiver no Linux/Mac, pode tirar o .exe
TARGET = $(BUILD_DIR)/jogo.exe

# Todos os arquivos fonte (.cpp) do seu projeto
SOURCES = main.cpp player.cpp decorations.cpp utils.cpp

# O que acontece quando você escreve apenas "make" no terminal
all: $(BUILD_DIR) $(TARGET)

# Cria a pasta de build apenas se ela não existir
$(BUILD_DIR):
	if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)

# Compila o executável
$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)
	@echo Compilacao concluida! O executavel esta na pasta build.

# Limpa a pasta build usando o comando do Windows (rmdir /S /Q)
clean:
	if exist $(BUILD_DIR) rmdir /S /Q $(BUILD_DIR)
	@echo Pasta de build limpa e removida.

.PHONY: all clean