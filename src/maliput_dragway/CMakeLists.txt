##############################################################################
# Sources
##############################################################################

set(SOURCES
  branch_point.cc
  junction.cc
  lane.cc
  road_geometry.cc
  road_network_builder.cc
  segment.cc)

add_library(maliput_dragway ${SOURCES})

add_library(maliput_dragway::maliput_dragway ALIAS maliput_dragway)

set_target_properties(maliput_dragway
  PROPERTIES
    OUTPUT_NAME maliput_dragway
)

target_include_directories(maliput_dragway
  PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(maliput_dragway
  maliput::api
  maliput::base
  maliput::common
  maliput::geometry_base
)

##############################################################################
# Export
##############################################################################

install(
  TARGETS maliput_dragway
  EXPORT ${PROJECT_NAME}-targets
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)
