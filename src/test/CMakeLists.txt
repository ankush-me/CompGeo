add_executable(test_viewer test_viewer.cpp)
target_link_libraries(test_viewer  osgviewer utils convexhull)

add_executable(test_bst test_bst.cpp)

add_executable(test_comparator test_ind_comparator.cpp)
target_link_libraries(test_comparator  utils)