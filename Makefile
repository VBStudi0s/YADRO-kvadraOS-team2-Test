.PHONY: build

build:
	mkdir -p build && cd build && cmake .. && make

run:
	./build/resource_viewer
