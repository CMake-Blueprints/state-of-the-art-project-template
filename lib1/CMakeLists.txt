add_library(${PROJECT_NAME}_Lib1)
add_library(${PROJECT_NAME}::Lib1 ALIAS ${PROJECT_NAME}_Lib1)
set(INCLUDE_PREFIX ${PROJECT_NAME}/lib1)

set(EXPORT_HEADER ${CMAKE_CURRENT_BINARY_DIR}/include/${INCLUDE_PREFIX}/lib1_export.h)
include(GenerateExportHeader)
generate_export_header(${PROJECT_NAME}_Lib1
  EXPORT_FILE_NAME ${EXPORT_HEADER}
  EXPORT_MACRO_NAME LIB1_EXPORT
)

target_sources(${PROJECT_NAME}_Lib1 PUBLIC
  FILE_SET HEADERS
  BASE_DIRS include ${CMAKE_CURRENT_BINARY_DIR}/include
  FILES

  # TODO: Add public headers here
  include/${INCLUDE_PREFIX}/lib1.h
  ${EXPORT_HEADER}
)
target_sources(${PROJECT_NAME}_Lib1 PRIVATE

  # TODO: Add private headers and sources here
  src/lib1_private.h
  src/lib1.cpp
)
target_compile_features(${PROJECT_NAME}_Lib1 PUBLIC
  cxx_std_17
)
target_include_directories(${PROJECT_NAME}_Lib1
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include/${INCLUDE_PREFIX}>
    $<INSTALL_INTERFACE:include>
  PRIVATE
    src
)
set_target_properties(${PROJECT_NAME}_Lib1 PROPERTIES
  VERSION ${PROJECT_VERSION}
  SOVERSION ${PROJECT_VERSION_MAJOR}
  OUTPUT_NAME lib1
  PREFIX ""
  EXPORT_NAME Lib1
)

# Testing
if(BUILD_TESTING OR ${PROJECT_NAME}_BUILD_TESTING)
  add_subdirectory(tests)
endif()

# Installation
include(GNUInstallDirs)
string(APPEND CMAKE_INSTALL_LIBDIR /$<CONFIG>)
string(APPEND CMAKE_INSTALL_BINDIR /$<CONFIG>)
install(TARGETS ${PROJECT_NAME}_Lib1
  EXPORT ${PROJECT_NAME}Targets
  FILE_SET HEADERS
)

# Install PDB files for MSVC debug builds
if(MSVC)
  if(BUILD_SHARED_LIBS)
    install(FILES $<TARGET_PDB_FILE:${PROJECT_NAME}_Lib1>
      DESTINATION ${CMAKE_INSTALL_BINDIR} OPTIONAL
    )
  else()
    install(DIRECTORY $<TARGET_FILE_DIR:${PROJECT_NAME}_Lib1>/
      DESTINATION ${CMAKE_INSTALL_LIBDIR} FILES_MATCHING PATTERN "*.pdb"
    )
  endif()
endif()
