
#include <boost/python.hpp>
#include <iostream>
#include <string>

namespace { // Avoid cluttering the global namespace.

	//a simple struct
	struct Element
	{
		void setN(int N) {this->NTime = N;};
		int getN() {return NTime;};
		int NTime {0};
	};

	// a class with default constructor
	class World
	{
	public:
		World() {};
		void set(std::string msg) { this->msg = msg; }
		std::string greet() { return msg; }
		std::string msg;
	};
	// A base class with constructor.
	class hello
	{
	public:
		hello(const std::string& country) { this->country = country; }
		std::string greet() const { return "Hello from " + country; }
	protected:
		std::string country;
	};

	// derived class with default constructor
	class myHello : public hello
	{
	public:
		std::string myWarmGreeting() {return "this is my warm hello from " + country;};
	};

	// A function taking a hello object as an argument.
	std::string invite(const hello& w) {
		return w.greet() + "! Please come soon!";
	}

	int square (int n)
	{
		return n*n;
	}

	BOOST_PYTHON_MODULE(hello_ext)
	{
		using namespace boost::python;

		// expose the struct
		class_<Element>("Element")
				.def("setN", &Element::setN)
				.def("getN", &Element::getN)
				;

		// expose a class with default constructor
		class_<World>("World")
				.def("greet", &World::greet)
				.def("set", &World::set)
				;

		// Create the Python type object for our extension class and define __init__ function.
		class_<hello>("hello", init<std::string>())
				.def("greet", &hello::greet)  // Add a regular member function.
				.def("invite", invite);  // Add invite() as a regular function to the module.

//         class_<myHello, bases<hello> >("myHello", init<std::string>())
//                .def("myWarmGreeting", &myHello::myWarmGreeting);
		//expose funcitons
		def("invite", invite); // invite() can also be made a member of module!!!
		def("square", square);

//	    class_<myHello, bases<hello> >("myHello", init)
		//        .def("myWarmGreeting",&myHello::myWarmGreeting);


	}

}
