#include "testclass.h"

testclass::testclass(const QString& path)
{
    msg = path;
}

testclass::~testclass()
{
}

const char* testclass::output()
{
    qDebug() << msg;
    return "hello";
}
