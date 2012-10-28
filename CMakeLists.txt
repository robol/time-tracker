PROJECT(GoogleTimeTracker)
cmake_minimum_required(VERSION 2.8)
FIND_PACKAGE(Qt4 REQUIRED)

# We also need libgcal
FIND_PACKAGE(PkgConfig)
PKG_CHECK_MODULES (GDATA libgdata>=0.12 gobject-2.0 REQUIRED)

ADD_SUBDIRECTORY(time-tracker)
