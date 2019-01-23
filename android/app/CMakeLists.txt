cmake_minimum_required(VERSION 3.4.1)

set( PROJECT_ROOT "${CMAKE_SOURCE_DIR}/../.." )
set( SUPPORT_LIB_ROOT "${PROJECT_ROOT}/../react-native-cpp-support/support-lib" )

file( GLOB JNI_CODE "src/main/cpp/*.cpp" "src/main/cpp/gen/*.cpp" )
file( GLOB PROJECT_CODE "${PROJECT_ROOT}/cpp/*.cpp" "${PROJECT_ROOT}/cpp/gen/*.cpp" )
file( GLOB PROJECT_HEADERS "${PROJECT_ROOT}/cpp/*.hpp" "${PROJECT_ROOT}/cpp/gen/*.hpp" )

file( GLOB DJINNI_CODE "${SUPPORT_LIB_ROOT}/cpp/*.cpp" "${SUPPORT_LIB_ROOT}/jni/*.cpp" )
file( GLOB DJINNI_HEADERS "${SUPPORT_LIB_ROOT}/cpp/*.hpp" "${SUPPORT_LIB_ROOT}/jni/*.hpp" )

include_directories(
    "${SUPPORT_LIB_ROOT}/cpp"
    "${SUPPORT_LIB_ROOT}/jni"
    "${PROJECT_ROOT}/cpp"
    "${PROJECT_ROOT}/cpp/gen"
    )

add_library( # Sets the name of the library.
     native-lib

     # Sets the library as a shared library.
     SHARED

     ${JNI_CODE}
     ${DJINNI_CODE}
     ${DJINNI_HEADERS}
     ${PROJECT_CODE}
     ${PROJECT_HEADERS} )
