#ifndef PROXYHANDLER_H
#define PROXYHANDLER_H

#include <QObject>

class ProxyHandler : public QObject
{
    Q_OBJECT
public:
    explicit ProxyHandler(QObject *parent = nullptr);

    void execute();
signals:

};

#endif // PROXYHANDLER_H
