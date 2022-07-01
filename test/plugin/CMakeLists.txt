find_package(ament_cmake_gtest REQUIRED)

ament_add_gtest(road_network_plugin road_network_plugin_test.cc)

macro(add_dependencies_to_test target)
    if (TARGET ${target})

      target_include_directories(${target}
        PRIVATE
          ${PROJECT_SOURCE_DIR}/include
      )

      # To avoid a false positive when running ubsan the symbols must be exported
      # See https://stackoverflow.com/questions/57361776/use-ubsan-with-dynamically-loaded-shared-libraries
      set_target_properties(${target}
        PROPERTIES
          ENABLE_EXPORTS ON
      )

      set(ROAD_NETWORK_PLUGIN ${CMAKE_INSTALL_PREFIX}/lib/maliput_plugins/)
      target_compile_definitions(${target}
        PRIVATE
          DEF_ROAD_NETWORK_PLUGIN="${ROAD_NETWORK_PLUGIN}"
      )

      target_link_libraries(${target}
          maliput_dragway::maliput_dragway
          maliput::plugin
          maliput::test_utilities
      )
    endif()
endmacro()

add_dependencies_to_test(road_network_plugin)
