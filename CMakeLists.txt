cmake_minimum_required(VERSION 3.23)

project(OpenTS VERSION 0.2.0 LANGUAGES C CXX)

set(OPENTS_VERSION_PRERELEASE "")
option(OPENTS_OFFICIAL_BUILD "Build as an official release of the declared version" OFF)
option(OPENTS_EXPERIMENTAL_CLANG_CL "Build with clang-cl using the MSVC ABI" OFF)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

string(TOLOWER "${CMAKE_CXX_COMPILER_ARCHITECTURE_ID}" OPENTS_ARCH)
if(NOT OPENTS_ARCH)
    set(OPENTS_ARCH "unknown")
endif()

# Only enable RC language on Windows
if(WIN32 AND NOT ANDROID)
    enable_language(RC)
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(OPENTS_GAME_DIR "${CMAKE_SOURCE_DIR}/Run" CACHE PATH "Tiberian Sun game data directory")

set(OPENTS_GENERATED_DIR "${CMAKE_BINARY_DIR}/generated")
set(OPENTS_VERSION_HEADER "${OPENTS_GENERATED_DIR}/opents_version.h")
set(OPENTS_STAMP_HEADER "${OPENTS_GENERATED_DIR}/opents_build.h")
file(MAKE_DIRECTORY "${OPENTS_GENERATED_DIR}")

set(OPENTS_STAMP_ARGS
    "-DOPENTS_VERSION_MAJOR=${PROJECT_VERSION_MAJOR}"
    "-DOPENTS_VERSION_MINOR=${PROJECT_VERSION_MINOR}"
    "-DOPENTS_VERSION_PATCH=${PROJECT_VERSION_PATCH}"
    "-DOPENTS_VERSION_PRERELEASE=${OPENTS_VERSION_PRERELEASE}"
    "-DOPENTS_OFFICIAL_BUILD=${OPENTS_OFFICIAL_BUILD}"
    "-DOPENTS_SOURCE_DIR=${CMAKE_SOURCE_DIR}"
    "-DOPENTS_VERSION_HEADER=${OPENTS_VERSION_HEADER}"
    "-DOPENTS_STAMP_HEADER=${OPENTS_STAMP_HEADER}"
    "-DOPENTS_ARCH=${OPENTS_ARCH}"
    -P "${CMAKE_SOURCE_DIR}/cmake/GitStamp.cmake"
)

execute_process(COMMAND ${CMAKE_COMMAND} ${OPENTS_STAMP_ARGS})

add_custom_target(OpenTSBuildStamp ALL
    COMMAND ${CMAKE_COMMAND} ${OPENTS_STAMP_ARGS}
    COMMENT "Stamping the build identity"
    VERBATIM
)

add_subdirectory(thirdparty)
add_subdirectory(code)
add_subdirectory(code/language)

# Android: skip tests - they pull MSVC flags and Windows-only code
if(NOT ANDROID)
    enable_testing()
    add_subdirectory(tests)
endif()
