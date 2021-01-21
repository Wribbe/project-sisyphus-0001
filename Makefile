DIR_SRC := src
DIR_BIN := bin

BINS := $(patsubst ${DIR_SRC}/%.c,${DIR_BIN}/%,$(wildcard ${DIR_SRC}/*.c))

CC := gcc
FLAGS := -g -Wall -pedantic -lX11

all: ${BINS}

${DIR_BIN}/% : ${DIR_SRC}/%.c Makefile | ${DIR_BIN}
	${CC} $(filter %.c %.h,$^) -o $@ ${FLAGS}

${DIR_BIN} :
	mkdir -p $@
