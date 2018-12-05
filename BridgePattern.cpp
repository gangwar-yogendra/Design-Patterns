/* 
	Create a shape and fill with different color
	referenceLink: https://www.youtube.com/watch?v=7BIdsD34-pg
*/

#include <iostream>

using namespace std;

/* Color Interface class */
class Color
{	
	public:
		Color(){ };
		~Color(){ };
		virtual void fillColor() = 0;		
};

class Red: public Color
{
	public:
		Red(){ };
		~Red(){ };
		
		void fillColor() {
			std::cout<<" fill with red color"<<std::endl;
		}
};

/* Subclass of interface KickBehavior */
class Green: public Color
{
	public:
		Green() {	};
		~Green() { };
		
		void fillColor() {
			std::cout<<" fill with green color"<<std::endl;
		}
};


//<<Interface>>
//Shape Interface class
class Shape
{
	public:
		Shape() {}
		~Shape() {}
		virtual void colorIt()=0;
		virtual void drawIt()=0;
};

// Bridge class of Shape and Color interface
class BridgeClass:public Shape
{
	private:
		Color *_color;
	public:
		BridgeClass(Color *c):_color(c){}
		
		virtual void colorIt()
		{
			_color->fillColor();
		}
};

class Circle: public BridgeClass
{
	public:
		Circle(Color *c):BridgeClass(c) {}
		void colorIt()
		{
			BridgeClass::colorIt();
		}
		
		void drawIt()
		{
			cout<<"Circle";
		}
};

class Square:public BridgeClass
{
	public:
		Square(Color *c):BridgeClass(c) {}
		void colorIt()
		{
			BridgeClass::colorIt();
		}
		
		void drawIt()
		{
			cout<<"Square";
		}
};

int main()
{
	Color *_cr = new Red();
	Color *_cg = new Green();
	
	Shape *_sh = new Square(_cr);
	_sh->drawIt();
	_sh->colorIt();
	
	Shape *_sh1 = new Circle(_cg);
	_sh1->drawIt();
	_sh1->colorIt();		
	
	delete _sh1;
	delete _sh;
	delete _cr;
	delete _cg;
}