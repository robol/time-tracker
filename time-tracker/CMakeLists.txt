SET (GoogleTimeTracker_SOURCES
eventlistmodel.cpp
calendar.cpp
mainwindow.cpp
calendarclient.cpp
calendarevent.cpp
calendarlistmodel.cpp
main.cpp
)

SET (GoogleTimeTracker_HEADERS
calendar.h
calendarclient.h
calendarevent.h
calendarlistmodel.h
eventlistmodel.h
mainwindow.h
)

SET (GoogleTimeTracker_FORMS
mainwindow.ui
)

QT4_WRAP_CPP (GoogleTimeTracker_HEADERS_MOC
        ${GoogleTimeTracker_HEADERS}
)

QT4_WRAP_UI (GoogleTimeTracker_FORMS_HEADERS ${GoogleTimeTracker_FORMS})

INCLUDE (${QT_USE_FILE})
INCLUDE_DIRECTORIES (${CMAKE_CURRENT_BINARY_DIR})
ADD_DEFINITIONS (${QT_DEFINITIONS} ${GDATA_CFLAGS} -g -O0)

ADD_EXECUTABLE (GoogleTimeTracker
        ${GoogleTimeTracker_SOURCES}
        ${GoogleTimeTracker_HEADERS_MOC}
        ${GoogleTimeTracker_FORMS_HEADERS})
TARGET_LINK_LIBRARIES (GoogleTimeTracker ${QT_LIBRARIES} ${GDATA_LDFLAGS} ${GDATA_LIBRARIES}
        -I${CMAKE_SOURCE_DIR}/time-tracker)

INSTALL (TARGETS GoogleTimeTracker
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION bin
  RUNTIME DESTINATION bin
)
