FROM ubuntu:latest

RUN apt-get update && apt-get install -y --fix-missing \
	build-essential \
	valgrind

WORKDIR /home/masha/Documents/SSA_pr6

