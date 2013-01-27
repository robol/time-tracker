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
eventmatcher.cpp
main.cpp
settings.cpp
qmlwindow.cpp
)

SET (timetracker_HEADERS
eventmatcher.h
)

SET (timetracker_QT_HEADERS
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
qmlwindow.h
)

SET (timetracker_FORMS
mainwindow.ui
logindialog.ui
qmlwindow.ui
)

QT4_ADD_RESOURCES(timetracker_RCC_SRCS timetracker.qrc)

QT4_WRAP_CPP (timetracker_HEADERS_MOC
        ${timetracker_QT_HEADERS}
)

QT4_WRAP_UI (timetracker_FORMS_HEADERS ${timetracker_FORMS})

INCLUDE (${QT_USE_FILE})
INCLUDE_DIRECTORIES (${CMAKE_CURRENT_BINARY_DIR})
ADD_DEFINITIONS (${QT_DEFINITIONS} ${QJSON_DEFINITIONS})

ADD_EXECUTABLE (timetracker
        ${timetracker_SOURCES}
        ${timetracker_HEADERS}
        ${timetracker_HEADERS_MOC}
        ${timetracker_FORMS_HEADERS}
	${timetracker_RCC_SRCS})

IF(WIN32)
  SET(ADDITIONAL_LDFLAGS -mwindows -lqjson)
ENDIF(WIN32)

TARGET_LINK_LIBRARIES (timetracker ${QT_LIBRARIES} 
        ${QJSON_LDFLAGS} ${QJSON_LIBRARIES}
        -I${CMAKE_SOURCE_DIR}/time-tracker ${ADDITIONAL_LDFLAGS})

INSTALL (TARGETS timetracker
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION bin
  RUNTIME DESTINATION bin
)
