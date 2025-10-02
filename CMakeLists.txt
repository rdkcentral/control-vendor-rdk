# SPDX-License-Identifier: Apache-2.0
cmake_minimum_required(VERSION 3.0)

set(PROJECTLIBNAME "ctrlm-cpc")
set(MAJOR_VERSION 1)
set(MINOR_VERSION 0)
set(PROJECT_VERSION "${MAJOR_VERSION}.${MINOR_VERSION}.0")

project(${PROJECTLIBNAME} VERSION ${PROJECT_VERSION} DESCRIPTION "Vendor CPC Library - Dummy" LANGUAGES CXX)

if(NOT CMAKE_BUILD_TYPE)
    message(STATUS "No build type selected, default to Release")
    set(CMAKE_BUILD_TYPE Release)
endif()

option(CREATE_SHARED_LIB "Create shared library" ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/")

find_package(PkgConfig REQUIRED)
find_package(IARMBus REQUIRED)

pkg_check_modules(GLIB REQUIRED glib-2.0)
pkg_check_modules(SAFEC REQUIRED libsafec)

include_directories(${GLIB_INCLUDE_DIRS} ${IARMBUS_INCLUDE_DIRS} ${SAFEC_INCLUDE_DIRS})

include(GNUInstallDirs)

set(SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/ctrlm_vendor_network_factory.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ctrlm_rf4ce_voice_packet_analysis.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/irdb/ctrlm_irdb_factory.cpp
)

if(CREATE_SHARED_LIB)
    add_library(${PROJECTLIBNAME} SHARED ${SOURCE_FILES})
else()
    add_library(${PROJECTLIBNAME} STATIC ${SOURCE_FILES})
endif()

target_link_libraries(${PROJECTLIBNAME} ${GLIB_LIBRARIES} ${SAFEC_LIBRARIES})
target_compile_options(${PROJECTLIBNAME} PRIVATE ${GLIB_CFLAGS_OTHER} ${SAFEC_CFLAGS_OTHER})

set_target_properties(${PROJECTLIBNAME} PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${MAJOR_VERSION}
)

install(TARGETS ${PROJECTLIBNAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
