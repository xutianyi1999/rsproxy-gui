#include "proxyhandler.h"
#include <QProcess>
#include <QTextStream>
#include <QDebug>

ProxyHandler::ProxyHandler(QObject *parent) : QObject(parent){

}
void ProxyHandler::execute() {
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
            emit readyMsg(str);
        }
    }
}

void ProxyHandler::stop(){
    emit readyMsg("stop");
}
