CC=tcc
INCSRC=$(wildcard inc/*.c)
OBJECTS=$(pathsubt %.c, %.o, $(INCSRC))

all: bin/mycat bin/echo bin/endlimit bin/false bin/limit bin/true 

bin/mycat: cat.c
	$(CC) -o bin/mycat cat.c

bin/echo: echo.c
	$(CC) -o bin/echo echo.c

bin/endlimit: obj/endlimit.o obj/string_to_number.o
	$(CC) -o bin/endlimit obj/endlimit.o obj/string_to_number.o

obj/endlimit.o: endlimit.c
	$(CC) -c -o obj/endlimit.o endlimit.c

bin/false: false.c
	$(CC) -o bin/false false.c

bin/limit: obj/limit.o obj/string_to_number.o
	$(CC) -o bin/limit obj/limit.o obj/string_to_number.o

obj/limit.o: limit.c
	$(CC) -c -o obj/limit.o limit.c

bin/true: true.c
	$(CC) -o bin/true true.c

obj/string_to_number.o: inc/string_to_number.c
	$(CC) -c -o obj/string_to_number.o inc/string_to_number.c

clean: 
	rm -rf bin/ obj/

$(shell mkdir -p bin)
$(shell mkdir -p obj)

