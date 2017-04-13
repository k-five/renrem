build:
	rm -f renrem
	g++  renrem_boost.cpp -o renrem \
	     -std=c++11 -Wall -Weffc++ -Wextra -pedantic -Wfatal-errors -pedantic-errors \
	     -L/usr/local/lib -I/usr/local/include/boost \
	     -l boost_regex

install:
	sudo mv renrem /usr/bin/

test:
	./renrem

clear:
	rm -f *.o *~
