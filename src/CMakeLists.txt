# TODO : add function to add executable

set(CMAKE_CXX_STANDARD 20)

set(hello_world_sources main.cpp)
add_executable(hello_world ${hello_world_sources})
target_link_libraries(hello_world ${ALL_DEPS})
set_property(TARGET hello_world PROPERTY CXX_STANDART 20)
set_property(TARGET hello_world PROPERTY CXX_STANDARD_REQUIRED ON)

set(glfw_test_sources glfw_test/glfw_test.cpp)
add_executable(glfw_test ${glfw_test_sources})
target_link_libraries(glfw_test ${ALL_DEPS})
set_property(TARGET glfw_test PROPERTY CXX_STANDART 20)
set_property(TARGET glfw_test PROPERTY CXX_STANDARD_REQUIRED ON)

set(audio_test_sources audio_test/audio_test.cpp)
add_executable(audio_test ${audio_test_sources})
target_link_libraries(audio_test ${ALL_DEPS})
set_property(TARGET audio_test PROPERTY CXX_STANDART 20)
set_property(TARGET audio_test PROPERTY CXX_STANDARD_REQUIRED ON)

populate_filters()