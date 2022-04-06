$(CC) := cc
WARN := -Wall -Wextra -Werror -pedantic
STD := -std=c99
INCLUDE := -Iinclude -Ilib/mpg/include
LIBS := -Llib/mpg/bin -lmpg

TARGET := bin/proj
OBJECTS := obj/main.o

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS) bin
	$(CC) $(WARN) $(STD) $(LIBS) $(OBJECTS) -o $(TARGET)

obj/%.o: src/%.c obj
	$(CC) $(WARN) $(STD) $(INCLUDE) -c $< -o $@

obj:
	mkdir -p obj

bin:
	@mkdir -p bin

clean:
	rm -rf $(TARGET) obj
