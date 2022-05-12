dir_guard = @mkdir -p $(@D)

BUILD_DIR = build

hello = ${BUILD_DIR}/hello
fct = ${BUILD_DIR}/fahrenheit-celsius-table

all: ${hello} ${fct}
.PHONY: all


${hello}: hello.c
	$(dir_guard)
	cc $< -o $@

${fct}: fahrenheit-celsius-table.c
	$(dir_guard)
	cc $< -o $@

clean:
	rm -rv build
