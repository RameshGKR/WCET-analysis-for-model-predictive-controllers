
      cmake -DCMAKE_INSTALL_PREFIX=. -B build
      cmake --build build --config Release
      cmake --install build --prefix .
      