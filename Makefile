CXX=g++
CC=$(CXX)
CFLAGS=-Wall -Werror -Wextra -pedantic -pedantic-errors -std=c++11 -g -O2 
MY_CFLAGS=-I/usr/include -I/usr/include/openssl
LIBS= -lPocoFoundation -lPocoNet -L/usr/ssl/lib -lcurlpp -lcrypto -L/usr/bin/X11/curl -lcurl

all: awsv4

awsv4: awsv4.o main2.o awsv4.hpp
	$(CXX) -o awsv4 main2.o awsv4.o $(LIBS)

lib: awsv4.o
	$(CXX) awsv4.o -shared -o libawsv4.so

awsv4.o: awsv4.cpp awsv4.hpp 
	$(CXX) -fPIC $(CFLAGS) $(MY_CFLAGS) -c awsv4.cpp

main2.o: main2.cpp awsv4.hpp
	$(CXX) $(CFLAGS) $(MY_CFLAGS) -c main2.cpp

clean:
	rm -f *.o awsv4
