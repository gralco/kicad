#
#  This program source code file is part of KICAD, a free EDA CAD application.
#
#  Copyright (C) 2007-2016 Kicad Developers, see AUTHORS.txt for contributors.
#
#  This program is free software; you can redistribute it and/or
#  modify it under the terms of the GNU General Public License
#  as published by the Free Software Foundation; either version 2
#  of the License, or (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program; if not, you may find one here:
#  http://www.gnu.org/licenses/old-licenses/gpl-2.0.html
#  or you may search the http://www.gnu.org website for the version 2 license,
#  or you may write to the Free Software Foundation, Inc.,
#  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
#

cmake_minimum_required( VERSION 2.8.12 FATAL_ERROR )
# because of http://public.kitware.com/Bug/view.php?id=10395

# See https://gitlab.kitware.com/cmake/cmake/issues/15943
# Remove as soon as 3.1 is minimum required version
if(POLICY CMP0025)
  cmake_policy(SET CMP0025 NEW) # CMake 3.0
endif()

project( kicad )

# Default to CMAKE_BUILD_TYPE = Release unless overridden on command line
# http://www.cmake.org/pipermail/cmake/2008-September/023808.html
if( DEFINED CMAKE_BUILD_TYPE )
    set( CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE} CACHE STRING "Set to either \"Release\" or \"Debug\"" )
else()
    set( CMAKE_BUILD_TYPE Release CACHE STRING "Set to either \"Release\" or \"Debug\"" )
endif()

include( GNUInstallDirs )

# Path to local CMake modules.
set( CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMakeModules )

#
# KiCad build options should be added below.
#
# If you add a new build option, please add it's state to the
# OnCopyVersionInfo() function in common/dialog_about/dialog_about.cpp
# so that build option settings can be included in bug reports.
#

option( USE_WX_GRAPHICS_CONTEXT
    "Use wxGraphicsContext for rendering (default OFF).  Warning, this is experimental" )

option( USE_WX_OVERLAY
    "Use wxOverlay: Always ON for MAC (default OFF).  Warning, this is experimental" )

option( KICAD_SCRIPTING
    "Build the Python scripting support inside KiCad binaries (default OFF)."
    ON )

option( KICAD_SCRIPTING_MODULES
    "Build native portion of the pcbnew Python module: _pcbnew.{pyd,so} for OS command line use of Python."
    ON )

option( KICAD_SCRIPTING_WXPYTHON
    "Build wxPython implementation for wx interface building in Python and py.shell (default OFF)."
    ON )

option( KICAD_SCRIPTING_ACTION_MENU
    "Build a tools menu with registred python plugins: actions plugins (default OFF)."
    )

option( KICAD_USE_OCE
    "Build tools and plugins related to OpenCascade Community Edition (default ON)"
    ON )

option( KICAD_USE_OCC
    "Build tools and plugins related to OpenCascade Technology (overrides KICAD_USE_OCE, default OFF)"
    OFF )

option( KICAD_INSTALL_DEMOS
    "Install kicad demos and examples (default ON)"
    ON )

# when option KICAD_SCRIPTING OR KICAD_SCRIPTING_MODULES is enabled:
# PYTHON_EXECUTABLE can be defined when invoking cmake
# ( use -DPYTHON_EXECUTABLE=<python path>/python.exe or python2 )
# when not defined by user, the default is python.exe under Windows and python2 for others
# python binary file should be is exec path.

# KICAD_SCRIPTING_MODULES requires KICAD_SCRIPTING enable it here if KICAD_SCRIPTING_MODULES is ON
if ( KICAD_SCRIPTING_MODULES AND NOT KICAD_SCRIPTING )
    message(STATUS "Changing KICAD_SCRIPTING to ON as needed by KICAD_SCRIPTING_MODULES")
    set ( KICAD_SCRIPTING ON )
endif()

# same with KICAD_SCRIPTING_ACTION_MENUS
if ( KICAD_SCRIPTING_ACTION_MENU AND NOT KICAD_SCRIPTING )
    message(STATUS "Changing KICAD_SCRIPTING to ON as needed by KICAD_SCRIPTING_ACTION_MENU")
    set ( KICAD_SCRIPTING ON )
endif()

option( BUILD_GITHUB_PLUGIN "Build the GITHUB_PLUGIN for pcbnew." ON )

option( KICAD_SPICE "Build Kicad with internal Spice simulator." ON )

# Global setting: exports are explicit
set( CMAKE_CXX_VISIBILITY_PRESET "hidden" )
set( CMAKE_VISIBILITY_INLINES_HIDDEN ON )


# Global setting: build everything position independent
set( CMAKE_POSITION_INDEPENDENT_CODE ON )


# Global setting: Use C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# CMP0063: CMake < 3.3 does not handle hidden visibility for static libraries,
# and 3.3 is backwards compatible when the minimum version is smaller than 3.3.
if( POLICY CMP0063 )
    cmake_policy( GET CMP0063 VISIBILITY_POLICY )
    if( VISIBILITY_POLICY STREQUAL NEW )
        message( WARNING "Compatibility code for CMake < 3.3 can be removed, search for CMP0063" )
    else()
        cmake_policy( SET CMP0063 NEW )
    endif()
