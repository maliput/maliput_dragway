set(TEST_UTILS_SOURCES
  fixtures.cc)

add_library(dragway_test_utilities ${TEST_UTILS_SOURCES})

target_include_directories(
  dragway_test_utilities
  PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

ament_target_dependencies(dragway_test_utilities
  "maliput"
  "maliput-dragway"
)

target_link_libraries(dragway_test_utilities
  dragway
  maliput::api
)

install(
    TARGETS dragway_test_utilities
    EXPORT ${PROJECT_NAME}-targets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)

ament_export_libraries(dragway_test_utilities)
