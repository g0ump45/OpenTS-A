#
# ---------------------------------------------------------
# Gather the VQALib player files
# ---------------------------------------------------------
#
file(GLOB VQALIB_SRC CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
)

#
# ---------------------------------------------------------
# Create the VQALib player library
# ---------------------------------------------------------
#
message(STATUS "${PROJECT_NAME}: Creating 'VQALib' library...")

add_library(VQALib STATIC ${VQALIB_SRC})

target_compile_features(VQALib PRIVATE cxx_std_20)

set_target_properties(VQALib PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

# FIX: On Android, NEVER use MSVC flags from OPENTS_COMPILE_OPTIONS
if(ANDROID)
  set(_filtered_opts "")
  foreach(opt IN LISTS OPENTS_COMPILE_OPTIONS)
    if(NOT opt MATCHES "^/EHsc" AND NOT opt MATCHES "^/Zc" AND NOT opt MATCHES "^/fp" AND NOT opt MATCHES "^/W" AND NOT opt MATCHES "^/O" AND NOT opt MATCHES "^/MT" AND NOT opt MATCHES "^/Zi" AND NOT opt MATCHES "^/MP" AND NOT opt MATCHES "^/GR" AND NOT opt MATCHES "^/GF" AND NOT opt MATCHES "^/RTC" AND NOT opt MATCHES "^/arch" AND NOT opt MATCHES "^/Oy" AND NOT opt MATCHES "^/utf" AND NOT opt MATCHES "^/permissive")
      # Keep only non-MSVC options
      if(NOT opt MATCHES "^/.*")
        list(APPEND _filtered_opts ${opt})
      endif()
    endif()
  endforeach()
  # Add Android-safe options
  list(APPEND _filtered_opts -fexceptions -frtti)
  target_compile_options(VQALib PRIVATE ${_filtered_opts})
else()
  target_compile_options(VQALib PRIVATE ${OPENTS_COMPILE_OPTIONS})
endif()

target_compile_definitions(VQALib PRIVATE
    WIN32
    _WINDOWS
    NOMINMAX
)

target_include_directories(VQALib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_include_directories(VQALib PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/..")

#
# ---------------------------------------------------------
# Visual Studio filters
# ---------------------------------------------------------
#
foreach(f ${VQALIB_SRC})
    if(f MATCHES "\\.(c|cpp)$")
        source_group("Source Files" FILES ${f})
    elseif(f MATCHES "\\.h$")
        source_group("Header Files" FILES ${f})
    endif()
endforeach()
