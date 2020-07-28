CC=tcc
INCSRC=$(wildcard inc/*.c)
OBJECTS=$(pathsubt %.c, %.o, $(INCSRC))
SRCDIR=src

all: bin/mycat \
	bin/echo \
	bin/endlimit \
	bin/false \
	bin/groups \
	bin/id \
	bin/limit \
	bin/ls \
	bin/md5sum \
	bin/nl \
	bin/tac \
	bin/true \
	bin/whoami

bin/mycat: $(SRCDIR)/cat.c
	$(CC) -o bin/mycat $(SRCDIR)/cat.c

bin/echo: $(SRCDIR)/echo.c
	$(CC) -o bin/echo $(SRCDIR)/echo.c

bin/endlimit: obj/endlimit.o obj/string_to_number.o obj/process_stdin.o
	$(CC) -o bin/endlimit obj/endlimit.o obj/string_to_number.o obj/process_stdin.o

obj/endlimit.o: $(SRCDIR)/endlimit.c
	$(CC) -c -o obj/endlimit.o $(SRCDIR)/endlimit.c

bin/false: $(SRCDIR)/false.c
	$(CC) -o bin/false $(SRCDIR)/false.c

bin/groups: $(SRCDIR)/groups.c
	$(CC) -o bin/groups $(SRCDIR)/groups.c

bin/id: $(SRCDIR)/id.c
	$(CC) -o bin/id $(SRCDIR)/id.c

bin/limit: obj/limit.o obj/string_to_number.o obj/process_stdin.o
	$(CC) -o bin/limit obj/limit.o obj/string_to_number.o obj/process_stdin.o

obj/limit.o: $(SRCDIR)/limit.c
	$(CC) -c -o obj/limit.o $(SRCDIR)/limit.c

bin/ls: $(SRCDIR)/ls.c
	$(CC) -o bin/ls $(SRCDIR)/ls.c

bin/md5sum: obj/md5sum.o obj/WjCryptLib_Md5.o obj/process_stdin.o
	$(CC) -o bin/md5sum obj/md5sum.o obj/WjCryptLib_Md5.o obj/process_stdin.o

obj/md5sum.o: $(SRCDIR)/md5sum.c
	$(CC) -c -o obj/md5sum.o $(SRCDIR)/md5sum.c

obj/WjCryptLib_Md5.o: lib/WjCryptLib/WjCryptLib_Md5.c
	$(CC) -c -o obj/WjCryptLib_Md5.o lib/WjCryptLib/WjCryptLib_Md5.c

bin/nl: obj/nl.o obj/process_stdin.o
	$(CC) -o bin/nl obj/nl.o obj/process_stdin.o

obj/nl.o: $(SRCDIR)/nl.c
	$(CC) -c -o obj/nl.o $(SRCDIR)/nl.c

bin/tac: obj/tac.o obj/process_stdin.o
	$(CC) -o bin/tac obj/tac.o obj/process_stdin.o

obj/tac.o: $(SRCDIR)/tac.c
	$(CC) -c -o obj/tac.o $(SRCDIR)/tac.c

bin/true: $(SRCDIR)/true.c
	$(CC) -o bin/true $(SRCDIR)/true.c

bin/whoami: $(SRCDIR)/whoami.c
	$(CC) -o bin/whoami $(SRCDIR)/whoami.c

obj/string_to_number.o: $(SRCDIR)/inc/string_to_number.c
	$(CC) -c -o obj/string_to_number.o $(SRCDIR)/inc/string_to_number.c

obj/process_stdin.o: $(SRCDIR)/inc/process_stdin.c
	$(CC) -c -o obj/process_stdin.o $(SRCDIR)/inc/process_stdin.c

clean: 
	rm -rf bin/ obj/

$(shell mkdir -p bin)
$(shell mkdir -p obj)
