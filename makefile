socketserver socketclient: socketserver.c socketclient.c
	gcc -g -o socketserver socketserver.c
	gcc -g -o socketclient socketclient.c


clean:
	rm socketclient socketserver 
