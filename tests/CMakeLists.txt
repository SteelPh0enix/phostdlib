file(GLOB test_sources RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.cpp")

foreach(test ${test_sources})
    # MESSAGE(STATUS "File: ${test}")
    string(REGEX REPLACE ".cpp\$" "" test_output "${test}")
    set(test_name "${test_output}")

    # MESSAGE(STATUS "Output file: ${test_exe}")
    message(STATUS "Adding ${test} as ${test_name}")
    include_directories(phostdlib_include_dir)
    add_executable("${test_name}" "${test}")
endforeach()