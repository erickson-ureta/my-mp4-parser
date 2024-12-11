# Makefile for building my_mp4_parser from my_mp4_parser.cpp

my_mp4_parser: my_mp4_parser.cpp
	g++ -o my_mp4_parser my_mp4_parser.cpp -Wall -Wextra

clean:
	rm -f my_mp4_parser

