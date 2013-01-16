SET (timetracker_SOURCES
logindialog.cpp
oauth2.cpp
calendar_data_manager.cpp
eventlistmodel.cpp
calendar.cpp
mainwindow.cpp
calendarclient.cpp
calendarevent.cpp
calendarlistmodel.cpp
main.cpp
settings.cpp
)

SET (timetracker_HEADERS
logindialog.h
oauth2.h
calendar_data_manager.h
calendar.h
calendarclient.h
calendarevent.h
calendarlistmodel.h
eventlistmodel.h
mainwindow.h
settings.h
)

SET (timetracker_FORMS
mainwindow.ui
logindialog.ui
)

QT4_WRAP_CPP (timetracker_HEADERS_MOC
        ${timetracker_HEADERS}
)

QT4_WRAP_UI (timetracker_FORMS_HEADERS ${timetracker_FORMS})

INCLUDE (${QT_USE_FILE})
INCLUDE_DIRECTORIES (${CMAKE_CURRENT_BINARY_DIR})
ADD_DEFINITIONS (${QT_DEFINITIONS})

ADD_EXECUTABLE (timetracker
        ${timetracker_SOURCES}
        ${timetracker_HEADERS_MOC}
        ${timetracker_FORMS_HEADERS})

IF(WIN32)
  SET(ADDITIONAL_LDFLAGS -mwindows)
ENDIF(WIN32)

TARGET_LINK_LIBRARIES (timetracker ${QT_LIBRARIES} -lqjson
        -I${CMAKE_SOURCE_DIR}/time-tracker ${ADDITIONAL_LDFLAGS})

INSTALL (TARGETS timetracker
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION bin
  RUNTIME DESTINATION bin
)
