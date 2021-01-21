DIR_SRC := src
DIR_BIN := bin

BINS := $(patsubst ${DIR_SRC}/%.c,${DIR_BIN}/%,$(wildcard ${DIR_SRC}/*.c))

CC := gcc
FLAGS := -g -Wall --pedantic

all: ${BINS}

${DIR_BIN}/% : ${DIR_SRC}/%.c | ${DIR_BIN}
	${CC} $^ -o $@ ${FLAGS}

${DIR_BIN} :
	mkdir -p $@
