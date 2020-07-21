CC=tcc
INCSRC=$(wildcard inc/*.c)
OBJECTS=$(pathsubt %.c, %.o, $(INCSRC))
SRCDIR=src

all: bin/mycat \
	bin/echo \
	bin/endlimit \
	bin/false \
	bin/id \
	bin/limit \
	bin/ls \
	bin/nl \
	bin/tac \
	bin/true \
	bin/whoami

bin/mycat: $(SRCDIR)/cat.c
	$(CC) -o bin/mycat $(SRCDIR)/cat.c

bin/echo: $(SRCDIR)/echo.c
	$(CC) -o bin/echo $(SRCDIR)/echo.c

bin/endlimit: obj/endlimit.o obj/string_to_number.o
	$(CC) -o bin/endlimit obj/endlimit.o obj/string_to_number.o

obj/endlimit.o: $(SRCDIR)/endlimit.c
	$(CC) -c -o obj/endlimit.o $(SRCDIR)/endlimit.c

bin/false: $(SRCDIR)/false.c
	$(CC) -o bin/false $(SRCDIR)/false.c

bin/id: $(SRCDIR)/id.c
	$(CC) -o bin/id $(SRCDIR)/id.c

bin/limit: obj/limit.o obj/string_to_number.o
	$(CC) -o bin/limit obj/limit.o obj/string_to_number.o

obj/limit.o: $(SRCDIR)/limit.c
	$(CC) -c -o obj/limit.o $(SRCDIR)/limit.c

bin/ls: $(SRCDIR)/ls.c
	$(CC) -o bin/ls $(SRCDIR)/ls.c

bin/nl: $(SRCDIR)/nl.c
	$(CC) -o bin/nl $(SRCDIR)/nl.c

bin/tac: $(SRCDIR)/tac.c
	$(CC) -o bin/tac $(SRCDIR)/tac.c

bin/true: $(SRCDIR)/true.c
	$(CC) -o bin/true $(SRCDIR)/true.c

bin/whoami: $(SRCDIR)/whoami.c
	$(CC) -o bin/whoami $(SRCDIR)/whoami.c

obj/string_to_number.o: $(SRCDIR)/inc/string_to_number.c
	$(CC) -c -o obj/string_to_number.o $(SRCDIR)/inc/string_to_number.c

clean: 
	rm -rf bin/ obj/

$(shell mkdir -p bin)
$(shell mkdir -p obj)

