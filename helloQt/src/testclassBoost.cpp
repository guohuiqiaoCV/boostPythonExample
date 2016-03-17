#include <boost/python.hpp>
#include "testclass.h"

using namespace boost::python;

BOOST_PYTHON_MODULE(libhelloQt)
{
     class_<QObject, boost::noncopyable>("QObject");
     class_<QString>("QString",init<const char *>());

     class_<testclass,bases<QObject>, boost::noncopyable >("testclass",init<const QString &>())
        .def("output", &testclass::output)
        .def("getPath", &testclass::getPath)
        ;
 
}
