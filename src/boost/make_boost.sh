#!/usr/bin/bash

cp ../src/std/renrem_std.cpp renrem_boost.cpp
perl -i -lpe 's/regex(?=>)/regex.hpp/; s/std::(?=(regex|regex_search|regex_replace|smatch))/boost::/g' renrem_boost.cpp
