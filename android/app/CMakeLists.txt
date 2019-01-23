cmake_minimum_required(VERSION 3.4.1)

set( PROJECT_ROOT "${CMAKE_SOURCE_DIR}/../.." )
set( SUPPORT_LIB_ROOT "${PROJECT_ROOT}/../react-native-cpp-support/support-lib" )

SET(OPENSSL_ROOT_DIR /Users/andreysaleba/projects/OpenSSL-for-Android-Prebuilt/openssl-1.0.2)
SET(OPENSSL_LIBRARIES_DIR "${OPENSSL_ROOT_DIR}/${ANDROID_ABI}/lib")
SET(OPENSSL_INCLUDE_DIR ${OPENSSL_ROOT_DIR}/include)
SET(OPENSSL_LIBRARIES "ssl" "crypto")

file( GLOB JNI_CODE "src/main/cpp/*.cpp" "src/main/cpp/gen/*.cpp" )
file( GLOB PROJECT_CODE "${PROJECT_ROOT}/cpp/*.cpp" "${PROJECT_ROOT}/cpp/gen/*.cpp" )
file( GLOB PROJECT_HEADERS "${PROJECT_ROOT}/cpp/*.hpp" "${PROJECT_ROOT}/cpp/gen/*.hpp" )

file( GLOB DJINNI_CODE "${SUPPORT_LIB_ROOT}/cpp/*.cpp" "${SUPPORT_LIB_ROOT}/jni/*.cpp" )
file( GLOB DJINNI_HEADERS "${SUPPORT_LIB_ROOT}/cpp/*.hpp" "${SUPPORT_LIB_ROOT}/jni/*.hpp" )

LINK_DIRECTORIES(${OPENSSL_LIBRARIES_DIR} ${ZLIB_LIBRARIES_DIR})

include_directories(
    "${SUPPORT_LIB_ROOT}/cpp"
    "${SUPPORT_LIB_ROOT}/jni"
    "${PROJECT_ROOT}/cpp"
    "${PROJECT_ROOT}/cpp/gen"
    "${OPENSSL_INCLUDE_DIR}"
    )

add_library(libssl STATIC IMPORTED)
add_library(libcrypto STATIC IMPORTED)

add_library( # Sets the name of the library.
     native-lib

     # Sets the library as a shared library.
     SHARED

     ${JNI_CODE}
     ${DJINNI_CODE}
     ${DJINNI_HEADERS}
     ${PROJECT_CODE}
     ${PROJECT_HEADERS} )

set_target_properties( libssl PROPERTIES IMPORTED_LOCATION
                    ${OPENSSL_LIBRARIES_DIR}/libssl.a )
set_target_properties( libcrypto PROPERTIES IMPORTED_LOCATION
                   ${OPENSSL_LIBRARIES_DIR}/libcrypto.a )

target_link_libraries(native-lib PRIVATE libssl libcrypto)
