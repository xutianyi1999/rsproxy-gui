#include "worker.h"
#include <QProcess>
#include <QProcess>
#include <QTextStream>
#include <QDebug>
#include <QTextCodec>

QTextCodec* codec = QTextCodec::codecForName("System");
QProcess *process = nullptr;

Worker::~Worker() {
    if (process != nullptr) {
        process->kill();
        delete process;
    }
}

void Worker::run() {
    if (process == nullptr) {
        process = new QProcess;
    }
//    QString program = "rs-proxy.exe";
    QString program = "C:/Users/xutia/Desktop/rs-proxy-dic/rs-proxy.exe";
    process->start(program, QStringList() << "client" << "config.yaml");
    auto flag = process -> waitForStarted();

    if(!flag) {
        qDebug() << "process error";
    }

    QTextStream textStream(process);

    while (process->waitForReadyRead(-1)) {
        while (!textStream.atEnd()) {
            auto byte = textStream.readLine().toUtf8();
            auto str =codec->fromUnicode(byte);
            emit push(str);
        }
    }
}

void Worker::stop() {
    process->kill();
}