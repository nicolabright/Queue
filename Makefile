all:    queue.c
	gcc -g queue.c -o queue.exe
	@ cls
	@ queue.exe

clean:
	del queue.exe 2> nul
