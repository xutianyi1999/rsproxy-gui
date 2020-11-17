#include "proxyhandler.h"
#include <QDebug>
#include <QThread>
#include "common.h"

void ProxyHandler::proxyStart() {
    WORKER->start();
}

void ProxyHandler::proxyStop(){
    WORKER->stop();
    WORKER->wait();
}
