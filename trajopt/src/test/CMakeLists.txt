
include_directories(
  ${CMAKE_SOURCE_DIR}/lib
)

add_executable(test_viewer test_viewer.cpp)
target_link_libraries(test_viewer  osgviewer)