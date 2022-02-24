import QtQuick 2.0

Item {
    anchors.fill: parent

    Timer{
        interval: 100;
        onTriggered: liveImage.reload()
        running:  true
        repeat:  true
    }

    Image {
        id: liveImage
        property bool counter: false

        asynchronous: true
        source: "image://live/image"
        anchors.fill: parent
        fillMode: Image.PreserveAspectFit
        cache: false
          function reload() {
            counter = !counter
            source = "image://live/image?id=" + counter
            console.log("reloaded....");
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

    Text {
        anchors.centerIn: parent
        id: test
        text: qsTr("Hello world")
    }






}
