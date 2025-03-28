CC = gcc
SERVER_CFLAGS = -Iserver/include  -pthread
CLIENT_CFLAGS = -Iclient/include

BIN_DIR = bin
SERVER_BIN = $(BIN_DIR)/mt_tcp_server
CLIENT_BIN = $(BIN_DIR)/tcp_client

SERVER_SRC = server/src/mt_tcp_server.c \
			server/src/str_utils.c \
			server/main.c

CLIENT_SRC = client/src/tcp_client.c \
			client/main.c

.PHONY: all clean

# Компиляция всех бинарников
all: $(BIN_DIR) $(SERVER_BIN) $(CLIENT_BIN)

# Создание каталога bin
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Сборка сервера
$(SERVER_BIN): $(SERVER_SRC)
	$(CC) $(SERVER_CFLAGS) $(SERVER_SRC) -o $@

# Сборка клиента
$(CLIENT_BIN): $(CLIENT_SRC)
	$(CC) $(CLIENT_CFLAGS) $(CLIENT_SRC) -o $@

# Очистка
clean:
	rm -rf $(BIN_DIR)
