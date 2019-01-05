proj1_20181655 : proj1_20181655.o login.o product.o users.o
	gcc -w -W -o proj1_20181655 proj1_20181655.o login.o product.o users.o

proj1_20181655.o : users.h login.h product.h proj1_20181655.c
	gcc -w -W -c -o proj1_20181655.o proj1_20181655.c

login.o : login.h users.h login.c
	gcc -w -W -c -o login.o login.c

product.o : product.h users.h product.c
	gcc -w -W -c -o product.o product.c

users.o : users.h users.c
	gcc -w -W -c -o users.o users.c

clean :
	rm -f *.o
	rm -f proj1_20181655
