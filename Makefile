# Makefile for building my_mp4_parser from my_mp4_parser.cpp

CXXFLAGS=-Wall -Wextra

my_mp4_parser: my_mp4_parser.o
	g++ -o my_mp4_parser my_mp4_parser.o

my_mp4_parser.o: my_mp4_parser.cpp my_mp4_parser.hpp
	g++ $(CXXFLAGS) -c my_mp4_parser.cpp

clean:
	rm -f my_mp4_parser *.o

