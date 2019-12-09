cmake_minimum_required(VERSION 3.5)

project(simpledicomviewer LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

find_package(Qt5X11Extras REQUIRED)



# Find ITK package
find_package(ITK REQUIRED)
IF(ITK_FOUND)
INCLUDE(${ITK_USE_FILE})
MESSAGE(STATUS "found ITK")
ELSE(ITK_FOUND)
MESSAGE(FATAL_ERROR "Cannot build InsightApplications without ITK. Please
set ITK_DIR.")
ENDIF(ITK_FOUND)

#Findi VTK package
if (ITKVtkGlue_LOADED)
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
MESSAGE(STATUS "found VTK")
else()
find_package(ItkVtkGlue REQUIRED)
include(${ItkVtkGlue_USE_FILE})
MESSAGE(STATUS "found ITKVTKGlue")
set(Glue ItkVtkGlue)
endif()

add_executable(simpledicomviewer
  main.cpp
  mainwindow.cpp
  mainwindow.h
  mainwindow.ui
)

target_link_libraries(simpledicomviewer PRIVATE Qt5::Widgets ${Glue} ${VTK_LIBRARIES} ${ITK_LIBRARIES})
