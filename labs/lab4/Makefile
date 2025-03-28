CC = gcc

BIN_DIR = bin
SERVER_BIN = $(BIN_DIR)/server
CLIENT_BIN = $(BIN_DIR)/client

SERVER_SRC = server/server.c

CLIENT_SRC = client/client.c

.PHONY: all clean

# Компиляция всех бинарников
all: $(BIN_DIR) $(SERVER_BIN) $(CLIENT_BIN)

# Создание каталога bin
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Сборка сервера
$(SERVER_BIN): $(SERVER_SRC)
	$(CC) $(SERVER_SRC) -o $@

# Сборка клиента
$(CLIENT_BIN): $(CLIENT_SRC)
	$(CC) $(CLIENT_SRC) -o $@

# Очистка
clean:
	rm -rf $(BIN_DIR)
