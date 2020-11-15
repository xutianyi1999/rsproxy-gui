import QtQuick.Dialogs 1.3
import QtQuick.Layouts 1.15
import QtQuick 2.15
import QtQuick.Controls 2.15
import mycpp 1.0

Dialog {
    width: 500
    height: 400
    x: parent.width / 2 - width / 2
    y: parent.height / 2 - height / 2
    title:  "添加节点"
    standardButtons:  Dialog.Save | Dialog.Cancel

    property var fileurl

    QmlCppBridge{
        id: qmlCppBridge
    }

    function init(cmd, json) {
        if (cmd === Enums.Cmd.EDIT) {
            name.readOnly = true
            name.text = json["name"]
            host.text = json["host"]

            if (json["protocol"] === "tcp") {
                protocol.currentIndex = 0
                key.text = json["key"]
                connections.text = json["connections"]
                buffSize.text = json["buffSize"]

                tcpVisible(true)
                quicVisible(false)
            } else {
                protocol.currentIndex = 1
                fileurl = json["cert"]
                var str = fileurl.slice(0, 10)
                cert.text = str +"..."
                serverName.text = json["serverName"]

                tcpVisible(false)
                quicVisible(true)
            }
        } else {
            name.readOnly = false
        }
    }

    onAccepted: {
        var json = {}
        json["name"] = name.text
        json["host"] = host.text

        var protocolText = protocol.currentText
        json["protocol"] = protocolText

        if (protocolText === "tcp") {
            json["connections"] = connections.text
            json["key"] = key.text
            json["buffSize"] = buffSize.text
        } else {
            json["cert"] = fileurl
            json["serverName"] = serverName.text
        }

        qmlCppBridge.update(json)
        bGrid.fillFromJson(qmlCppBridge.selectList())
        textFiledReset()
    }

    onRejected: textFiledReset()

    function textFiledReset() {
        fileurl = ""
        name.text = ""
        host.text = ""
        protocol.currentIndex = 0
        key.text = ""
        connections.text = ""
        buffSize.text = ""
        cert.text = "浏览..."
        serverName.text = ""

        tcpVisible(true)
        quicVisible(false)
    }

    function tcpVisible(flag){
        keyText.visible = flag
        key.visible = flag
        connectionsText.visible = flag
        connections.visible = flag
        buffSizeText.visible = flag
        buffSize.visible = flag
    }

    function quicVisible(flag){
        cert.visible = flag
        certText.visible = flag
        serverNameText.visible = flag
        serverName.visible = flag
    }

    GridLayout {
        columns: 2
        anchors.fill: parent
        anchors.margins: 10
        columnSpacing: 10

        Label {
            text: "协议"
        }
        ComboBox {
            id: protocol
            model: ["tcp", "quic"]
            onActivated: {
                if(index == 0) {
                    tcpVisible(true)
                    quicVisible(false)
                } else {
                    tcpVisible(false)
                    quicVisible(true)
                }
            }
        }

        Label {
            text: "名称"
        }
        TextField {
            id: name
        }

        Label {
            text: "IP地址"
        }
        TextField {
            id: host
        }

        Label {
            id: keyText
            text: "密钥"
        }
        TextField {
            id: key
        }

        Label {
            id: connectionsText
            text: "连接数"
        }
        TextField {
            id: connections
            validator: IntValidator {bottom: 1}
        }

        Label {
            id: buffSizeText
            text: "缓冲队列容量"
        }
        TextField {
            id: buffSize
            validator: IntValidator {bottom: 1}
        }

        Label {
            id: certText
            visible:false
            text: "SSL证书"
        }

        Button {
            visible: false
            id: cert
            text:"浏览..."
            onClicked: {
                certDialog.open();
            }
        }


        FileDialog {
            visible: false
            id: certDialog
            title: "选择文件"
            selectExisting: true
            selectFolder: false
            selectMultiple: false
            onAccepted:{
                fileurl = certDialog.fileUrl.toString();
                var str= fileurl.slice(0, 10)
                cert.text = str +"..."
            }

            onRejected: {
                cert.text = "浏览..."
            }
        }

        Label {
            visible: false
            id: serverNameText
            text: "server name"
        }

        TextField {
            visible: false
            id: serverName
        }
    }
}
