project("main")
enable_language(C CXX ASM_MASM)

file(GLOB MAIN_SOURCE_FILES
    "source/*.*"
    "utility/*.*"
    "utility/logger/*.*"
    "utility/memory/*.*"
    "utility/memory/signatures/*.*"
    "utility/invoker/*.*"
)

include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/)

add_definitions(-D_CRT_SECURE_NO_WARNINGS)
add_library(${PROJECT_NAME} SHARED ${MAIN_SOURCE_FILES})