# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\HospitalQt_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\HospitalQt_autogen.dir\\ParseCache.txt"
  "HospitalQt_autogen"
  )
endif()
