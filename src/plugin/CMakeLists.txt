##############################################################################
# Sources
##############################################################################

add_library(road_network road_network.cc)
add_library(maliput_dragway::road_network ALIAS road_network)

set_target_properties(road_network
  PROPERTIES
    OUTPUT_NAME maliput_dragway_road_network
)

target_link_libraries(road_network
  maliput::api
  maliput::base
  maliput::common
  maliput::plugin
  maliput_dragway::maliput_dragway
)

target_include_directories(road_network
  PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
    $<INSTALL_INTERFACE:include>
)

##############################################################################
# Export
##############################################################################

# Using a different location as this target is a dynamic library
# which will be loaded in runtime as a maliput plugin.
set(PLUGIN_INSTALL_DIR
    lib/maliput_plugins
)

install(
  TARGETS road_network
  EXPORT ${PROJECT_NAME}-targets
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION ${PLUGIN_INSTALL_DIR}
  RUNTIME DESTINATION bin
)
