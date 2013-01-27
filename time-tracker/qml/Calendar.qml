// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle {
    width: 640
    height: 480

    Grid {
        id: eventGrid
        rows: 1; columns: 2; spacing: 6
        anchors.fill: parent

        Event {
	    name: "Boh"
        }

        Event {
            name: "Boh 2"
        }
    }
}
