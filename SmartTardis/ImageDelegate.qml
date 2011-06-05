import QtQuick 1.0

    Item {
        id: imgDelegateItem
        width: tardisImage.width; height: tardisImage.height

        signal itemClicked(string name, string url)

        Image {
            anchors.centerIn: parent
            source: url
            id: tardisImage

            sourceSize.width: 80
            sourceSize.height: 80

            width: sourceSize.width
            height: sourceSize.height
        }

        //width: GridView.cellWidth; height: GridView.cellHeight
        //clip: true
//            Column {
//                //anchors.horizontalCenter: parent.horizontalCenter
//                id: col

//                Text {
//                    anchors.horizontalCenter: parent.horizontalCenter
//                    text: name
//                }
//            }

        MouseArea {
            id: mouseArea
            anchors.fill: parent
            onClicked: imgDelegateItem.itemClicked(name, url)
        }
    }