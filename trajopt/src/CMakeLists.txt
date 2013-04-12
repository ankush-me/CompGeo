include_directories(
  ${CMAKE_SOURCE_DIR}/ext
  ${CMAKE_SOURCE_DIR}/src
)


add_definitions(-DEIGEN_DEFAULT_TO_ROW_MAJOR)

set(OpenRAVE_BOTH_LIBRARIES ${OpenRAVE_LIBRARIES} ${OpenRAVE_CORE_LIBRARIES})
add_subdirectory(osgviewer)
