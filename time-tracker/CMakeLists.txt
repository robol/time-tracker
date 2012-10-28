SET (timetracker_SOURCES
eventlistmodel.cpp
calendar.cpp
mainwindow.cpp
calendarclient.cpp
calendarevent.cpp
calendarlistmodel.cpp
main.cpp
)

SET (timetracker_HEADERS
calendar.h
calendarclient.h
calendarevent.h
calendarlistmodel.h
eventlistmodel.h
mainwindow.h
)

SET (timetracker_FORMS
mainwindow.ui
)

QT4_WRAP_CPP (timetracker_HEADERS_MOC
        ${timetracker_HEADERS}
)

QT4_WRAP_UI (timetracker_FORMS_HEADERS ${timetracker_FORMS})

INCLUDE (${QT_USE_FILE})
INCLUDE_DIRECTORIES (${CMAKE_CURRENT_BINARY_DIR})
ADD_DEFINITIONS (${QT_DEFINITIONS} ${GDATA_CFLAGS})

ADD_EXECUTABLE (timetracker
        ${timetracker_SOURCES}
        ${timetracker_HEADERS_MOC}
        ${timetracker_FORMS_HEADERS})
TARGET_LINK_LIBRARIES (timetracker ${QT_LIBRARIES} ${GDATA_LDFLAGS} ${GDATA_LIBRARIES}
        -I${CMAKE_SOURCE_DIR}/time-tracker)

INSTALL (TARGETS timetracker
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION bin
  RUNTIME DESTINATION bin
)
