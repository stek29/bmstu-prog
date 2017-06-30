project(lab7)
set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        main.cpp)

if (CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-DLAB7_DBG)
endif(CMAKE_BUILD_TYPE MATCHES Debug)

if (NOT DEFINED LAB7_IMPL)
    message(WARNING "No Impl Defined, falling back to STL")
    set(LAB7_IMPL "STL")
endif(NOT DEFINED LAB7_IMPL)

if (${LAB7_IMPL} STREQUAL STL)
    add_definitions(-DLAB7_USE_STL)
    add_executable(lab7 ${SOURCE_FILES} stl.cpp)
elseif(${LAB7_IMPL} STREQUAL QT)
    add_definitions(-DLAB7_USE_QT)
    set(IMPL_FILES qt.cpp)

    add_executable(lab7 ${SOURCE_FILES} qt.cpp)

    find_package(Qt5Core)
    include_directories(${Qt5Core_INCLUDE_DIRS})
    target_link_libraries(lab7 Qt5::Core)
endif(${LAB7_IMPL} STREQUAL STL)

include_directories(.)
