import QtQuick 1.0

    Item {
        id: imgDelegateItem
        width: tardisImage.width; height: tardisImage.height

        signal itemClicked(string name, string url)

        Image {
            anchors.centerIn: parent
            source: url
            id: tardisImage

            asynchronous: true
            opacity: 0.0
            onStatusChanged:  if (status == Image.Ready) { state="loaded"; } else { state="notloaded"; }

            sourceSize.width: 80
            sourceSize.height: 80

            width: sourceSize.width
            height: sourceSize.height

            states: [
                State {
                    name: "notloaded"
                    PropertyChanges { target: tardisImage; opacity: 0}
                },
                State {
                    name: "loaded"
                    PropertyChanges { target: tardisImage; opacity: 1.0}
                }
            ]

            transitions:  [
                Transition {
                    to: "*"
                    NumberAnimation { target: tardisImage; properties: "opacity"; duration:200; easing.type: Easing.Linear }
                }

            ]
        }

        MouseArea {
            id: mouseArea
            anchors.fill: parent
            onClicked: imgDelegateItem.itemClicked(name, url)
        }
    }
