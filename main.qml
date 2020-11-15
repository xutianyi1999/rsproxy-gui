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

    SettingDialog{
        id: settingDialog
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
                text: ""
                display: AbstractButton.TextBesideIcon
            }

            Button {
                id: button
                x: 475
                y: 42
                text: "设置"
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
                    settingDialog.init(Enums.Cmd.OPEN, null)
                    settingDialog.open()
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
                                qmlCppBridge.remove(ref1)
                                bGrid.fillFromJson(qmlCppBridge.selectList())
                            } else {
                                var json = qmlCppBridge.select(ref1)
                                settingDialog.init(Enums.Cmd.EDIT, json)
                                settingDialog.open()
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

            QmlCppBridge{
                id: qmlCppBridge
            }

            Component.onCompleted: {
                bGrid.fillFromJson(qmlCppBridge.init());
            }
        }
    }
}
