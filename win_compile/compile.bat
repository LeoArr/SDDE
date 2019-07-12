@echo off
REM -mwindows 
g++ -std=c++17 -Wall -g "%cd%\src\*.cpp" -I./include -I./win_include -L./lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -o ./win_bin/test
IF %ERRORLEVEL% NEQ 0 EXIT
xcopy "%cd%\assets\*" "%cd%\win_bin\assets\" /E /Y