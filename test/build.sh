mkdir -p build
cmake -Bbuild -H.
make -C build
cp -rf res build
