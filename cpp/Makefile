# Компилятор и флаги
CXX := g++
CXXFLAGS := -std=c++11 -Wall -Wextra -O2

# Директории
BIN_DIR := bin
SRC_DIR := .

# Все цели
TARGETS := $(BIN_DIR)/z1 $(BIN_DIR)/z2 $(BIN_DIR)/z3 $(BIN_DIR)/z4 $(BIN_DIR)/z5 \
           $(BIN_DIR)/z6a $(BIN_DIR)/z6 $(BIN_DIR)/z7

# Объектные файлы
OBJS := z1.o z2.o z3.o z4.o z5.o z6.o z6a.o z7.o \
        stack.o set.o lfu.o hashtabledouble.o hashtablecuckoo.o

# Основная цель
all: $(BIN_DIR) $(TARGETS)

# Создание директории
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Правила для исполняемых файлов
$(BIN_DIR)/z1: z1.o stack.o
	$(CXX) $^ -o $@

$(BIN_DIR)/z2: z2.o set.o
	$(CXX) $^ -o $@

$(BIN_DIR)/z3: z3.o set.o
	$(CXX) $^ -o $@

$(BIN_DIR)/z4: z4.o
	$(CXX) $^ -o $@

$(BIN_DIR)/z5: z5.o hashtabledouble.o
	$(CXX) $^ -o $@

$(BIN_DIR)/z6: z6.o hashtabledouble.o
	$(CXX) $^ -o $@

$(BIN_DIR)/z6a: z6a.o hashtabledouble.o hashtablecuckoo.o
	$(CXX) $^ -o $@

$(BIN_DIR)/z7: z7.o lfu.o
	$(CXX) $^ -o $@

# Общее правило для объектных файлов
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Зависимости для объектных файлов
stack.o: stack.cpp stack.h
set.o: set.cpp set.h
lfu.o: lfu.cpp lfu.h
hashtabledouble.o: hashtabledouble.cpp hashtabledouble.h
hashtablecuckoo.o: hashtablecuckoo.cpp hashtablecuckoo.h

# Очистка
clean:
	rm -f $(OBJS)
	rm -rf $(BIN_DIR)

.PHONY: all clean