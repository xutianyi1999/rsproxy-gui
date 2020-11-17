#ifndef PROXYHANDLER_H
#define PROXYHANDLER_H

#include <QObject>

class ProxyHandler : public QObject
{
    Q_OBJECT
public:
    Q_INVOKABLE void proxyStart();
    Q_INVOKABLE void proxyStop();
};

#endif // PROXYHANDLER_H
