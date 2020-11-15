#ifndef QMLCPPBRIDGE_H
#define QMLCPPBRIDGE_H

#include <QObject>
#include <QJsonArray>
#include <QJsonObject>
#include <QString>

class QmlCppBridge : public QObject
{
    Q_OBJECT
public:
    explicit QmlCppBridge(QObject *parent = nullptr);
    Q_INVOKABLE QJsonArray init();
    Q_INVOKABLE QJsonArray selectList();
    Q_INVOKABLE QJsonObject select(QString name);
    Q_INVOKABLE void remove(QString name);
    Q_INVOKABLE void update(QJsonObject json);

signals:

};

#endif // QMLCPPBRIDGE_H
