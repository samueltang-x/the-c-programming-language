dir_guard=@mkdir -p $(@D)

TARGAT =  ./build/day-of-year
SRC = day-of-year.c

$(TARGAT): $(SRC)
	$(dir_guard)
	gcc $(SRC) -o $(TARGAT)
clean:
	rm -fv $(TARGAT)
