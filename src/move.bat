@echo off
if not exist "..\include" (
    mkdir "..\include"
)
move *.h "..\include\"
echo All .h files have been moved to the "include" directory.