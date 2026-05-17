.PHONY: build

build:
	mkdir -p build && cd build && cmake .. && make
	npx tsc

run:
	./build/resource_viewer
