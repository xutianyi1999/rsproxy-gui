QT += quick
QT += quickcontrols2
CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
        qmlcppbridge.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

include(D:/cpp/code/bppgrid-master/BppTable.pri)
include(D:/cpp/code/bppgrid-master/BppFa.pri)


INCLUDEPATH += D:\cpp\code\yaml-cpp-yaml-cpp-0.6.3\include
LIBS += D:\cpp\code\build-yaml-cpp-yaml-cpp-0.6.3-Desktop_Qt_5_15_0_MinGW_64_bit-Release\libyaml-cpp.a

HEADERS += \
    qmlcppbridge.h
