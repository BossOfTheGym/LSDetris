# TODO : add function to add executable

set(hello_world_sources main.cpp)
add_executable(hello_world ${hello_world_sources})
target_link_libraries(hello_world ${ALL_DEPS})
set_property(TARGET hello_world PROPERTY CXX_STANDART 20)

set(glfw_test_sources glfw_test/glfw_test.cpp)
add_executable(glfw_test ${glfw_test_sources})
target_link_libraries(glfw_test ${ALL_DEPS})
set_property(TARGET glfw_test PROPERTY CXX_STANDART 20)

set(audio_test_sources audio_test/audio_test.cpp)
add_executable(audio_test ${audio_test_sources})
target_link_libraries(audio_test ${ALL_DEPS})
set_property(TARGET audio_test PROPERTY CXX_STANDART 20)

populate_filters()