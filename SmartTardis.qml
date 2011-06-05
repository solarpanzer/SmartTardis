import QtQuick 1.0

Rectangle{
    width: 300
    height: 300

    ListModel {
        id: list

        ListElement {
            name: "a"
            url: "file:///home/sebastian/tardis.jpg"
        }

        ListElement {
            name: "a"
            url: "file:///home/sebastian/tardis.jpg"
        }

        ListElement {
            name: "a"
            url: "file:///home/sebastian/tardis.jpg"
        }

        ListElement {
            name: "a"
            url: "file:///home/sebastian/tardis.jpg"
        }

        ListElement {
            name: "a"
            url: "file:///home/sebastian/tardis.jpg"
        }

        ListElement {
            name: "a"
            url: "file:///home/sebastian/tardis.jpg"
        }

        ListElement {
            name: "a"
            url: "file:///home/sebastian/tardis.jpg"
        }

        ListElement {
            name: "a"
            url: "file:///home/sebastian/tardis.jpg"
        }

        ListElement {
            name: "a"
            url: "file:///home/sebastian/tardis.jpg"
        }

        ListElement {
            name: "a"
            url: "file:///home/sebastian/tardis.jpg"
        }

        ListElement {
            name: "a"
            url: "file:///home/sebastian/tardis.jpg"
        }

        ListElement {
            name: "a"
            url: "file:///home/sebastian/tardis.jpg"
        }

        ListElement {
            name: "a"
            url: "file:///home/sebastian/tardis.jpg"
        }

        ListElement {
            name: "a"
            url: "file:///home/sebastian/tardis.jpg"
        }
    }

    Component {
        id: tardis
        Image {
            source: "file:///home/sebastian/tardis.jpg"
            id: tardisImage
            scale: 0.3
        }
    }

    Component {
        id: labeledImageDelegate
        Column {
            Image {
                anchors.horizontalCenter: parent.horizontalCenter
                source: "file:///home/sebastian/tardis.jpg"
                id: tardisImage
                width: 0.2 * sourceSize.width
                height: 0.2 * sourceSize.height
            }
            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                text: name
            }
        }
    }

    GridView {
        id: gridview
        model: list

        anchors.fill: parent

        cellWidth: 100
        cellHeight: 100

        delegate:  labeledImageDelegate

//        MouseArea {
//            anchors.fill:  parent
//            onClicked: console.log("" + parent.contentWidth + "/" + parent.contentHeight)
//        }
    }

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

