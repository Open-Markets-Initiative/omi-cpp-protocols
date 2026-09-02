cmake_minimum_required(VERSION 3.20)
project(omi_cpp_protocols CXX)

# The modern parser uses C++23 (std::byteswap, etc.); a C++23 compiler (GCC 15+) is required.
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Each translation unit under checks/ includes a protocol's aggregating headers, so
# compiling it fires the generated layout static_asserts. A clean build is the gate:
# it proves every parser (structs, types, messages) is well-formed and self-consistent.
add_library(protocols_check OBJECT
  checks/iex_iexequities_deep_iextp_v1.06_advanced.cpp
  checks/iex_iexequities_deep_iextp_v1.06_modern.cpp
  checks/iex_iexequities_deep_iextp_v1.08_advanced.cpp
  checks/iex_iexequities_deep_iextp_v1.08_modern.cpp
  checks/iex_iexequities_deep_snap_v1.6_advanced.cpp
  checks/iex_iexequities_deep_snap_v1.6_modern.cpp
  checks/iex_iexequities_deepplus_iextp_v1.01_advanced.cpp
  checks/iex_iexequities_deepplus_iextp_v1.01_modern.cpp
  checks/iex_iexequities_deepplus_iextp_v1.04_advanced.cpp
  checks/iex_iexequities_deepplus_iextp_v1.04_modern.cpp
  checks/iex_iexequities_deepplus_snap_v1.05_advanced.cpp
  checks/iex_iexequities_deepplus_snap_v1.05_modern.cpp
  checks/iex_iexequities_tops_iextp_v1.56_advanced.cpp
  checks/iex_iexequities_tops_iextp_v1.56_modern.cpp
  checks/iex_iexequities_tops_iextp_v1.64_advanced.cpp
  checks/iex_iexequities_tops_iextp_v1.64_modern.cpp
  checks/iex_iexequities_tops_iextp_v1.66_advanced.cpp
  checks/iex_iexequities_tops_iextp_v1.66_modern.cpp
  checks/iex_iexequities_tops_snap_v1.6_advanced.cpp
  checks/iex_iexequities_tops_snap_v1.6_modern.cpp
)

