
all:

	g++ -c *.cpp
	g++ -o epollSock *.o -lpthread
#261757

clean:
	rm -rf *.o
	rm epollSock

