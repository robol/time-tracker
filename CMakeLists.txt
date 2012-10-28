PROJECT(GoogleTimeTracker)
cmake_minimum_required(VERSION 2.8)
FIND_PACKAGE(Qt4 REQUIRED)

# We also need libgcal
FIND_PACKAGE(PkgConfig)
PKG_CHECK_MODULES (GDATA libgdata>=0.12 gobject-2.0 REQUIRED)

SET (GoogleTimeTracker_SOURCES
time-tracker/eventlistmodel.cpp
time-tracker/mainwindow.cpp
time-tracker/calendarclient.cpp
time-tracker/calendarevent.cpp
time-tracker/calendarlistmodel.cpp
time-tracker/main.cpp
)

SET (GoogleTimeTracker_HEADERS
time-tracker/calendarclient.h
time-tracker/calendarevent.h
time-tracker/calendarlistmodel.h
time-tracker/eventlistmodel.h
time-tracker/mainwindow.h
)

SET (GoogleTimeTracker_FORMS
time-tracker/mainwindow.ui
)

QT4_WRAP_CPP (GoogleTimeTracker_HEADERS_MOC
	${GoogleTimeTracker_HEADERS}
)

QT4_WRAP_UI (GoogleTimeTracker_FORMS_HEADERS ${GoogleTimeTracker_FORMS})

INCLUDE (${QT_USE_FILE})
INCLUDE_DIRECTORIES (${CMAKE_CURRENT_BINARY_DIR})
ADD_DEFINITIONS (${QT_DEFINITIONS} ${GDATA_CFLAGS})

ADD_EXECUTABLE (GoogleTimeTracker 
	${GoogleTimeTracker_SOURCES} 
	${GoogleTimeTracker_HEADERS_MOC}
	${GoogleTimeTracker_FORMS_HEADERS})
TARGET_LINK_LIBRARIES (GoogleTimeTracker ${QT_LIBRARIES} ${GDATA_LDFLAGS} ${GDATA_LIBRARIES}
	-I${CMAKE_SOURCE_DIR}/time-tracker)

install(TARGETS GoogleTimeTracker
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION bin
  RUNTIME DESTINATION bin
)
