#ifndef PROCESSVISION_H
#define PROCESSVISION_H
#include <QThread>

#include <QElapsedTimer>


class processVision: public QThread
{
    Q_OBJECT
public:

    explicit processVision(QObject *parent = 0);
    ~processVision();
    void    StartThread();
    void    StopThread();
    bool    m_bRun;
protected:

    void run();
signals:
    void ProcessLoop();

};

#endif // PROCESSVISION_H
