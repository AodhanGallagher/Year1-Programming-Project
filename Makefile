CC=gcc
CCFLAGS=-g -std=c99 -Wall
MODULES=pgmRead.o pgmWrite.o
MAINS=pgmEcho.o pgmComp.o pgma2b.o pgmb2a.o pgmReduce.o pgmTile.o pgmAssemble.o
TARGETS=pgmEcho pgmComp pgma2b pgmb2a pgmReduce pgmTile pgmAssemble

all: ${TARGETS}

clean:
		rm ${TARGETS} ${MAINS} ${MODULES} *.o

pgmEcho:	pgmEcho.o ${MODULES}
		${CC}	${CCFLAGS}	-o pgmEcho	pgmEcho.o ${MODULES}

pgmComp:	pgmComp.o ${MODULES}
		${CC}	${CCFLAGS}	-o pgmComp	pgmComp.o ${MODULES}

pgma2b:	pgma2b.o ${MODULES}
		${CC}	${CCFLAGS}	-o pgma2b	pgma2b.o ${MODULES}

pgmb2a:	pgmb2a.o ${MODULES}
		${CC}	${CCFLAGS}	-o pgmb2a	pgmb2a.o ${MODULES}

pgmReduce:	pgmReduce.o ${MODULES}
		${CC}	${CCFLAGS}	-o pgmReduce	pgmReduce.o ${MODULES}

pgmTile:	pgmTile.o ${MODULES}
		${CC}	${CCFLAGS}	-o pgmTile	pgmTile.o ${MODULES}

pgmAssemble:	pgmAssemble.o ${MODULES}
		${CC}	${CCFLAGS}	-o pgmAssemble	pgmAssemble.o ${MODULES}

pgmEcho.o:	pgmEcho.c	pgmDefinitions.h pgmStruct.h pgmRead.h pgmWrite.h
		${CC}	-c ${CCFLAGS}	-o pgmEcho.o	pgmEcho.c

pgmComp.o:	pgmComp.c	pgmDefinitions.h pgmStruct.h pgmRead.h
		${CC}	-c ${CCFLAGS}	-o pgmComp.o	pgmComp.c

pgma2b.o:	pgma2b.c	pgmDefinitions.h pgmStruct.h pgmRead.h pgmWrite.h
		${CC}	-c ${CCFLAGS}	-o pgma2b.o	pgma2b.c

pgmb2a.o:	pgmb2a.c	pgmDefinitions.h pgmStruct.h pgmRead.h pgmWrite.h
		${CC}	-c ${CCFLAGS}	-o pgmb2a.o	pgmb2a.c

pgmReduce.o:	pgmReduce.c	pgmDefinitions.h pgmStruct.h pgmRead.h pgmWrite.h
		${CC}	-c ${CCFLAGS}	-o pgmReduce.o	pgmReduce.c

pgmTile.o:	pgmTile.c	pgmDefinitions.h pgmStruct.h pgmRead.h pgmWrite.h
		${CC}	-c ${CCFLAGS}	-o pgmTile.o	pgmTile.c

pgmAssemble.o:	pgmAssemble.c	pgmDefinitions.h pgmStruct.h pgmRead.h pgmWrite.h
		${CC}	-c ${CCFLAGS}	-o pgmAssemble.o	pgmAssemble.c

pgmRead.o:	pgmRead.c	pgmDefinitions.h pgmStruct.h
		${CC}	-c ${CCFLAGS}	-o pgmRead.o	pgmRead.c

pgmWrite.o:	pgmWrite.c	pgmDefinitions.h pgmStruct.h
		${CC}	-c ${CCFLAGS}	-o pgmWrite.o	pgmWrite.c