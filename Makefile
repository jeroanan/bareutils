CC=tcc

all: bin/mycat bin/limit

bin/mycat: cat.c
	$(CC) -o bin/mycat cat.c

bin/limit: limit.c
	$(CC) -o bin/limit limit.c

$(shell mkdir -p bin)

