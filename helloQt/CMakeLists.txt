cmake_minimum_required(VERSION 3.0)

set(Project helloQt)

# load paths from the user file if exists 
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/CMakeUser.cmake)
	include(${CMAKE_CURRENT_SOURCE_DIR}/CMakeUser.cmake)
endif()

# support c++11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fPIC")

# disable the lib prefix for shared objects
#set(CMAKE_SHARED_LIBRARY_PREFIX "")

# set boost properties and link to boost
if(NOT BOOST_ROOT)
  MESSAGE(WARNING "BOOST_ROOT not found. Please make sure your boost.python is installed in standard path")
endif()
set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 

find_package(Boost 1.60.0 REQUIRED COMPONENTS python3) 

if(Boost-NOTFOUND)
  MESSAGE(FATAL_ERROR "boost.python not found!")
endif()

# set python path (use 3.4 here)
set(Python_INCLUDE_DIRS "/usr/include/python3.4m")

### find Qt
unset(QT_QTCORE_LIBRARY CACHE)
unset(QT_QTGUI_LIBRARY CACHE)
unset(QT_QTNETWORK_LIBRARY CACHE)
unset(QT_QTMAIN_LIBRARY CACHE)

# set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

if(NOT QT_QMAKE_EXECUTABLE)
	find_program(QT_QMAKE_EXECUTABLE NAMES "qmake" "qmake-qt5" "qmake.exe")
endif()
if(NOT QT_QMAKE_EXECUTABLE)
	message(FATAL_ERROR "you have to set the path to the Qt5 qmake executable")
endif()

GET_FILENAME_COMPONENT(QT_QMAKE_PATH ${QT_QMAKE_EXECUTABLE} PATH)
set(CMAKE_PREFIX_PATH ${QT_QMAKE_PATH}\\..\\lib\\cmake\\Qt5)
# message(STATUS "path: ${QT_QMAKE_PATH}")


set(QT5_COMPONENTS Core Gui Widgets Network LinguistTools PrintSupport Concurrent OpenGL)
find_package(Qt5 REQUIRED ${QT5_COMPONENTS})

foreach(module ${QT5_COMPONENTS})
   set(QT_INCLUDES ${QT_INCLUDES} "${Qt5${module}_INCLUDE_DIRS}")
   set(QT_LIBRARIES ${QT_LIBRARIES} "${Qt5${module}_LIBRARIES}")
endforeach()

message(STATUS "QT_LIBRARIES = ${QT_LIBRARIES}")
#message(STATUS "QT_INCLUDES = ${QT_INCLUDES}")

add_definitions(-DQT5)

if (DISABLE_QT_DEBUG)
	message (STATUS "disabling qt debug messages")
	add_definitions(-DQT_NO_DEBUG_OUTPUT)
endif()

if(NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DQT_NO_DEBUG)
endif()

### end of find Qt

### OpenGL
#find_package(OpenGL)

# set up the include path
INCLUDE_DIRECTORIES("${Boost_INCLUDE_DIRS}" 
                    "${Python_INCLUDE_DIRS}"
		    "${QT_INCLUDES}" 
                   )

# add files
file(GLOB SRC_FILES "src/*.cpp")
file(GLOB HEADER_FILES "src/*.h")
QT5_WRAP_CPP(MOC_SRC ${HEADER_FILES})

# add libaray
ADD_LIBRARY(${Project} SHARED ${SRC_FILES} ${HEADER_FILES} ${MOC_SRC})
TARGET_LINK_LIBRARIES(${Project} ${Boost_LIBRARIES} ${QT_LIBRARIES})
