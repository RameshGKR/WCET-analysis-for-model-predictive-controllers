
      echo "Should be ran in 'x64 Native Tools Command Prompt for VS'"
      cmake -G "Visual Studio 16 2019" -A x64 -B build
      cmake --build build --config Release
      cmake --install build --prefix .
      