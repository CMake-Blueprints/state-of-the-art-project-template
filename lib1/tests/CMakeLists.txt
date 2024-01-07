include_directories($<TARGET_PROPERTY:${PROJECT_NAME}_Lib1,INCLUDE_DIRECTORIES>)
add_compile_definitions(${PROJECT_NAME}_Lib1_EXPORTS)

add_executable(${PROJECT_NAME}_Lib1Test ut.cpp $<TARGET_OBJECTS:${PROJECT_NAME}_Lib1>)
add_test(NAME ${PROJECT_NAME}_Lib1Test COMMAND ${PROJECT_NAME}_Lib1Test)
