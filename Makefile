# Makefile for building my_mp4_parser from my_mp4_parser.cpp

CXXFLAGS=-Wall -Wextra

my_mp4_parser: my_mp4_parser.o log.hpp buffer_utils.o
	g++ -o my_mp4_parser my_mp4_parser.o buffer_utils.o

my_mp4_parser.o: *.cpp *.hpp
	g++ $(CXXFLAGS) -c my_mp4_parser.cpp

buffer_utils.o: buffer_utils.cpp buffer_utils.hpp
	g++ $(CXXFLAGS) -c buffer_utils.cpp

clean:
	rm -f my_mp4_parser *.o

