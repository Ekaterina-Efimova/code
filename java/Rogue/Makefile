all: build run clean

build:
	docker build -t rogue .

run: 
	docker run --rm -it rogue

clean:
	docker rmi rogue

.PHONY: all build run