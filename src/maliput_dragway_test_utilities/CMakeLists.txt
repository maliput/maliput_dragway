set(TEST_UTILS_SOURCES
  fixtures.cc)

add_library(maliput_dragway_test_utilities ${TEST_UTILS_SOURCES})

add_library(maliput_dragway::test_utilities ALIAS maliput_dragway_test_utilities)

target_include_directories(
  maliput_dragway_test_utilities
  PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

ament_target_dependencies(maliput_dragway_test_utilities
  "maliput"
)

target_link_libraries(maliput_dragway_test_utilities
  maliput::api
  maliput_dragway::maliput_dragway
)

install(
    TARGETS maliput_dragway_test_utilities
    EXPORT ${PROJECT_NAME}-targets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)

ament_export_libraries(maliput_dragway_test_utilities)
