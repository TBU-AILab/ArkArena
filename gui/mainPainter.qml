import QtQuick 2.0

Item {
    anchors.fill: parent
    Text {
        anchors.centerIn: parent
        id: test
        text: qsTr("Hello world")
    }


    Rectangle{
        radius: 50
        border.width: 2
        border.color: "black"
        color: "green"
        width: 100
        height:100

    }

}
