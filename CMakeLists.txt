PROJECT(GoogleTimeTracker)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
FIND_PACKAGE(Qt4 REQUIRED)

# Check for the required dependencies.
FIND_PACKAGE(PkgConfig)
PKG_CHECK_MODULES (GDATA libgdata>=0.9.0 gobject-2.0 REQUIRED)

ADD_SUBDIRECTORY(time-tracker)
