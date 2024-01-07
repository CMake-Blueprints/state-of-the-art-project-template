add_library(${PROJECT_NAME}_Lib2 INTERFACE)
add_library(${PROJECT_NAME}::Lib2 ALIAS ${PROJECT_NAME}_Lib2)

target_sources(${PROJECT_NAME}_Lib2 INTERFACE
  FILE_SET HEADERS
  BASE_DIRS include
  FILES
    include/${PROJECT_NAME}/lib2/lib2.h
)

target_compile_features(${PROJECT_NAME}_Lib1 PUBLIC
  cxx_std_17
)
target_include_directories(${PROJECT_NAME}_Lib2 INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)
set_target_properties(${PROJECT_NAME}_Lib2 PROPERTIES
  EXPORT_NAME Lib2
)

# Testing
if(BUILD_TESTING OR ${PROJECT_NAME}_BUILD_TESTING)
  add_subdirectory(tests)
endif()

# Installation
include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}_Lib2
  EXPORT ${PROJECT_NAME}Targets
  FILE_SET HEADERS
)
