find_package(ament_cmake_gtest REQUIRED)
find_package(ament_cmake_pytest REQUIRED)

ament_add_gtest(dragway_test dragway_test.cc)

macro(add_dependencies_to_test target)
    if (TARGET ${target})

      target_include_directories(${target}
        PRIVATE
          ${PROJECT_SOURCE_DIR}/include
      )

      ament_target_dependencies(${target}
        "maliput"
      )

      target_link_libraries(${target}
          maliput::maliput_test_utilities
          maliput_dragway::maliput_dragway
      )

    endif()
endmacro()

add_dependencies_to_test(dragway_test)

# TODO(francocipollone): Improve this check by wrapping ament_add_pytest_test() function.
# When sanitizers are activated python scripts are disabled.
if (NOT ${SANITIZERS})
  ament_add_pytest_test(dragway_pytest
    dragway_test.py
    # Avoid pytest from importing the module stub
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  )
endif()

