@echo off
"C:\Program Files (x86)\Dev-Cpp\MinGW64\bin\g++.exe" gap.cpp grader.cpp -o gap.exe -static -DLOCAL -g3 -Wl,--stack=1073741824 2> compile.log
type compile.log
del compile.log