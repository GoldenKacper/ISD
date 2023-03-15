 
INPUT_FILES = main.c neural_network.c
CFLAGS = -Wall -Wpedantic -Werror -Wno-unused-variable
OUTPUT_NAME = main.out

all: clean
	gcc $(INPUT_FILES) $(CFLAGS) -o $(OUTPUT_NAME)

clean:
	rm -f $(OUTPUT_NAME) 

run: all
	@echo "\nRunning program:"
	@echo "------------------------"
	@./$(OUTPUT_NAME)
	@echo "------------------------"