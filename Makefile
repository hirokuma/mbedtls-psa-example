
TARGET=./tst
SRC=\
	test1.c \
	main.c
DEPEND=.depend

CFLAGS=-Wall --std=gnu99 -I${HOME}/.local/include
LDFLAGS=-L${HOME}/.local/lib -lmbedtls -lmbedx509 -lmbedcrypto

all: ${TARGET}

depend:
	gcc ${SRC} ${CFLAGS} -MM > ${DEPEND}

${TARGET}: ${DEPEND} ${SRC}
	gcc -o ${TARGET} ${SRC} ${CFLAGS} ${LDFLAGS}

leak:
	valgrind --tool=memcheck --leak-check=full ${TARGET}

clean:
	-rm -f ${TARGET} ${DEPEND}

-include ${DEPEND}
