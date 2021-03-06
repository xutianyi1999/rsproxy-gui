import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    anchors.fill: parent
    property int commandId: -1

    function getButton(theCommand){
        if(theCommand === Enums.Commands.DoCmd1)
            return Fa.fa_trash;

        if(theCommand === Enums.Commands.DoCmd2)
            return Fa.fa_edit;

        return null;
    }

    Rectangle {
        id: rect
        radius: 15
        color: "#607D8B"
        border.color: "#515151"
        border.width: 2
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        width: 30
        height: 30
        Text {
            font.family: Fa.solid
            font.pointSize: 11
            color: "#FFFFFF"
            text: getButton(commandId);
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
}
