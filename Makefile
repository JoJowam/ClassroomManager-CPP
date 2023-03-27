CC=g++ # compilador, troque para gcc se preferir utilizar C
CFLAGS=-std=c++17 -Wall -Wextra # compiler flags, troque o que quiser, exceto bibliotecas externas
EXEC=./main # nome do executavel que sera gerado, nao troque

$(EXEC): main.cpp menu.o
	$(CC) $(CFLAGS) main.cpp bin/menu.o bin/system.o bin/classroom.o bin/course.o bin/manager.o bin/professor.o bin/student.o bin/person.o -o $(EXEC)

menu.o: src/menu.cpp system.o
	$(CC) $(CFLAGS) -c src/menu.cpp -o bin/menu.o

system.o: src/system.cpp course.o classroom.o professor.o manager.o student.o
	$(CC) $(CFLAGS) -c src/system.cpp -o bin/system.o

classroom.o: src/classroom.cpp course.o
	$(CC) $(CFLAGS) -c src/classroom.cpp -o bin/classroom.o

course.o: src/course.cpp classroom.o professor.o student.o
	$(CC) $(CFLAGS) -c src/course.cpp -o bin/course.o

manager.o: src/manager.cpp person.o
	$(CC) $(CFLAGS) -c src/manager.cpp -o bin/manager.o

professor.o: src/professor.cpp person.o course.o
	$(CC) $(CFLAGS) -c src/professor.cpp -o bin/professor.o

student.o: src/student.cpp person.o course.o
	$(CC) $(CFLAGS) -c src/student.cpp -o bin/student.o

person.o: src/person.cpp 
	$(CC) $(CFLAGS) -c src/person.cpp -o bin/person.o

clean: # remove todos os arquivos temporarios que forem gerados pela compilacao
	rm -rf 
