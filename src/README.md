**Please read the entire of this context to prevent from some complier issues.**

**Firstly** I tested the binary code on both Linux and Windows with `gcc` complier. And the versions of `gcc 5.3.0` and lower, have some bugs on `regex` library. Therefore you should compile the code with `gcc 5.4.0` or upper. And if you are willing to use another compiler, please test the binary code carefully.
Although I added a macro to check the `gcc` version to prevent of using `gcc` lass than `5.4.0` but may you use another compiler.

**Secondly** with `boost::regex` on Linux you need to link the library like: `-l boost_regex` that the same flag is needed on Windows like: `-l boost_regex-gcc54-s-1_63`. Here on Windows, I have built the library manually so the link file is available where you compile the `boost` library.

**Thirdly** For optimization the code, you can use `-O2` flag. If you modified the code, it is better to use some warning flags like: `-Wall -Weffc++ -Wextra -pedantic -Wfatal-errors -pedantic-errors`

**Fourthly** you need to use `-std=c++11` flag, as well.

- - - 

# Some tips:

[How to Install boost on Ubuntu?](http://stackoverflow.com/questions/12578499/how-to-install-boost-on-ubuntu)

[boost Getting Started on Windows](http://www.boost.org/doc/libs/1_63_0/more/getting_started/windows.html)

[boost library installation](https://theboostcpplibraries.com/introduction-installation)

[the same regex but different results on Linux and Windows only C++](http://stackoverflow.com/questions/42627957/the-same-regex-but-different-results-on-linux-and-windows-only-c)

