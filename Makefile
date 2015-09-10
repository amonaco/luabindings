all:
	g++ host.cpp -o cpphost -llua
	gcc host.c -o chost -llua
clean:
	rm -f chost cpphost
