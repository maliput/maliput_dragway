##############################################################################
# Sources
##############################################################################

add_library(dragway_road_network dragway_road_network.cc)

set_target_properties(dragway_road_network
  PROPERTIES
    OUTPUT_NAME maliput_dragway_road_network
)

ament_target_dependencies(maliput_dragway
    "maliput"
)

target_link_libraries(dragway_road_network
  maliput::api
  maliput::common
  maliput::base
  maliput_dragway::maliput_dragway
)

target_include_directories(dragway_road_network
  PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

##############################################################################
# Export
##############################################################################

install(
  TARGETS dragway_road_network
  EXPORT ${PROJECT_NAME}-targets
  DESTINATION "${CMAKE_INSTALL_PREFIX}/../plugins"
)
