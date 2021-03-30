hello_world: main.o print.o
	g++ -o hello_world main.o print.o
main.o: main.cpp
	g++ -c main.cpp
print.o: print.cpp
	g++ -c print.cpp
clean:
	rm hello_world  main.o print.o