# Programs under executables/ — one per protocol. Each reads the parser published under
# cpp/, included by a repository-root-relative path, so there is only ever one copy of a
# protocol's parser in the tree.
add_executable(statistics_iex_iexequities_deep_iextp_v1.06 executables/statistics/iex/iexequities/deep/iextp/v1.06/main.cpp)
target_include_directories(statistics_iex_iexequities_deep_iextp_v1.06 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/statistics/iex/iexequities/deep/iextp/v1.06)
add_executable(extractor_iex_iexequities_deep_iextp_v1.06 executables/extractor/iex/iexequities/deep/iextp/v1.06/main.cpp)
target_include_directories(extractor_iex_iexequities_deep_iextp_v1.06 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/extractor/iex/iexequities/deep/iextp/v1.06)
add_executable(dump_iex_iexequities_deep_iextp_v1.06 executables/dump/iex/iexequities/deep/iextp/v1.06/main.cpp)
target_include_directories(dump_iex_iexequities_deep_iextp_v1.06 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/dump/iex/iexequities/deep/iextp/v1.06)
add_executable(statistics_iex_iexequities_deep_iextp_v1.08 executables/statistics/iex/iexequities/deep/iextp/v1.08/main.cpp)
target_include_directories(statistics_iex_iexequities_deep_iextp_v1.08 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/statistics/iex/iexequities/deep/iextp/v1.08)
add_executable(extractor_iex_iexequities_deep_iextp_v1.08 executables/extractor/iex/iexequities/deep/iextp/v1.08/main.cpp)
target_include_directories(extractor_iex_iexequities_deep_iextp_v1.08 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/extractor/iex/iexequities/deep/iextp/v1.08)
add_executable(dump_iex_iexequities_deep_iextp_v1.08 executables/dump/iex/iexequities/deep/iextp/v1.08/main.cpp)
target_include_directories(dump_iex_iexequities_deep_iextp_v1.08 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/dump/iex/iexequities/deep/iextp/v1.08)
add_executable(statistics_iex_iexequities_deep_snap_v1.6 executables/statistics/iex/iexequities/deep/snap/v1.6/main.cpp)
target_include_directories(statistics_iex_iexequities_deep_snap_v1.6 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/statistics/iex/iexequities/deep/snap/v1.6)
add_executable(extractor_iex_iexequities_deep_snap_v1.6 executables/extractor/iex/iexequities/deep/snap/v1.6/main.cpp)
target_include_directories(extractor_iex_iexequities_deep_snap_v1.6 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/extractor/iex/iexequities/deep/snap/v1.6)
add_executable(dump_iex_iexequities_deep_snap_v1.6 executables/dump/iex/iexequities/deep/snap/v1.6/main.cpp)
target_include_directories(dump_iex_iexequities_deep_snap_v1.6 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/dump/iex/iexequities/deep/snap/v1.6)
add_executable(statistics_iex_iexequities_deepplus_iextp_v1.01 executables/statistics/iex/iexequities/deepplus/iextp/v1.01/main.cpp)
target_include_directories(statistics_iex_iexequities_deepplus_iextp_v1.01 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/statistics/iex/iexequities/deepplus/iextp/v1.01)
add_executable(extractor_iex_iexequities_deepplus_iextp_v1.01 executables/extractor/iex/iexequities/deepplus/iextp/v1.01/main.cpp)
target_include_directories(extractor_iex_iexequities_deepplus_iextp_v1.01 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/extractor/iex/iexequities/deepplus/iextp/v1.01)
add_executable(dump_iex_iexequities_deepplus_iextp_v1.01 executables/dump/iex/iexequities/deepplus/iextp/v1.01/main.cpp)
target_include_directories(dump_iex_iexequities_deepplus_iextp_v1.01 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/dump/iex/iexequities/deepplus/iextp/v1.01)
add_executable(statistics_iex_iexequities_deepplus_iextp_v1.04 executables/statistics/iex/iexequities/deepplus/iextp/v1.04/main.cpp)
target_include_directories(statistics_iex_iexequities_deepplus_iextp_v1.04 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/statistics/iex/iexequities/deepplus/iextp/v1.04)
add_executable(extractor_iex_iexequities_deepplus_iextp_v1.04 executables/extractor/iex/iexequities/deepplus/iextp/v1.04/main.cpp)
target_include_directories(extractor_iex_iexequities_deepplus_iextp_v1.04 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/extractor/iex/iexequities/deepplus/iextp/v1.04)
add_executable(dump_iex_iexequities_deepplus_iextp_v1.04 executables/dump/iex/iexequities/deepplus/iextp/v1.04/main.cpp)
target_include_directories(dump_iex_iexequities_deepplus_iextp_v1.04 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/dump/iex/iexequities/deepplus/iextp/v1.04)
add_executable(statistics_iex_iexequities_deepplus_snap_v1.05 executables/statistics/iex/iexequities/deepplus/snap/v1.05/main.cpp)
target_include_directories(statistics_iex_iexequities_deepplus_snap_v1.05 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/statistics/iex/iexequities/deepplus/snap/v1.05)
add_executable(extractor_iex_iexequities_deepplus_snap_v1.05 executables/extractor/iex/iexequities/deepplus/snap/v1.05/main.cpp)
target_include_directories(extractor_iex_iexequities_deepplus_snap_v1.05 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/extractor/iex/iexequities/deepplus/snap/v1.05)
add_executable(dump_iex_iexequities_deepplus_snap_v1.05 executables/dump/iex/iexequities/deepplus/snap/v1.05/main.cpp)
target_include_directories(dump_iex_iexequities_deepplus_snap_v1.05 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/dump/iex/iexequities/deepplus/snap/v1.05)
add_executable(statistics_iex_iexequities_tops_iextp_v1.56 executables/statistics/iex/iexequities/tops/iextp/v1.56/main.cpp)
target_include_directories(statistics_iex_iexequities_tops_iextp_v1.56 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/statistics/iex/iexequities/tops/iextp/v1.56)
add_executable(extractor_iex_iexequities_tops_iextp_v1.56 executables/extractor/iex/iexequities/tops/iextp/v1.56/main.cpp)
target_include_directories(extractor_iex_iexequities_tops_iextp_v1.56 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/extractor/iex/iexequities/tops/iextp/v1.56)
add_executable(dump_iex_iexequities_tops_iextp_v1.56 executables/dump/iex/iexequities/tops/iextp/v1.56/main.cpp)
target_include_directories(dump_iex_iexequities_tops_iextp_v1.56 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/dump/iex/iexequities/tops/iextp/v1.56)
add_executable(statistics_iex_iexequities_tops_iextp_v1.64 executables/statistics/iex/iexequities/tops/iextp/v1.64/main.cpp)
target_include_directories(statistics_iex_iexequities_tops_iextp_v1.64 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/statistics/iex/iexequities/tops/iextp/v1.64)
add_executable(extractor_iex_iexequities_tops_iextp_v1.64 executables/extractor/iex/iexequities/tops/iextp/v1.64/main.cpp)
target_include_directories(extractor_iex_iexequities_tops_iextp_v1.64 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/extractor/iex/iexequities/tops/iextp/v1.64)
add_executable(dump_iex_iexequities_tops_iextp_v1.64 executables/dump/iex/iexequities/tops/iextp/v1.64/main.cpp)
target_include_directories(dump_iex_iexequities_tops_iextp_v1.64 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/dump/iex/iexequities/tops/iextp/v1.64)
add_executable(statistics_iex_iexequities_tops_iextp_v1.66 executables/statistics/iex/iexequities/tops/iextp/v1.66/main.cpp)
target_include_directories(statistics_iex_iexequities_tops_iextp_v1.66 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/statistics/iex/iexequities/tops/iextp/v1.66)
add_executable(extractor_iex_iexequities_tops_iextp_v1.66 executables/extractor/iex/iexequities/tops/iextp/v1.66/main.cpp)
target_include_directories(extractor_iex_iexequities_tops_iextp_v1.66 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/extractor/iex/iexequities/tops/iextp/v1.66)
add_executable(dump_iex_iexequities_tops_iextp_v1.66 executables/dump/iex/iexequities/tops/iextp/v1.66/main.cpp)
target_include_directories(dump_iex_iexequities_tops_iextp_v1.66 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/dump/iex/iexequities/tops/iextp/v1.66)
add_executable(statistics_iex_iexequities_tops_snap_v1.6 executables/statistics/iex/iexequities/tops/snap/v1.6/main.cpp)
target_include_directories(statistics_iex_iexequities_tops_snap_v1.6 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/statistics/iex/iexequities/tops/snap/v1.6)
add_executable(extractor_iex_iexequities_tops_snap_v1.6 executables/extractor/iex/iexequities/tops/snap/v1.6/main.cpp)
target_include_directories(extractor_iex_iexequities_tops_snap_v1.6 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/extractor/iex/iexequities/tops/snap/v1.6)
add_executable(dump_iex_iexequities_tops_snap_v1.6 executables/dump/iex/iexequities/tops/snap/v1.6/main.cpp)
target_include_directories(dump_iex_iexequities_tops_snap_v1.6 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/dump/iex/iexequities/tops/snap/v1.6)
# Packet-driven tests: each reads captures from the packet corpus, walks every transport
# payload with the generated iterator, and requires the message the capture is named for.
# Point OMI_PACKETS_DIR at the corpus checkout to run them:
#
#   cmake -S . -B build -DOMI_PACKETS_DIR=/path/to/ScaledPackets
#   cmake --build build --parallel && ctest --test-dir build
set(OMI_PACKETS_DIR "" CACHE PATH "Packet corpus checkout holding the capture samples")

