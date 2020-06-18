#ifndef APPLICATION_H
#define APPLICATION_H
#include <QApplication>
#include <QSharedMemory>


class application : public QApplication
{
    Q_OBJECT
public:
    application(int &argc, char **argv);
    ~application();

    bool lock();

private:
    QSharedMemory *_singular; // shared memory !! SINGLE ACCESS
};

#endif // APPLICATION_H
