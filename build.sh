clear
rm -rf build
rm compile_commands.json
mkdir build
cmake -DCMAKE_BUILD_TYPE=Debug -S . -B build -G "Ninja"
cd build
bear -- ninja
cd ..
ln -s build/compile_commands.json compile_commands.json
