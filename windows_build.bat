del bomberman.exe
rmdir "_build/Debug"
mkdir _build
cmake -H. -B_build
cd _build
cmake --build .
cd ..
copy "_build\Debug\bomberman.exe" "."