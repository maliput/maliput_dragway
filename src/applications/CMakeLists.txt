add_executable(load_dragway_rn
  load_dragway_rn.cc)

ament_target_dependencies(load_dragway_rn
   "maliput"
)

target_link_libraries(load_dragway_rn
  gflags
  maliput::api
  maliput::common
  maliput::utilities
)

install(
  TARGETS load_dragway_rn
  EXPORT ${PROJECT_NAME}-targets
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)