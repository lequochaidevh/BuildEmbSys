// build_guide.md

### Build module
```sh
cd ../core/vielog
cmake -B build -DCMAKE_INSTALL_PREFIX=/tmp/vielog-install
cmake --build build
cmake --install build
```
=> Todo: set default DCMAKE_INSTALL_PREFIX

### Build excute include module
```sh
cd ../core/vielog
cmake -B build -DCMAKE_INSTALL_PREFIX=/tmp/vielog-install
cmake --build build
```