else()
    if( CMAKE_CXX_COMPILE_OPTIONS_VISIBILITY AND NOT APPLE )
        set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_COMPILE_OPTIONS_VISIBILITY}hidden" )
    endif()
    if( CMAKE_CXX_COMPILE_OPTIONS_VISIBILITY_INLINES_HIDDEN AND NOT APPLE )
        set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_COMPILE_OPTIONS_VISIBILITY_INLINES_HIDDEN}" )
    endif()
endif()


# Add option to add user directories for linker, if any
LINK_DIRECTORIES( ${LINK_DIRECTORIES_PATH} )

if( UNIX )
    set( KICAD_USER_CONFIG_DIR $ENV{HOME} CACHE PATH "Location of user specific KiCad config files" )
elseif( MINGW )
    set( KICAD_USER_CONFIG_DIR $ENV{APPDATA} CACHE PATH "Location of user specific KiCad config files" )
endif()
mark_as_advanced( KICAD_USER_CONFIG_DIR )

# Set default data file path to CMAKE_INSTALL_PREFIX if it wasn't specified during the
# CMake configuration.  The value of DEFAULT_INSTALL_PATH is expanded in config.h and
# used in the source code to define the base path for kicad search paths and environment
# variables.
if( NOT DEFAULT_INSTALL_PATH )
    set( DEFAULT_INSTALL_PATH "${CMAKE_INSTALL_PREFIX}"
         CACHE
         PATH
         "Location of KiCad data files." )
endif()

message( STATUS "Kicad install dir: <${DEFAULT_INSTALL_PATH}>" )

# Generate build system specific header file.
include( PerformFeatureChecks )
perform_feature_checks()


# Workaround: CMake < 3.1 does not support CMAKE_CXX_STANDARD
if( NOT CMAKE_MINIMUM_REQUIRED_VERSION VERSION_LESS 3.1 )
    message( FATAL_ERROR "Remove compatibility code" )
endif()

if( CMAKE_VERSION VERSION_LESS 3.1 AND ( CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang" ) )
    include(CheckCXXCompilerFlag)

    CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)

    if(COMPILER_SUPPORTS_CXX11)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
    endif()
endif()


# Warn about missing override specifiers, if supported
if( CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang" )
    include(CheckCXXCompilerFlag)

    CHECK_CXX_COMPILER_FLAG("-Wsuggest-override" COMPILER_SUPPORTS_WSUGGEST_OVERRIDE)

    if(COMPILER_SUPPORTS_WSUGGEST_OVERRIDE)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wsuggest-override")
    endif()
endif()


# Warn about shadowed variables (-Wshadow option), if supported
# Unfortunately, the swig autogenerated files have a lot of shadowed variables
# and -Wno-shadow does not exist.
# Adding -Wshadow can be made only for .cpp files
#and will be added later in CMakeLists.txt
if( CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang" )
    include(CheckCXXCompilerFlag)

    CHECK_CXX_COMPILER_FLAG("-Wshadow" COMPILER_SUPPORTS_WSHADOW)

    if( COMPILER_SUPPORTS_WSHADOW )
        set(WSHADOW_FLAGS "-Wshadow")
    endif()
endif()


#================================================
# Provide access to CCACHE
#================================================
if (USE_CCACHE)
  find_program(CCACHE_FOUND ccache)
  if(CCACHE_FOUND)
    get_property(RULE_LAUNCH_COMPILE GLOBAL PROPERTY RULE_LAUNCH_COMPILE)
    set(RULE_LAUNCH_COMPILE "${RULE_LAUNCH_COMPILE} ${CCACHE_FOUND}")
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ${RULE_LAUNCH_COMPILE})

    get_property(RULE_LAUNCH_LINK GLOBAL PROPERTY RULE_LAUNCH_LINK)
    set(RULE_LAUNCH_LINK "${RULE_LAUNCH_LINK} ${CCACHE_FOUND}")
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ${RULE_LAUNCH_LINK})

    message(STATUS "Used ${CCACHE_FOUND} for compilation.")
  else(CCACHE_FOUND)
    message(STATUS "CCache was requested but not found.")
  endif(CCACHE_FOUND)
endif(USE_CCACHE)


#================================================
# Provide access to CCACHE
#================================================
if (USE_DISTCC)
  find_program(DISTCC_FOUND distcc)
  if(DISTCC_FOUND)
    get_property(RULE_LAUNCH_COMPILE GLOBAL PROPERTY RULE_LAUNCH_COMPILE)
    set(RULE_LAUNCH_COMPILE "${RULE_LAUNCH_COMPILE} ${DISTCC_FOUND}")
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ${RULE_LAUNCH_COMPILE})
    message(STATUS "Using ${DISTCC_FOUND} for distributed build.")
  else(DISTCC_FOUND)
    message(INFO "Distcc was requested but not found.")
  endif(DISTCC_FOUND)
endif(USE_DISTCC)


