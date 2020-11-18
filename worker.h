#ifndef WORKER_H
#define WORKER_H

#include <QThread>

class Worker : public QThread
{
    Q_OBJECT
public:
    ~Worker();
    void run() override;
    void stop();
signals:
    void pushMsg(QString msg);
    void end();
};

#endif // WORKER_H