if(OMI_PACKETS_DIR)
  enable_testing()

  add_executable(iex_iexequities_deep_iextp_v1.06_test tests/messages/iex_iexequities_deep_iextp_v1.06.cpp)
  target_include_directories(iex_iexequities_deep_iextp_v1.06_test PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap)
  add_test(NAME iex_iexequities_deep_iextp_v1.06 COMMAND iex_iexequities_deep_iextp_v1.06_test)
  set_tests_properties(iex_iexequities_deep_iextp_v1.06 PROPERTIES ENVIRONMENT "OMI_PACKETS_DIR=${OMI_PACKETS_DIR}")

  add_executable(iex_iexequities_deepplus_iextp_v1.01_test tests/messages/iex_iexequities_deepplus_iextp_v1.01.cpp)
  target_include_directories(iex_iexequities_deepplus_iextp_v1.01_test PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap)
  add_test(NAME iex_iexequities_deepplus_iextp_v1.01 COMMAND iex_iexequities_deepplus_iextp_v1.01_test)
  set_tests_properties(iex_iexequities_deepplus_iextp_v1.01 PROPERTIES ENVIRONMENT "OMI_PACKETS_DIR=${OMI_PACKETS_DIR}")

  add_executable(iex_iexequities_tops_iextp_v1.56_test tests/messages/iex_iexequities_tops_iextp_v1.56.cpp)
  target_include_directories(iex_iexequities_tops_iextp_v1.56_test PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap)
  add_test(NAME iex_iexequities_tops_iextp_v1.56 COMMAND iex_iexequities_tops_iextp_v1.56_test)
  set_tests_properties(iex_iexequities_tops_iextp_v1.56 PROPERTIES ENVIRONMENT "OMI_PACKETS_DIR=${OMI_PACKETS_DIR}")

  add_executable(iex_iexequities_tops_iextp_v1.64_test tests/messages/iex_iexequities_tops_iextp_v1.64.cpp)
  target_include_directories(iex_iexequities_tops_iextp_v1.64_test PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap)
  add_test(NAME iex_iexequities_tops_iextp_v1.64 COMMAND iex_iexequities_tops_iextp_v1.64_test)
  set_tests_properties(iex_iexequities_tops_iextp_v1.64 PROPERTIES ENVIRONMENT "OMI_PACKETS_DIR=${OMI_PACKETS_DIR}")
endif()