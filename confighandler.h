#ifndef QMLCPPBRIDGE_H
#define QMLCPPBRIDGE_H

#include <QObject>
#include <QJsonArray>
#include <QJsonObject>
#include <QString>

class ConfigHandler : public QObject
{
    Q_OBJECT

public:
    explicit ConfigHandler(QObject *parent = nullptr);
    ~ConfigHandler();
    Q_INVOKABLE QJsonArray init();
    Q_INVOKABLE QString getHost();
    Q_INVOKABLE void updateHost(QString host);
    Q_INVOKABLE QJsonArray selectList();
    Q_INVOKABLE QJsonObject select(QString name);
    Q_INVOKABLE void remove(QString name);
    Q_INVOKABLE void update(QJsonObject json);

    Q_INVOKABLE void writeTemp(QVector<QString> nameList);
signals:
};

#endif // QMLCPPBRIDGE_H
