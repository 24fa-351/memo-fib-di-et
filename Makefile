fib: fib.c
	gcc -o fib.exe fib.c

clean:
	rm fib.exe

test: fib
	bash test.sh
