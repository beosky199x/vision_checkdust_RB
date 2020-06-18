#include "mainwindow.h"
#include <QApplication>
#include "processcam.h"

//29032019
class Application final : public QApplication {
public:

    Application(int& argc, char** argv) : QApplication(argc, argv) {}
    virtual bool notify(QObject *receiver, QEvent *event) override {
         // your code here
        try {
                return QApplication::notify(receiver, event);
            } catch (std::exception &e) {
                qFatal("Error %s sending event %s to object %s (%s)",
                    e.what(), typeid(*event).name(), qPrintable(receiver->objectName()),
                    typeid(*receiver).name());
            } catch (...) {
                qFatal("Error <unknown> sending event %s to object %s (%s)",
                    typeid(*event).name(), qPrintable(receiver->objectName()),
                    typeid(*receiver).name());
            }

            // qFatal aborts, so this isn't really necessary
            // but you might continue if you use a different logging lib
            return false;
    }
};

//29032019
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
