CFLAGS = -c `pkg-config glib-2.0 --cflags`
LFLAGS = `pkg-config glib-2.0 --libs`


all: programa-principal programa-testes

programa-principal.o: src/programa-principal.c
	gcc -I includes src/programa-principal.c $(CFLAGS)

parse_users.o: src/parse_users.c
	gcc -I includes src/parse_users.c $(CFLAGS)

parse_drivers.o: src/parse_drivers.c
	gcc -I includes src/parse_drivers.c $(CFLAGS)

parse_rides.o: src/parse_rides.c
	gcc -I includes src/parse_rides.c $(CFLAGS)

querys.o: src/querys.c
	gcc -I includes src/querys.c $(CFLAGS)

batch.o: src/batch.c
	gcc -I includes src/batch.c $(CFLAGS)
	
programa-testes.o: src/programa-testes.c
	gcc -I includes src/programa-testes.c $(CFLAGS)
	
programa-principal: programa-principal.o parse_users.o parse_drivers.o parse_rides.o querys.o batch.o
	gcc -I includes programa-principal.o parse_users.o parse_drivers.o parse_rides.o querys.o batch.o -o programa-principal $(LFLAGS)
	
programa-testes: programa-testes.o parse_users.o parse_drivers.o parse_rides.o querys.o batch.o
	gcc -I includes programa-testes.o parse_users.o parse_drivers.o parse_rides.o querys.o batch.o -o programa-testes $(LFLAGS)
	
clean:
	rm -rf *.o
