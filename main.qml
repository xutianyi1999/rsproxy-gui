import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import BppTableModel 0.1
import BppTable 0.1
import mycpp 1.0

ApplicationWindow {
    height: 500
    width: 600

    maximumHeight: height
    maximumWidth: width

    minimumHeight: height
    minimumWidth: width
    visible:true

    ConfigHandler{
        id: configHandler
    }

    ProxyHandler {
        id: proxyHandler
    }

    NodeDialog {
        id: nodeDialog
    }

    LogDialog {
        id: logDialog
    }

    Dialog {
        id: settingDialog
        x: parent.width / 2 - width / 2
        y: parent.height / 2 - height / 2
        width: 350
        title: "设置"
        standardButtons:  Dialog.Save | Dialog.Cancel

        GridLayout {
            columns: 2
            anchors.fill: parent
            anchors.margins: 10
            columnSpacing: 20

            Label {
                text: "socks5监听地址"
            }
            TextField {
                selectByMouse: true
                Layout.fillWidth: true
                id: host
            }
        }

        function init(_host) {
           host.text = _host
        }

        onAccepted: {
            configHandler.updateHost(host.text)
        }
    }

    Connections{
        target: worker
        onEnd: switch1.checked = false
    }

    ColumnLayout {
        id: gridLayout
        anchors.fill: parent
        anchors.margins: 10

        RowLayout{
            Layout.fillWidth: true

            Switch {
                id: switch1
                x: 40
                y: 42
                display: AbstractButton.TextBesideIcon
                onClicked: {
                    if (switch1.checked) {
                        var rows = bGrid.getSelectedRows()

                        var nameList = []
                        for (var i = 0; i < rows.length; i++) {
                            nameList.push(bGrid.cellValue(rows[i], 2))
                        }
                        configHandler.writeTemp(nameList)
                        proxyHandler.proxyStart()
                    } else {
                        proxyHandler.proxyStop()
                    }
                }
            }

            Button {
                id: button
                x: 475
                y: 42
                text: "设置"
                onClicked: {
                    settingDialog.init(configHandler.getHost())
                    settingDialog.open()
                }
            }
        }

        ListModel{
            id: modColumns
            ListElement { width: 40; title: ""; view: Enums.CellView.CommandButton; command: Enums.Commands.DoCmd2; dataRef1: "name" }
            ListElement { width: 40; title: ""; view: Enums.CellView.CommandButton; command: Enums.Commands.DoCmd1; dataRef1: "name" }
            ListElement { role: "name"; title: "名称"; width: 150 }
            ListElement { role: "protocol"; title: "协议"; width: 120 }
            ListElement { role: "host"; title: "主机地址"; width: 224 }
        }

        CompGrid {
            id: bGrid
            Layout.fillWidth: true
            Layout.fillHeight: true
            withMultiselection: true
            showOptionsButton: false
            dataHeight: 40

            RoundButton {
                id: roundButton
                x: 510
                y: 352
                width: 62
                height: 60
                text: "+"
                flat: false
                autoRepeat: false
                highlighted: true
                clip: false
                font.pointSize: 20
                font.weight: Font.Normal
                font.strikeout: false
                font.underline: false
                font.italic: false
                font.bold: true
                onClicked: {
                    nodeDialog.init(Enums.Cmd.OPEN, null)
                    nodeDialog.open()
                }
            }

            Component {
                id: cellDelegate

                Rectangle {
                    id: cellContainer
                    implicitHeight: bGrid.dataHeight
                    color: bGrid.getCellBk(row, highlight)
                    visible: model.visible

                    CellText {
                        visible: view === Enums.CellView.SimpleText
                        text: bGrid.formatDisplay(display, dataType, 2)
                        horizontalAlignment: bGrid.getAlign(dataType)
                        font.capitalization: Font.Capitalize
                    }

                    CellClicker {
                        grid: bGrid
                        linkEnabled: view === Enums.CellView.CommandButton
                        onDoCommand: {
                            var deleteCmd = 1
                            var editCmd = 2

                            if (command === deleteCmd) {
                                configHandler.remove(ref1)
                                bGrid.fillFromJson(configHandler.selectList())
                            } else {
                                var json = configHandler.select(ref1)
                                nodeDialog.init(Enums.Cmd.EDIT, json)
                                nodeDialog.open()
                            }
                        }
                    }

                    ButtonAction {
                        visible: view === Enums.CellView.CommandButton
                        commandId: command
                    }
                }
            }

            cellDelegate: cellDelegate

            fromListModel: modColumns

            Component.onCompleted: {
                bGrid.fillFromJson(configHandler.init());
            }
        }
    }

    Button {
        id: logConsole
        x: 490
        y: 10
        text: "日志"
        onClicked: logDialog.open()
    }
}
