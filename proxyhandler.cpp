#include "proxyhandler.h"
#include <QProcess>
#include <QQmlEngine>
#include <QQmlComponent>
#include <QMetaObject>

QObject *context;

ProxyHandler::ProxyHandler(QObject *parent) : QObject(parent){
    QQmlComponent component(new QQmlEngine, "LogDialog.qml");
    context = component.create();
}

void ProxyHandler::execute() {
    qDebug() << "execute";
    QProcess process;

//    QString program = "rs-proxy.exe";
    QString program = "C:/Users/xutia/Desktop/rs-proxy-dic/rs-proxy.exe";
    process.start(program, QStringList() << "client" << "config.yaml");
    auto flag = process.waitForStarted();

    if(!flag) {
        qDebug() << "process error";
    }

    QTextStream textStream(&process);

    while (process.waitForReadyRead()) {
        while (!textStream.atEnd()) {
            auto str = textStream.readLine();
            QMetaObject::invokeMethod(context, "logAppend", Q_ARG(QString, str));
        }
    }
}
