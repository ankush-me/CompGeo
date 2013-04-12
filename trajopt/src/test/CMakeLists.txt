
include_directories(
  ${CMAKE_SOURCE_DIR}/lib/osgviewer
  ${CMAKE_SOURCE_DIR}/lib
)

message(STATUS "************** LIBRARY OUTPUT PATH ${CMAKE_LIBRARY_PATH}")
link_directories(${CMAKE_LIBRARY_PATH})


add_executable(test_viewer test_viewer.cpp)
target_link_libraries(test_viewer  osgviewer)