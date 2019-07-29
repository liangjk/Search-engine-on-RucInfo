1:lock.o function.o main.o
	g++ lock.o function.o main.o -o 1 -std=c++11 -lpthread
lock.o:lock.cpp lock.h
	g++ -c lock.cpp -std=c++11 -lpthread
function.o:function.cpp getinfo.h getpages.h lock.h
	g++ -c function.cpp -std=c++11 -lpthread
main.o:main.cpp getpages.h
	g++ -c main.cpp -std=c++11 -lpthread
clean:
	rm -rf *.o wget-log*
