
cmake_minimum_required(VERSION 2.8)
if(NOT DEFINED BOARDPORT)
  set(BOARDPORT "/dev/ttyACM0")
endif()

project(TDD_Arduino)

if(MSVC)
  add_definitions( -D_VARIADIC_MAX=10 -DGTEST_USE_OWN_TR1_TUPLE=0 )
endif()

if(ARDUINO_FOUND)
  include_directories( avr-stl/include )

  generate_arduino_firmware(gameoflife
      HDRS include/debug.h
      SRCS src/main.cpp src/gameoflife.cpp
      PORT ${BOARDPORT}
      BOARD uno
      )
else()
  enable_testing()
  add_subdirectory(gmock)
  include_directories(${gmock_SOURCE_DIR}/include
      ${gtest_SOURCE_DIR}/include
      ${CMAKE_SOURCE_DIR}
      ${CMAKE_BINARY_DIR}
      ${CMAKE_SOURCE_DIR}/ArduinoMock )


  # This is a hack to make Visual Studio build gtest correct.
  if(MSVC)
    foreach(flag_var CMAKE_C_FLAGS_DEBUG CMAKE_CXX_FLAGS_DEBUG
        CMAKE_C_FLAGS_RELEASE CMAKE_CXX_FLAGS_RELEASE CMAKE_C_FLAGS_MINSIZEREL
        CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_C_FLAGS_RELWITHDEBINFO
        CMAKE_CXX_FLAGS_RELWITHDEBINFO)

      string(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
      string(REGEX REPLACE "/MDd" "/MTd" ${flag_var} "${${flag_var}}")
    endforeach(flag_var)
    SET (CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG}" CACHE STRING "MSVC C Debug MT flags " FORCE)
    SET (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}" CACHE STRING "MSVC CXX Debug MT flags " FORCE)
    SET (CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE}" CACHE STRING "MSVC C Release MT flags " FORCE)
    SET (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}" CACHE STRING "MSVC CXX Release MT flags " FORCE)
    SET (CMAKE_C_FLAGS_MINSIZEREL "${CMAKE_C_FLAGS_MINSIZEREL}" CACHE STRING "MSVC C Debug MT flags " FORCE)
    SET (CMAKE_CXX_FLAGS_MINSIZEREL "${CMAKE_CXX_FLAGS_MINSIZEREL}" CACHE STRING "MSVC C Release MT flags " FORCE)
    SET (CMAKE_C_FLAGS_RELWITHDEBINFO "${CMAKE_C_FLAGS_RELWITHDEBINFO}" CACHE STRING "MSVC CXX Debug MT flags " FORCE)
    SET (CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO}" CACHE STRING "MSVC CXX Release MT flags " FORCE)
  endif()


#  add_executable(engine_test
#      engine.h
#      test/engine_test.cpp
#      ArduinoMock/arduino.cpp
#      )
#  target_link_libraries(engine_test gtest gmock gmock_main )
#  add_test(AllTestsInEngine engine_test  --gtest_color=on --gtest_output=xml)
#
#  add_custom_command(OUTPUT EngineMock.h
#      COMMAND ${gmock_SOURCE_DIR}/scripts/generator/gmock_gen.py ${CMAKE_SOURCE_DIR}/engine.h > EngineMock.h
#      DEPENDS ${CMAKE_SOURCE_DIR}/engine.h
#      )
#
#  add_executable(driver_test
#      driver.h
#      engine.h
#      EngineMock.h
#      test/driver_test.cpp
#      ArduinoMock/arduino.cpp
#      )
#  target_link_libraries(driver_test gtest gmock gmock_main )
#  add_test(AllTestsInDriver driver_test  --gtest_color=on --gtest_output=xml)


endif()

