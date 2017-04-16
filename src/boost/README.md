For using the `boost` version of the program, I have created a bash script that uses a simple **Perl** one-liner to create the appropriate `.cpp` file that can be complied with `boost::regex` library.
If you are wiling to do it by hand, you should modify all related things to `std::regex` to `boost::regex` and what you need is in the `make_boost.sh` such as `std::regex`, `std::regex_search`.
Also you should know about your installation library for the `boost` since may yours was different from mine.

Also the screen-shot below shows you how to use `make_boost.sh` and `makefile`

![screen-shot_make_boost.png](https://github.com/k-five/renrem/blob/master/screenshot/make_boost.png)