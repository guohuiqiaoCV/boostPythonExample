cmake_minimum_required(VERSION 3.0)

set(Project hello_ext)

# support c++11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fPIC")

# disable the lib prefix for shared objects
set(CMAKE_SHARED_LIBRARY_PREFIX "")

# set boost properties and link to boost
set(BOOST_ROOT /opt/Boost)
set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 

find_package(Boost 1.60.0 REQUIRED COMPONENTS python3) 

if(Boost-NOTFOUND)
  MESSAGE(FATAL_ERROR "boost.python not found!")
endif()

# set python path (use 3.4 here)
set(Python_INCLUDE_DIRS "/usr/include/python3.4m")

# set up the include path
INCLUDE_DIRECTORIES("${Boost_INCLUDE_DIRS}" 
                    "${Python_INCLUDE_DIRS}" 
                   )

# add project
ADD_LIBRARY(${Project} SHARED hello.cpp)

TARGET_LINK_LIBRARIES(${Project} ${Boost_LIBRARIES})
