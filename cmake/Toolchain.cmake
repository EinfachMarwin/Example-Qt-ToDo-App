# Bundled toolchain files for Qt and VCPKG

# if (WIN32 OR DEFINED QT_TOOLCHAIN_FILE )
#     if (NOT DEFINED QT_TOOLCHAIN_FILE)
#         message(SEND_ERROR "Please set QT_TOOLCHAIN_FILE to the CMake toolchain file of your Qt installation")
#     else ()
#         message(STATUS "Using Qt toolchain file: ${QT_TOOLCHAIN_FILE}")
#         include(${QT_TOOLCHAIN_FILE})
#     endif ()
# endif ()

if (NOT DEFINED VCPKG_ROOT AND DEFINED ENV{VCPKG_ROOT})
    set(VCPKG_ROOT $ENV{VCPKG_ROOT})
    message(STATUS "VCPKG_ROOT not set, using environment variable: ${VCPKG_ROOT}")
endif ()

set(ENV{VCPKG_DEFAULT_HOST_TRIPLET} "${VCPKG_TARGET_TRIPLET}")

if (DEFINED VCPKG_TOOLCHAIN_FILE)
    message(STATUS "Using vcpkg toolchain file: ${VCPKG_TOOLCHAIN_FILE}")
    include(${VCPKG_TOOLCHAIN_FILE})
elseif (NOT DEFINED VCPKG_ROOT)
    message(SEND_ERROR "Please set VCPKG_ROOT to the root of your vcpkg installation")
else ()
    message(STATUS "Using vcpkg root: ${VCPKG_ROOT}")

    set(VCPKG_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
    include(${VCPKG_TOOLCHAIN_FILE})
endif ()

set(CMAKE_TRY_COMPILE_PLATFORM_VARIABLES QT_TOOLCHAIN_FILE VCPKG_TOOLCHAIN_FILE)
