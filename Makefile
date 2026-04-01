# Nom de l'exécutable
TARGET = game_of_life

# Dossiers
SRC_DIR = src
BUILD_DIR = build

# Compilateur
CC = gcc

# Flags
CFLAGS = -Wall -Wextra -std=c11
LDFLAGS = -lraylib -lm -lpthread -ldl -lrt -lX11

# Fichiers source et objets
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

# Règle principale
all: $(BUILD_DIR) $(TARGET)

# Compilation finale
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Compilation des .c en .o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Création du dossier build
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Nettoyage
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

# Rebuild complet
re: clean all

.PHONY: all clean re