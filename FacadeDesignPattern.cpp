/* 	Provide a unified interface to a set of interfaces in a subsystem. 
	Facade defines a higher-level interface that makes the subsystem easier to use.
*/
#include <iostream>

using namespace std;

class A
{
	public:
		void funcA()
		{
			cout<<"funcA()"<<" ";
		}
		
		void funcB()
		{
			cout<<"funcB()"<<" ";
		}
};

class B
{
	public:
		void funcC()
		{
			cout<<"funcC()"<<" ";
		}
		
		void funcD()
		{
			cout<<"funcD()"<<" ";
		}
};


class C
{
	public:
		void funcE()
		{
			cout<<"funcE()"<<" ";
		}
		
		void funcF()
		{
			cout<<"funcF()"<<" ";
		}
};

class FasadeClass
{
	private:
		A &a;
		B &b;
		C &c;
	public:
		FasadeClass(A &_a, B &_b, C &_c):a(_a), b(_b), c(_c)
		{
			
		}
		
		void F1()
		{
			a.funcA();
			b.funcD();
			c.funcE();
		}
		
		void F2()
		{
			a.funcB();
			c.funcF();
			b.funcC();
		}
};

int main()
{
	A *_aa = new A();
	B *_bb = new B();
	C *_cc = new C();
	
	FasadeClass *f = new FasadeClass(*_aa, *_bb, *_cc);
	f->F1();
	cout<<"\n";
	f->F2();
	
	return 0;
}