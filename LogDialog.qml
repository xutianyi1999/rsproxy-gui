import QtQuick 2.15
import QtQuick.Controls 2.15

Dialog {
    width: 500
    height: 400
    x: parent.width / 2 - width / 2
    y: parent.height / 2 - height / 2
    title:  "日志"
    standardButtons: Dialog.Close

    ScrollView {
        id: view
        anchors.fill: parent
        TextArea {
            id: textArea
            selectByMouse: true
            font.pixelSize: 12
            background: Rectangle {
                anchors.fill: parent
            }
        }
    }

    function logAppend(log: string) {
       textArea.append(log);
    }
}
