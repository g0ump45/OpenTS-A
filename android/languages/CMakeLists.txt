include(FetchContent)
foreach(feature OPENSSL LIBB2 LZ4 LZO LZMA ZSTD ZLIB BZip2 LIBXML2 EXPAT WIN32_XMLLITE PCREPOSIX PCRE2POSIX LIBGCC CNG TAR CPIO CAT UNZIP XATTR ACL ICONV TEST INSTALL)
    set(ENABLE_${feature} OFF CACHE BOOL "" FORCE)
endforeach()
set(ENABLE_WERROR OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
FetchContent_Declare(opents_archive
    URL https://codeload.github.com/libarchive/libarchive/tar.gz/refs/tags/v3.8.9
    URL_HASH SHA256=744346f6bca195c8f894f847bb32a16e9bcae6002624a58fadc81e80f595b3cb
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE)
FetchContent_MakeAvailable(opents_archive)
add_library(opents_language_archive SHARED archive_jni.cpp)
target_link_libraries(opents_language_archive PRIVATE archive_static)
