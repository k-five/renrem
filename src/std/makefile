build:
	rm -f renrem
	g++ renrem_std.cpp -o renrem -std=c++11 -Wall -Weffc++ -Wextra -pedantic -Wfatal-errors -pedantic-errors -O2

install:
	sudo mv renrem /usr/bin/

test:
	./renrem

clear:
	rm -f *.o *~
