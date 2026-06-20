@echo off
cd src
for %%f in (*.cpp) do (
    echo Compiling %%f
    g++ -std=c++17 %%f -o %%~nf.exe -lws2_32
)
echo Done.
