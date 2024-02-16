@echo off
set ABSPATH=C:\Users\sande\Documents\Projects\OpenGL\Basic_Win32\
echo "Cleaning up..."
del main.exe
echo "Compiling..."
gcc win32_base.c -luser32 -lgdi32 -lopengl32 -g -o main.exe
echo "Running..."
main
