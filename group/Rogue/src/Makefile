all: clean install build run

build:
	mvn clean package

run:
	mvn exec:java -Dexec.mainClass="Rogue.App"

clean:
	mvn clean

install:
	mvn nstall

.PHONY: all build run clean install test
