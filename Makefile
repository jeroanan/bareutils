CC=tcc

all: bin/mycat bin/echo bin/endlimit bin/false bin/limit bin/true 

bin/mycat: cat.c
	$(CC) -o bin/mycat cat.c

bin/echo: echo.c
	$(CC) -o bin/echo echo.c

bin/endlimit: endlimit.c
	$(CC) -o bin/endlimit endlimit.c

bin/false: false.c
	$(CC) -o bin/false false.c

bin/limit: limit.c
	$(CC) -o bin/limit limit.c

bin/true: true.c
	$(CC) -o bin/true true.c

clean: 
	rm -rf bin/

$(shell mkdir -p bin)

