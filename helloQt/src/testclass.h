#include <QDebug>
#include <QString>
#include <QObject>

class testclass : public QObject
{
   Q_OBJECT
public:
    testclass(const QString& path = QString());
    const char* output();
    virtual ~testclass();
    QString getPath() {return msg;};

private:
    QString msg;
};

