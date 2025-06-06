#################################################################################
#
# CMake configuration for GEOS benchmarks/operation/predicate tests
#
# Copyright (C) 2017 Mateusz Loskot <mateusz@loskot.net>
#
# This is free software; you can redistribute and/or modify it under
# the terms of the GNU Lesser General Public Licence as published
# by the Free Software Foundation.
# See the COPYING file for more information.
#
#################################################################################
add_executable(perf_interiorpoint_area InteriorPointAreaPerfTest.cpp)
target_link_libraries(perf_interiorpoint_area geos)

add_executable(perf_unaryunion_segments UnaryUnionSegmentsPerfTest.cpp)
target_link_libraries(perf_unaryunion_segments geos)

if (BUILD_BENCHMARKS)

add_executable(stress_orientation OrientationIndexStressTest.cpp)
target_link_libraries(stress_orientation geos)

if (benchmark_FOUND)
    add_executable(perf_orientation OrientationIndexPerfTest.cpp
            ${PROJECT_SOURCE_DIR}/src/algorithm/CGAlgorithmsDD.cpp
            ${PROJECT_SOURCE_DIR}/src/math/DD.cpp)
    target_include_directories(perf_orientation PUBLIC
            $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
            $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>)
    target_link_libraries(perf_orientation PRIVATE
            benchmark::benchmark geos_cxx_flags)

    add_executable(perf_line_intersector LineIntersectorPerfTest.cpp)
    target_include_directories(perf_line_intersector PUBLIC
            $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
            $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
            $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/benchmarks>)
    target_link_libraries(perf_line_intersector PRIVATE
            benchmark::benchmark geos)

    add_executable(perf_voronoi VoronoiPerfTest.cpp)
    target_include_directories(perf_voronoi PUBLIC
            $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
            $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/benchmarks>
            $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>)
    target_link_libraries(perf_voronoi PRIVATE
            benchmark::benchmark geos)
else()
  MESSAGE(WARNING "Unable to find google benchmarks library!")
  MESSAGE(WARNING "  Some benchmarks will not be built!")
  MESSAGE(WARNING "  See https://github.com/google/benchmark")
endif()

endif()

add_subdirectory(locate)
