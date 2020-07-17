CC=tcc

all: bin/mycat bin/limit bin/true bin/false

bin/mycat: cat.c
	$(CC) -o bin/mycat cat.c

bin/limit: limit.c
	$(CC) -o bin/limit limit.c

bin/true: true.c
	$(CC) -o bin/true true.c

bin/false: false.c
	$(CC) -o bin/false false.c

$(shell mkdir -p bin)

