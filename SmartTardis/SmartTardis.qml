import QtQuick 1.0

Item {
    id: smartTardis
    width: 300
    height: 300

    signal itemClicked(string name, string url)

    function setItems(names, urls)
    {
        console.debug(names.length)
        itemList.clear()
        for(var i=0; i<names.length; i++) {
            var l = {"name": names[i], "url": urls[i]}
            itemList.append(l)
        }
    }

    ListModel {
        id: itemList
        objectName: "itemList"

        ListElement {
            name: "NoData"
            url: "tardis.jpg"
        }
    }

    Component
    {
        id: labeledImageDelegate

        Item {
            width: col.width; height: col.height
            //width: GridView.cellWidth; height: GridView.cellHeight
            //clip: true
            Column {
                //anchors.horizontalCenter: parent.horizontalCenter
                id: col
                Image {
                    anchors.horizontalCenter: parent.horizontalCenter
                    source: url
                    id: tardisImage
                    width: 0.2 * sourceSize.width
                    height: 0.2 * sourceSize.height
                }

                Text {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: name
                }
            }

            MouseArea {
                id: mouseArea
                anchors.fill: parent
                onClicked: smartTardis.itemClicked(name, url)
            }
        }
    }


    GridView {
        id: gridview
        model: itemList

        anchors.fill: parent

        cellWidth: 100
        cellHeight: 100

        delegate:  labeledImageDelegate

    }

//    MouseArea {
//        anchors.fill:  parent
//        onClicked: console.log("click!")
//    }

//    ListView {
//        width: 180; height: 200
//        id: listview
//        model: list
//        anchors.top: parent.top
//        delegate: Row {
//            Text { text: name + ", age " + age + "\n" }
//        }
//    }

//    MouseArea {
//        anchors.fill: parent
//        onClicked: {
//            list.append({"name": "Patient Nr. " + list.count} );
//            console.debug(gridview.contentHeight)
//        }
//    }
}

//Rectangle {
//    width: 360
//    height: 360
//    id: page
//    color: "#AAAAAA"
//    Text {
//        anchors.centerIn: parent
//        text: "Hello World"
//    }

