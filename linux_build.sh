rm -f bomberman
mkdir _build
cmake -H. -B_build
cd _build && make && cp bomberman ..