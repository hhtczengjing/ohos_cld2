# the minimum version of CMake.
cmake_minimum_required(VERSION 3.5.0)
project(myNpmLib)

set(NATIVERENDER_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

if(DEFINED PACKAGE_FIND_FILE)
    include(${PACKAGE_FIND_FILE})
endif()

include_directories(${NATIVERENDER_ROOT_PATH}
                    ${NATIVERENDER_ROOT_PATH}/include)

set(SELF_LIB_NAME cld2)
file(GLOB SELF_TEMP_SRC_FILES RELATIVE ${NATIVERENDER_ROOT_PATH} *.cc *.cpp *.h)
list(APPEND SELF_SRC_FILES ${SELF_TEMP_SRC_FILES})
add_library(${SELF_LIB_NAME} SHARED ${SELF_SRC_FILES})
target_link_libraries(${SELF_LIB_NAME} PUBLIC libace_napi.z.so libhilog_ndk.z.so)
target_link_libraries(${SELF_LIB_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../../libs/${OHOS_ARCH}/libcld2.a)
