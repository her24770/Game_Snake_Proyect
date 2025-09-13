# Makefile para SnakeGame-CPP-Multihilo
# Fase 2: Entorno Gráfico

# Compilador y flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
INCLUDES = -Iinclude

# Directorios
SRC_DIR = src
OBJ_DIR = obj
INCLUDE_DIR = include

# Archivos fuente
SOURCES = $(SRC_DIR)/main.cpp \
          $(SRC_DIR)/utils/WindowsConsole.cpp \
          $(SRC_DIR)/utils/InputHandler.cpp \
          $(SRC_DIR)/rendering/ASCIIArt.cpp

# Archivos objeto
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Ejecutable
EXECUTABLE = snake_game

# Objetivo principal
all: $(EXECUTABLE)

# Crear ejecutable
$(EXECUTABLE): $(OBJECTS)
	@echo "🔗 Enlazando $(EXECUTABLE)..."
	$(CXX) $(OBJECTS) -o $(EXECUTABLE)
	@echo "✅ Compilación exitosa!"

# Compilar archivos objeto
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	@echo "🔨 Compilando $<..."
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Limpiar archivos generados
clean:
	@echo "🧹 Limpiando archivos objeto y ejecutable..."
	rm -rf $(OBJ_DIR) $(EXECUTABLE)
	@echo "✅ Limpieza completada!"

# Ejecutar el programa
run: $(EXECUTABLE)
	@echo "🚀 Ejecutando $(EXECUTABLE)..."
	./$(EXECUTABLE)

# Instalar dependencias (para Ubuntu/WSL)
install-deps:
	@echo "📦 Instalando dependencias para Ubuntu/WSL..."
	sudo apt update
	sudo apt install -y build-essential g++ make

# Verificar compilador
check:
	@echo "🔍 Verificando herramientas de compilación..."
	@which g++ > /dev/null && echo "✅ g++ encontrado: $$(g++ --version | head -n1)" || echo "❌ g++ no encontrado"
	@which make > /dev/null && echo "✅ make encontrado: $$(make --version | head -n1)" || echo "❌ make no encontrado"

# Compilación con información de debug
debug: CXXFLAGS += -g -DDEBUG
debug: $(EXECUTABLE)
	@echo "🐛 Compilación en modo debug completada!"

# Mostrar ayuda
help:
	@echo "🎯 Comandos disponibles:"
	@echo "  make all          - Compilar el proyecto"
	@echo "  make clean        - Limpiar archivos generados"
	@echo "  make run          - Compilar y ejecutar"
	@echo "  make debug        - Compilar en modo debug"
	@echo "  make check        - Verificar herramientas"
	@echo "  make install-deps - Instalar dependencias (Ubuntu/WSL)"
	@echo "  make help         - Mostrar esta ayuda"

# Objetivos que no son archivos
.PHONY: all clean run debug check install-deps help