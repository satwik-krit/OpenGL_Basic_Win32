rem @echo off
set ABSPATH=C:\Users\sande\Documents\Projects\OpenGL\Basic_Win32\
echo "Cleaning up..."
mkdir bin
del .\bin\main.exe
set include=%ABSPATH%include\
set output=%ABSPATH%bin\
set source=%ABSPATH%src\
echo "Compiling..."
gcc -I%include% %source%*.c -luser32 -lgdi32 -lopengl32 -g -o %output%main.exe
echo "Running..."
.\bin\main
