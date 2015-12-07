all: anagram anagramx
anagram: anagram.cpp validity.hpp palindrome.hpp check.hpp find.hpp help.hpp
	g++ -std=c++11 -o anagram anagram.cpp
anagramx: anagramx.cpp validity.hpp find.hpp
	g++ -std=c++11 $(shell pkg-config --cflags --libs Qt5Widgets) -o anagramx anagramx.cpp

install: anagram anagramx
	install -vm 0755 {anagram,anagramx} /usr/local/bin
	mkdir -vp /usr/local/share/anagram/dictionary
	cp dictionary/* /usr/local/share/anagram/dictionary
