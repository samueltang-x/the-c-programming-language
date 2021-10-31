dir_guard = @mkdir -p $(@D)

TARGAT = ./build/hello
SRC = hello.c

$(TARGAT): $(SRC)
	$(dir_guard)
	gcc $(SRC) -o $(TARGAT)
clean:
	rm -fv $(TARGAT)
