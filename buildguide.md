# Build guide
Install wsl2
In wsl2:
* sudo apt install gcc g++ make cmake ninja-build
* git clone https://github.com/drh/lcc.git
* cd lcc
* mkdir bin
* export BUILDDIR=./bin
* make HOSTFILE=./etc/linux.c lcc
* To ~/.bashrc add this line:
* export PATH=$PATH:~/lcc/bin/
* cd to TF2003-qvm directory
* chmod +x build_cmake.sh
* Now you can build with:
* ./build_cmake.sh
* Build output is in:
* _cmake falder