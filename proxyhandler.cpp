#include "proxyhandler.h"
#include <QProcess>
#include <QQmlEngine>
#include <QQmlComponent>
#include <QMetaObject>

QObject *context;

ProxyHandler::ProxyHandler(QObject *parent) : QObject(parent){
    QQmlEngine engine;
    QQmlComponent component(&engine, "LogDialog.qml");
    context = component.create();
}

void ProxyHandler::execute() {
    QProcess process;
    process.start("rs-proxy.exe", QStringList() << "client" << "config.yaml");
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
