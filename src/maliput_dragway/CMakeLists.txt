##############################################################################
# Sources
##############################################################################

set(SOURCES
  branch_point.cc
  junction.cc
  lane.cc
  road_geometry.cc
  segment.cc)

add_library(maliput_dragway ${SOURCES})

target_include_directories(maliput_dragway
  PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

target_link_libraries(maliput_dragway
  maliput::api
  maliput::common
  maliput::geometry_base
)

ament_target_dependencies(maliput_dragway
    "maliput"
)

##############################################################################
# Export
##############################################################################

install(
    TARGETS maliput_dragway
    EXPORT ${PROJECT_NAME}-targets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
)

ament_export_libraries(maliput_dragway)
