
#include <boost/python.hpp>
#include <iostream>
#include <string>



namespace daf{ // Avoid cluttering the global namespace.

	using namespace std;

	class Shape {
	protected:
		int width, height;
	public:
		Shape( int a=0, int b=0)
		{
			width = a;
			height = b;
		}
		int area()
		{
			cout << "Parent class area :" <<endl;
			return 0;
		}
	};
	class Rectangle: public Shape{
	public:
		Rectangle( int a=0, int b=0):Shape(a, b) { }
		int area ()
		{
			cout << "Rectangle class area :" <<endl;
			return (width * height);
		}
	};
	class Triangle: public Shape{
	public:
		Triangle( int a=0, int b=0):Shape(a, b) { }
		int area ()
		{
			cout << "Triangle class area :" <<endl;
			return (width * height / 2);
		}
	};

	//a simple struct
	struct Element
	{
		void setN(int N) {this->NTime = N;};
		int getN() {return NTime;};
		int NTime {0};
		char joy;
	};

	// a class with default constructor
	class World
	{
	public:
		World(Element& ele) {this->mTimer = ele.NTime;};
		void set(std::string msg) { this->msg = msg; }
		std::string greet() { return msg; }
		std::string msg;
		int getMyTimer() { return this->mTimer;};
		int mTimer;
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
//		myHello(const std::string& country, int t) {this->country = country; T = t;};
		std::string myWarmGreeting() {return "this is my warm hello from " + country;};
		int T;
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
				.add_property("joy", &Element::joy)
				;

		class_<World>("World",init<Element&>())
				.def("greet", &World::greet)
				.def("set", &World::set)
				.def("getMyTimer", &World::getMyTimer)
				;

		// Create the Python type object for our extension class and define __init__ function.
		class_<hello>("hello", init<std::string&>())
				.def("greet", &hello::greet)  // Add a regular member function.
				.def("invite", invite);  // Add invite() as a regular function to the module.

//         class_<myHello, bases<hello> >("myHello", init<std::string&>())
//                .def("myWarmGreeting", &myHello::myWarmGreeting);
		//expose funcitons
		def("invite", invite); // invite() can also be made a member of module!!!
		def("square", square);

//	    class_<myHello, bases<hello> >("myHello", init)
		//        .def("myWarmGreeting",&myHello::myWarmGreeting);


		// expose derived class
		class_<Rectangle>("Rectangle",init<int,int>())
				.def("area", &Rectangle::area)
				;

	}

}
