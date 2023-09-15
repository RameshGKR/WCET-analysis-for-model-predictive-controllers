
      project(mpc)

      set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

      cmake_minimum_required(VERSION 3.0)

      message("If you get a complaint about missing libcasadi.lib, please copy the casadi.lib file to libcasadi.lib")
      set(CMAKE_PREFIX_PATH "C:/Users/wardg/UA/IMPACT/.venv/Lib/site-packages/casadi" ${CMAKE_PREFIX_PATH})
      find_package(casadi REQUIRED)

      add_library(mpc SHARED mpc.c)
      target_link_libraries(mpc casadi)

      install(TARGETS mpc RUNTIME DESTINATION . LIBRARY DESTINATION .)

      