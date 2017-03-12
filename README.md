# renrem program utility  
renrem is an acronym for [ rename ] and [ remove ] task together.  
Since it uses regular expression to match a string, apart from renaming a file, can be used for removing a file. It also has contraction synopsis and both works together to avoid of using command-ling argument, that sometimes it annoys the user. Notice that for spelling your spell it: ren-rem.  

---


![00_title](https://github.com/k-five/renrem/blob/master/button/00_title.png)
![01_fast](https://github.com/k-five/renrem/blob/master/button/01_fast.png)
![02_portable](https://github.com/k-five/renrem/blob/master/button/02_portable.png)
![03_colorize](https://github.com/k-five/renrem/blob/master/button/03_colorize.png)
![04_changeable](https://github.com/k-five/renrem/blob/master/button/04_changeable.png)
![05_index](https://github.com/k-five/renrem/blob/master/button/05_index.png)
![06_lightweight](https://github.com/k-five/renrem/blob/master/button/06_lightweight.png)
![07_leading](https://github.com/k-five/renrem/blob/master/button/07_leading.png)
![99_copyright](https://github.com/k-five/renrem/blob/master/button/99_copyright.png)


---

## Fast:
Only C++ code and plus a little C  

## Portable:
Only the standard library:  
* std::iostream  
* std::regex  
* stdio.h  

## Colorize the output:
Using [ANCI escape code](https://en.wikipedia.org/wiki/ANSI_escape_code) for colorize the output for both match and substitute.  

## Changeable form std::regex to boost::regex:
Since C++ use [ECMAScript](https://www.ecma-international.org/publications/standards/Ecma-262.htm) 262 if you are willing to use almost PCRE feature your can modify the code to boost::regex easly.  

## Index-match ( new feature ):
A great new feature that helps you to substitute a match string as easy as possible.  

## Lightweight:
Less then 300 line of code.  

## Auto zero leading:
Counts each line and adds zero-leading if need.  

---


# License:  
[GPL3](https://www.gnu.org/licenses/gpl-3.0.en.html)  
