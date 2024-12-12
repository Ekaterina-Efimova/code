all: clean install build run

build:
	mvn clean package

run:
	mvn exec:java -Dexec.mainClass="Rogue.App"

clean:
	mvn clean

install:
	mvn install

install-java:
	sudo apt update
	sudo apt install default-jdk

install-maven:
	sudo apt install maven

.PHONY: all build run clean install test