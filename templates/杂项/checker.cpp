@echo off
:loop
gen.exe
b_s.exe
b.exe
fc test.out test.ans
if not errorlevel 1 goto loop