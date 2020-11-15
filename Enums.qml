import QtQuick 2.15

Item {
    enum CellView {
        SimpleText = 0,
        GenderCell,
        CommandButton,
        ProgressView
    }

    enum Commands {
        DoCmd1 = 1,
        DoCmd2
    }

    enum Cmd {
        OPEN,
        EDIT
    }
}