#================================================
# Set flags for GCC, or treat llvm as GCC
#================================================

if( CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang" )

    execute_process( COMMAND ${CMAKE_C_COMPILER} -dumpversion
        OUTPUT_VARIABLE GCC_VERSION
        OUTPUT_STRIP_TRAILING_WHITESPACE )

    if( CMAKE_CXX_COMPILER_ID MATCHES "Clang" )
        set( TO_LINKER -XLinker )
    else()
        set( TO_LINKER -Wl )
    endif()

    # Establish -Wall early, so specialized relaxations of this may come
    # subsequently on the command line, such as in pcbnew/github/CMakeLists.txt
    set( CMAKE_C_FLAGS   "-Wall ${CMAKE_C_FLAGS}" )
    set( CMAKE_CXX_FLAGS "-Wall ${CMAKE_CXX_FLAGS}" )

    set( CMAKE_C_FLAGS_DEBUG   "-g3 -ggdb3 -DDEBUG" )
    set( CMAKE_CXX_FLAGS_DEBUG "-g3 -ggdb3 -DDEBUG -Wno-deprecated-declarations" )

    if( MINGW )
        set( CMAKE_EXE_LINKER_FLAGS_RELEASE "-s" )

        # _UNICODE definition seems needed under mingw/gcc 4.8
        # (Kicad uses unicode, and on Windows, wxWidgets >= 2.9.4 is mandatory
        # and uses unicode)
        if( GCC_VERSION VERSION_EQUAL 4.8.0 OR GCC_VERSION VERSION_GREATER 4.8.0 )
            add_definitions(-D_UNICODE)
        endif()

        # Since version 2.8.5, Cmake uses a response file (.rsp) to
        # pass the list of include paths to gcc
        # unfortunately, under mingw32+msys, at least with gcc 4.8 and previous,
        # this file is not always expanded and in this case include paths defined in this file
        # are not taken in account ( this is the case of wxWidgets includes )
        # If it is the case, disable this response file for includes ( See Windows-GNU.cmake module )
        if( false ) #set to true to disable the include response file
            if( WIN32 AND MSYS AND NOT CMAKE_CROSSCOMPILING )
                # fixme: it is needed only with MSYS+MINGW32? or always under MINGW
                if( ${CMAKE_SIZEOF_VOID_P} MATCHES 4 )
                    set( CMAKE_CXX_USE_RESPONSE_FILE_FOR_INCLUDES 0 )
                endif()
            endif()
        endif()

        # for some reasons, cmake does do use always a response file to send the list of objects
        # to the archiver, and because this list can be very long, and can create issue
        # when it is used in a command line, force use of a response file to store it
        SET( CMAKE_CXX_USE_RESPONSE_FILE_FOR_OBJECTS 1 )

        # The MinGW compiler can use the microsoft system snprintf as standard and it has a broken
        # API with respect to the C99 standard, so make sure we force it to use its own compliant
        # snprintf
        add_definitions(-D__USE_MINGW_ANSI_STDIO=1)

    else()
        if( NOT APPLE )
            # Thou shalt not link vaporware and tell us it's a valid DSO (apple ld doesn't support it)
            set( CMAKE_SHARED_LINKER_FLAGS "${TO_LINKER},--no-undefined" )
            set( CMAKE_MODULE_LINKER_FLAGS "${TO_LINKER},--no-undefined" )

            set( CMAKE_EXE_LINKER_FLAGS_RELEASE "-s" )

            # Defeat ELF's ability to use the GOT to replace locally implemented functions
            # with ones from another module.
            # https://bugs.launchpad.net/kicad/+bug/1322354
            set( CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} ${TO_LINKER},-Bsymbolic" )
            set( CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} ${TO_LINKER},-Bsymbolic" )
        endif()

    endif()

    # quiet GCC while in boost
    if( GCC_VERSION VERSION_GREATER 4.8 OR GCC_VERSION VERSION_EQUAL 4.8 OR CMAKE_CXX_COMPILER_ID MATCHES "Clang" )
        set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-local-typedefs" )
    endif()
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-strict-aliasing" )

    if( APPLE )
        set( CMAKE_LD_FLAGS "${CMAKE_LD_FLAGS} -headerpad_max_install_names") # needed by fixbundle
    endif()

endif( CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang" )

if( USE_WX_OVERLAY OR APPLE )
    add_definitions( -DUSE_WX_OVERLAY )
endif()

if( KICAD_SCRIPTING )
    add_definitions( -DKICAD_SCRIPTING )
endif()

if( KICAD_SCRIPTING_MODULES )
    add_definitions( -DKICAD_SCRIPTING_MODULES )
endif()

if( KICAD_SCRIPTING_WXPYTHON )
    add_definitions( -DKICAD_SCRIPTING_WXPYTHON )
endif()

if( KICAD_SCRIPTING_ACTION_MENU )
    add_definitions( -DKICAD_SCRIPTING_ACTION_MENU )
endif()

if( KICAD_SPICE )
    add_definitions( -DKICAD_SPICE )
endif()

if( KICAD_USE_OCE )
    add_definitions( -DKICAD_USE_OCE )
endif()

if( KICAD_USE_OCC )
    add_definitions( -DKICAD_USE_OCC )
    remove_definitions( -DKICAD_USE_OCE )
    unset( KICAD_USE_OCE )
endif()

if( KICAD_USE_CUSTOM_PADS )
    add_definitions( -DKICAD_USE_CUSTOM_PADS )
endif()

if( USE_WX_GRAPHICS_CONTEXT OR APPLE )
    add_definitions( -DUSE_WX_GRAPHICS_CONTEXT )
endif()


# KIFACE_SUFFIX is the file extension used for top level program modules which
# implement the KIFACE interface.  A valid suffix starts with a period '.'.

if( false )
    # This is the eventual situation near milestone C) of modular-kicad blueprint.
    # Until then we use .kiface extension so we don't collide with python DSO.
    set( KIFACE_SUFFIX  ${CMAKE_SHARED_MODULE_SUFFIX} )
else()
    # Temporary situation until we can dovetail the python DSO into the kiface DSO.
    set( KIFACE_SUFFIX  ".kiface" )
endif()

# KIFACE_PREFIX is a basename prefix used for top level program modules which
# implement the KIFACE.
set( KIFACE_PREFIX  "_" )
#message( STATUS "KIFACE_SUFFIX:${KIFACE_SUFFIX}  KIFACE_PREFIX:${KIFACE_PREFIX}" )


#================================================
# Locations for install targets.
#================================================
if( NOT APPLE )
    # Everything without leading / is relative to CMAKE_INSTALL_PREFIX.
    set( KICAD_BIN bin
        CACHE PATH "Location of KiCad binaries." )

    set( KICAD_DATA ${CMAKE_INSTALL_DATADIR}/kicad
        CACHE PATH "Location of KiCad data files." )

    if( WIN32 )
        set( KICAD_PLUGINS ${KICAD_BIN}/scripting/plugins
            CACHE PATH "Location of KiCad plugins." )

        set( KICAD_LIB ${KICAD_BIN}
            CACHE PATH "Location of KiCad shared objects" )

        set( KICAD_USER_PLUGIN ${KICAD_BIN}/plugins
            CACHE PATH "Location of KiCad user-loaded plugins" )
    else()
        set( KICAD_PLUGINS ${KICAD_DATA}/plugins
            CACHE PATH "Location of KiCad plugins." )

        set( KICAD_LIB ${CMAKE_INSTALL_LIBDIR}
            CACHE PATH "Location of KiCad shared objects" )

        set( KICAD_USER_PLUGIN ${CMAKE_INSTALL_LIBDIR}/kicad/plugins
            CACHE PATH "Location of KiCad user-loaded plugins" )
    endif()

    set( KICAD_DOCS ${CMAKE_INSTALL_DATADIR}/doc/kicad
        CACHE PATH "Location of KiCad documentation files." )
    set( KICAD_DEMOS ${KICAD_DATA}/demos
        CACHE PATH "Location of KiCad demo files." )
    set( KICAD_TEMPLATE ${KICAD_DATA}/template
        CACHE PATH "Location of KiCad template files." )
else()
    # everything without leading / is relative to CMAKE_INSTALL_PREFIX.
    # CMAKE_INSTALL_PREFIX is root of .dmg image
    set( KICAD_BIN ${CMAKE_INSTALL_PREFIX}
        CACHE PATH "Location of KiCad binaries." FORCE )

    # some paths to single app bundle
    set( OSX_BUNDLE_MAIN "kicad.app" )
    set( OSX_BUNDLE_BIN_DIR "Contents/MacOS" )
    set( OSX_BUNDLE_LIB_DIR "Contents/Frameworks" )
    set( OSX_BUNDLE_KIFACE_DIR "Contents/PlugIns" )
    set( OSX_BUNDLE_SUP_DIR "Contents/SharedSupport" )
    set( OSX_BUNDLE_APP_DIR "Contents/Applications" )
    set( OSX_BUNDLE_BUILD_DIR "${CMAKE_BINARY_DIR}/kicad/${OSX_BUNDLE_MAIN}" )
    set( OSX_BUNDLE_BUILD_BIN_DIR "${OSX_BUNDLE_BUILD_DIR}/${OSX_BUNDLE_BIN_DIR}" )
    set( OSX_BUNDLE_BUILD_LIB_DIR "${OSX_BUNDLE_BUILD_DIR}/${OSX_BUNDLE_LIB_DIR}" )
    set( OSX_BUNDLE_BUILD_KIFACE_DIR "${OSX_BUNDLE_BUILD_DIR}/${OSX_BUNDLE_KIFACE_DIR}" )
    set( OSX_BUNDLE_BUILD_PLUGIN_DIR "${OSX_BUNDLE_BUILD_DIR}/${OSX_BUNDLE_KIFACE_DIR}" )
    set( OSX_BUNDLE_INSTALL_DIR "${KICAD_BIN}/${OSX_BUNDLE_MAIN}" )
    set( OSX_BUNDLE_INSTALL_BIN_DIR "${OSX_BUNDLE_INSTALL_DIR}/${OSX_BUNDLE_BIN_DIR}" )
    set( OSX_BUNDLE_INSTALL_LIB_DIR "${OSX_BUNDLE_INSTALL_DIR}/${OSX_BUNDLE_LIB_DIR}" )
    set( OSX_BUNDLE_INSTALL_KIFACE_DIR "${OSX_BUNDLE_INSTALL_DIR}/${OSX_BUNDLE_KIFACE_DIR}" )
    set( OSX_BUNDLE_INSTALL_PLUGIN_DIR "${OSX_BUNDLE_INSTALL_DIR}/${OSX_BUNDLE_KIFACE_DIR}" )

    # everything provided with the application bundle goes into
    # kicad.app/Contents/SharedSupport => accessible via GetDataDir()
    # everything else to the .dmg image
    set( KICAD_DATA ${OSX_BUNDLE_INSTALL_DIR}/${OSX_BUNDLE_SUP_DIR}
        CACHE PATH "Location of KiCad data files." FORCE )
    set( KICAD_LIB ${OSX_BUNDLE_INSTALL_DIR}/${OSX_BUNDLE_LIB_DIR}
        CACHE PATH "Location of KiCad shared objects" FORCE )
    set( KICAD_USER_PLUGIN ${OSX_BUNDLE_INSTALL_PLUGIN_DIR}
        CACHE PATH "Location of KiCad user-loaded plugins" FORCE )
    set( KICAD_TEMPLATE ${KICAD_DATA}/template
        CACHE PATH "Location of KiCad template files." FORCE )
    set( KICAD_PLUGINS ${KICAD_DATA}/plugins
        CACHE PATH "Location of KiCad plugins." FORCE )
    set( KICAD_DOCS doc
        CACHE PATH "Location of KiCad documentation files." FORCE )
    set( KICAD_DEMOS demos
        CACHE PATH "Location of KiCad demo files." FORCE )

    # RPATH setttings for building shared libraries
    set( CMAKE_MACOSX_RPATH FALSE )

    # Override default paths for fixup_bundle
    set( OSX_BUNDLE_OVERRIDE_PATHS "
        function( gp_item_default_embedded_path_override item default_embedded_path_var )
            # by default, embed things right next to the main bundle executable:
            set( path \"@executable_path/../../Contents/MacOS\" )
            set( overridden 0 )

            # embed .dylibs right next to the main bundle executable:
            if( item MATCHES \"\\\\.dylib$\" )
                set( path \"@executable_path/../Frameworks\" )
                set( overridden 1 )
            endif()

            set( \${default_embedded_path_var} \"\${path}\" PARENT_SCOPE )
        endfunction(gp_item_default_embedded_path_override)

        # If `BU_CHMOD_BUNDLE_ITEMS` is not set, `install_name_tool` will fail to re-write some
        # loader paths due to lack of writable permissions if the build dependencies were installed
        # by brew (or didn't have writable permissions)
        set ( BU_CHMOD_BUNDLE_ITEMS ON )
        "
        )
endif()

mark_as_advanced( KICAD_BIN
    KICAD_PLUGINS
    KICAD_USER_PLUGIN
    KICAD_LIB
    KICAD_DATA
    KICAD_DOCS
    KICAD_DEMOS
    KICAD_TEMPLATE )

include( Functions )

include( ExternalProject )

#================================================
# Find libraries that are needed to build KiCad.
#================================================
include( CheckFindPackageResult )

#
# Find OpenMP support, optional
#

find_package( OpenMP )

if( OPENMP_FOUND )
    set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}" )
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}" )
    add_definitions( -DUSE_OPENMP )

    # MinGW does not include the OpenMP link library and FindOpenMP.cmake does not
    # set it either.  Not sure this is the most elegant solution but it works.
    if( MINGW )
        set( OPENMP_LIBRARIES gomp )
    endif()
endif()

#
# Find wxWidgets library, required
#

# Here you can define what libraries of wxWidgets you need for your
# application. You can figure out what libraries you need here;
# http://www.wxwidgets.org/manuals/2.8/wx_librarieslist.html

# Turn on wxWidgets compatibility mode for some classes
add_definitions( -DWX_COMPATIBILITY )

# See line 41 of CMakeModules/FindwxWidgets.cmake
set( wxWidgets_CONFIG_OPTIONS ${wxWidgets_CONFIG_OPTIONS} --static=no )

find_package( wxWidgets 3.0.0 COMPONENTS gl aui adv html core net base xml stc REQUIRED )

# Include wxWidgets macros.
include( ${wxWidgets_USE_FILE} )

# Check the toolkit used to build wxWidgets
execute_process( COMMAND sh -c "${wxWidgets_CONFIG_EXECUTABLE} --query-toolkit"
    RESULT_VARIABLE wxWidgets_TOOLKIT_RESULT
    OUTPUT_VARIABLE wxWidgets_TOOLKIT_FOUND
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

if( wxWidgets_TOOLKIT_FOUND STREQUAL "gtk3" )
    message( WARNING "\nwxWidgets library has been built against GTK3, it causes a lot of problems in KiCad" )
    add_definitions( -DUSE_WX_GRAPHICS_CONTEXT )
    add_definitions( -DWXGTK3 )
endif()

#
# Find OpenGL library, required
#
set( OpenGL_GL_PREFERENCE "GLVND" )     # CMake 3.11+ setting; see 'cmake --help-policy CMP0072'
find_package( OpenGL REQUIRED )

#
# Find GLEW library, required
#
if( NOT GLEW_FOUND )
    find_package( GLEW REQUIRED )
    check_find_package_result( GLEW_FOUND "GLEW" )
endif()

#
# Find GLM library, required
#
find_package( GLM 0.9.5.1 REQUIRED )

add_definitions( -DGLM_FORCE_CTOR_INIT )

#
# Find CURL library, required for github plugin
#
if( BUILD_GITHUB_PLUGIN )
    find_package( CURL REQUIRED )
endif()

#
# Find Cairo library, required
#
find_package( Cairo 1.8.8 REQUIRED )
find_package( Pixman 0.30 REQUIRED )

#
# Find Boost headers, required.
find_package( Boost 1.54.0 REQUIRED )

# Include MinGW resource compiler.
include( MinGWResourceCompiler )

# Find GDI+ on windows if wxGraphicsContext is available.
if( MINGW AND USE_WX_GRAPHICS_CONTEXT )
    find_package( GdiPlus )
    check_find_package_result( GDI_PLUS_FOUND "GDI+" )
endif()

# Find ngspice library, required for integrated circuit simulator
if( KICAD_SPICE )
    find_package( ngspice REQUIRED )
endif()

# Find OpenCascade Community Edition, required for STEP plugin and tools
if( KICAD_USE_OCE )
    set( OCC_LIBRARIES TKBinXCAF TKPCAF TKSTEP TKXDESTEP TKIGES TKXDEIGES )

    find_package( OCE 0.16 REQUIRED ${OCC_LIBRARIES} )

elseif( KICAD_USE_OCC )
    find_package(OpenCASCADE)
    if( NOT OCC_FOUND )
        MESSAGE( FATAL_ERROR "================================================================\n"
                             " KICAD_USE_OCC=True but OpenCASCADE was no found!\n"
                             "================================================================\n")
    endif()
    if( OCC_VERSION_STRING VERSION_LESS 6.8.0 )
        MESSAGE( FATAL_ERROR "================================================================\n"
                             "OpenCASCADE version ${OCC_VERSION_STRING} was found.\n"
                             "  KiCad requires a minimum version of 6.8.0\n"
                             "================================================================\n")
    endif()
    include_directories( SYSTEM ${OCC_INCLUDE_DIR} )
endif()

# Assist with header file searching optimization:
# INC_BEFORE and INC_AFTER are two lists which go at the front and back of the
# header file search lists, respectively.
# INC_BEFORE is for use with "include_directories( BEFORE ...)", which _reverses_
# the order during insertion.  (So put first wanted last, which is
# ${CMAKE_SOURCE_DIR/include.)  Use '.' for current source dir since
# we don't want expansion here and now, which would happen if using ${CMAKE_CURRENT_SOURCE_DIR}.
# Instead we use '.' which is applicable to any source directory below here as a result of
# this lack of expansion.
set( INC_BEFORE
    .
    ${CMAKE_SOURCE_DIR}/include
    )

set( INC_AFTER
    ${Boost_INCLUDE_DIR}
    ${CMAKE_BINARY_DIR}
    )


# Find Python and other scripting resources
if( KICAD_SCRIPTING OR KICAD_SCRIPTING_MODULES )

    # SWIG 3.0 or later require for C++11 support.
    find_package( SWIG 3.0 REQUIRED )
    include( ${SWIG_USE_FILE} )

    # force a python version < 3.0
    set( PythonInterp_FIND_VERSION 2.6 )
    set( PythonLibs_FIND_VERSION 2.6 )

    find_package( PythonInterp )

    check_find_package_result( PYTHONINTERP_FOUND "Python Interpreter" )

    if( NOT PYTHON_VERSION_MAJOR EQUAL 2 )
        message( FATAL_ERROR "Python 2.x is required." )
    endif()

    # Get the correct Python site package install path from the Python interpreter found by
    # FindPythonInterp unless the user specifically defined a custom path.
    if( NOT PYTHON_SITE_PACKAGE_PATH )
        execute_process( COMMAND ${PYTHON_EXECUTABLE} -c "import distutils.sysconfig;print\"%s\"%distutils.sysconfig.get_python_lib(plat_specific=0, standard_lib=0, prefix='')"
            OUTPUT_VARIABLE PYTHON_SITE_PACKAGE_PATH
            OUTPUT_STRIP_TRAILING_WHITESPACE
            )

        if( NOT PYTHON_SITE_PACKAGE_PATH )
            message( FATAL_ERROR "Error occurred while attempting to find the Python site library path." )
        endif()
    endif()

    if( NOT APPLE )
        set( PYTHON_DEST "${PYTHON_SITE_PACKAGE_PATH}"
            CACHE PATH "Python module install path."
            )
    else()
        # relative path for python in bundle
        set( PYTHON_LIB_DIR "python/site-packages" )
        # install into bundle Frameworks folder
        set( PYTHON_DEST "${OSX_BUNDLE_BUILD_LIB_DIR}/${PYTHON_LIB_DIR}"
            CACHE PATH "Python module install path."
            )
    endif()
    mark_as_advanced( PYTHON_DEST )
    message( STATUS "Python module install path: ${PYTHON_DEST}" )

    find_package( PythonLibs 2.6 )

    if( KICAD_SCRIPTING_WXPYTHON )
        # Check to see if the correct version of wxPython is installed based on the version of
        # wxWidgets found.  At least the major an minor version should match.
        set( _wxpy_version "${wxWidgets_VERSION_MAJOR}.${wxWidgets_VERSION_MINOR}" )
        set( _py_cmd "import wxversion;print wxversion.checkInstalled('${_wxpy_version}')" )

        # Add user specified Python site package path.
        if( PYTHON_SITE_PACKAGE_PATH )
            set( _py_cmd
                "import sys;sys.path.insert(0, \"${PYTHON_SITE_PACKAGE_PATH}\");${_py_cmd}" )
        endif()

        execute_process( COMMAND ${PYTHON_EXECUTABLE} -c "${_py_cmd}"
            RESULT_VARIABLE WXPYTHON_VERSION_RESULT
            OUTPUT_VARIABLE WXPYTHON_VERSION_FOUND
            OUTPUT_STRIP_TRAILING_WHITESPACE
            )

        # message( STATUS "WXPYTHON_VERSION_FOUND: ${WXPYTHON_VERSION_FOUND}" )
        # message( STATUS "WXPYTHON_VERSION_RESULT: ${WXPYTHON_VERSION_RESULT}" )

        # Check to see if any version of wxPython is installed on the system.
        if( WXPYTHON_VERSION_RESULT GREATER 0 )
            message( FATAL_ERROR "wxPython does not appear to be installed on the system." )
        endif()

        if( NOT WXPYTHON_VERSION_FOUND STREQUAL "True" )
            message( FATAL_ERROR
                "wxPython version ${_wxpy_version} does not appear to be installed on the system." )
        endif()

        set( WXPYTHON_VERSION ${_wxpy_version} CACHE STRING "wxPython version found." )
        message( STATUS "wxPython version ${_wxpy_version} found." )


        # Compare wxPython and wxWidgets toolkits
        set( _py_cmd "import wx; print(wx.version().split(' ')[1])" )

        # Add user specified Python site package path.
        if( PYTHON_SITE_PACKAGE_PATH )
            set( _py_cmd
                "import sys;sys.path.insert(0, \"${PYTHON_SITE_PACKAGE_PATH}\");${_py_cmd}" )
        endif()

        execute_process( COMMAND ${PYTHON_EXECUTABLE} -c "${_py_cmd}"
            RESULT_VARIABLE WXPYTHON_TOOLKIT_RESULT
            OUTPUT_VARIABLE WXPYTHON_TOOLKIT_FOUND
            OUTPUT_STRIP_TRAILING_WHITESPACE
        )

        # Check if wxWidgets toolkits match, it is a Linux-only issue
        if( UNIX AND NOT APPLE AND NOT wxWidgets_TOOLKIT_FOUND STREQUAL WXPYTHON_TOOLKIT_FOUND )
            message( FATAL_ERROR "\nwxWidgets and wxPython use different toolkits "
                "(${wxWidgets_TOOLKIT_FOUND} vs ${WXPYTHON_TOOLKIT_FOUND}). "
                "It will result in a broken build. Please either install wxPython built using "
                "${wxWidgets_TOOLKIT_FOUND} or add '-DKICAD_SCRIPTING_WXPYTHON=OFF' to cmake "
                "parameters to disable wxPython support." )
        endif()
    endif()

    #message( STATUS "PYTHON_INCLUDE_DIRS:${PYTHON_INCLUDE_DIRS}" )

    # Infrequently needed headers go at end of search paths, append to INC_AFTER which
    # although is used for all components, should be a harmless hit for something like eeschema
    # so long as unused search paths are at the end like this.
    set( INC_AFTER ${INC_AFTER} ${PYTHON_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/scripting )

    #message( STATUS "/ INC_AFTER:${INC_AFTER}" )
endif()

if( APPLE )
    # Remove app bundles in ${KICAD_BIN} before installing anything new.
    # Must be defined before all includes so that it is executed first.
    install( CODE "
            message( STATUS \"Removing existing application bundles...\" )
            # Remove links to standalone apps
            file( REMOVE ${KICAD_BIN}/bitmap2component.app )
            file( REMOVE ${KICAD_BIN}/eeschema.app )
            file( REMOVE ${KICAD_BIN}/gerbview.app )
            file( REMOVE ${KICAD_BIN}/pcb_calculator.app )
            file( REMOVE ${KICAD_BIN}/pcbnew.app )
            file( REMOVE ${KICAD_BIN}/pl_editor.app )
            # Remove main bundle
            file( REMOVE_RECURSE ${KICAD_BIN}/${OSX_BUNDLE_MAIN} )
        " COMPONENT Runtime
        )
endif()

#================================================
# Doxygen Output
#================================================

find_package( Doxygen )
if( DOXYGEN_FOUND )
    add_custom_target( doxygen-docs
        ${CMAKE_COMMAND} -E remove_directory Documentation/doxygen
        COMMAND ${DOXYGEN_EXECUTABLE}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        DEPENDS Doxyfile
        COMMENT "building doxygen docs into directory Documentation/doxygen/html"
        )
    add_custom_target( dev-docs
        ${CMAKE_COMMAND} -E remove_directory Documentation/development/doxygen
        COMMAND ${DOXYGEN_EXECUTABLE}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Documentation/development
        DEPENDS Doxyfile
        COMMENT "building developer's resource docs into directory Documentation/development/doxygen/html"
        )
else()
    message( STATUS "WARNING: Doxygen not found - doxygen-docs (Source Docs) target not created" )
endif()

# Generate config.h.
configure_file( ${PROJECT_SOURCE_DIR}/CMakeModules/config.h.cmake
    ${CMAKE_BINARY_DIR}/config.h )

###
# Generate Map file
###
if( KICAD_MAKE_LINK_MAPS )
    # Currently only works on linux/gcc
    if( UNIX AND NOT APPLE )
        set( MAKE_LINK_MAPS true )
    else()
        set( MAKE_LINK_MAPS false )
    endif()
endif()

#================================================
# "make uninstall" rules
#================================================
configure_file(
    "${CMAKE_MODULE_PATH}/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY )

add_custom_target( uninstall
    "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake" )


#================================================
# Installation
#================================================

###
# Install scripts
###
if( UNIX AND NOT APPLE )
    install( DIRECTORY scripts
        DESTINATION ${KICAD_DOCS}
        COMPONENT resources
        PATTERN "*.bat" EXCLUDE
        )
endif()

###
# FreeDesktop .desktop and MIME resources
###
if( UNIX AND NOT APPLE )

    # Set paths
    set( UNIX_MIME_DIR resources/linux/mime )
    set( UNIX_MIME_FILES ${UNIX_MIME_DIR}/mime )
    set( UNIX_ICON_FILES ${UNIX_MIME_DIR}/icons )
    set( UNIX_APPLICATIONS_FILES ${UNIX_MIME_DIR}/applications )
    set( UNIX_APPDATA_FILES resources/linux/appdata )

    # Install Mime directory
    install( DIRECTORY ${UNIX_ICON_FILES}
        DESTINATION share
        COMPONENT resources
        )

    # Install Icons
    install( DIRECTORY ${UNIX_MIME_FILES}
        DESTINATION share
        COMPONENT resources
        )

    # Install Applications directory (.desktop files)
    install( DIRECTORY ${UNIX_APPLICATIONS_FILES}
        DESTINATION share
        COMPONENT resources
        )

    # Install AppStream directory (app store entry)
    install( DIRECTORY ${UNIX_APPDATA_FILES}
        DESTINATION share
        COMPONENT resources
        )
endif()

#include( CTest )

if( UNIX AND NOT APPLE )

    # Create a *.deb file:
    set( CPACK_GENERATOR "DEB" )
    set( CPACK_DEBIAN_PACKAGE_MAINTAINER "http://launchpad.net/kicad" )

    set( CPACK_PACKAGE_VERSION_MAJOR 1 )
    set( CPACK_PACKAGE_VERSION_MINOR 0 )
    set( CPACK_PACKAGE_VERSION_PATCH 0 )
    #set( CPACK_PACKAGE_CONTACT Firstname Lastname <email@company.com> )
    set( CPACK_PACKAGE_DESCRIPTION_SUMMARY "KiCad built by CMake build system." )

    include( CPack )

endif()

#================================================
# Let CMake look in these directories for nested
# 'CMakeLists.txt' files to process
#================================================

# Binaries ( CMake targets )
add_subdirectory( bitmaps_png )
add_subdirectory( common )
add_subdirectory( 3d-viewer )
add_subdirectory( cvpcb )
add_subdirectory( eeschema )
add_subdirectory( gerbview )
add_subdirectory( lib_dxf )
add_subdirectory( pcbnew )
add_subdirectory( polygon )
add_subdirectory( pagelayout_editor )
add_subdirectory( potrace )
add_subdirectory( bitmap2component )
add_subdirectory( pcb_calculator )
add_subdirectory( plugins )             # 3D plugins must be built before kicad
add_subdirectory( kicad )               # should follow pcbnew, eeschema
add_subdirectory( tools )
add_subdirectory( utils )
add_subdirectory( qa )

# Resources
if ( KICAD_INSTALL_DEMOS )
add_subdirectory( demos )
endif ( KICAD_INSTALL_DEMOS )
add_subdirectory( template )
