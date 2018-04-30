/*	Decorate Pattern for booking a Tennis court with
	extra facility like ballpack and tennis racket 
*/
#include <iostream>
#include <string>

using namespace std;

// Main class for court booking
class CourtBooking
{
	public:
		virtual string serve() = 0;
		virtual float cost() = 0;
};

// Initially provides the services for court booking
class HardCourtBooking: public CourtBooking
{
	public:
		string serve() {
			return "HardCourt";
		}
		float cost()
		{
			return 500;
		}
};


// Initially provides the services for court booking
class ClayCourtBooking: public CourtBooking
{
	public:
		string serve() {
			return "ClayCourt";
		}
		float cost()
		{
			return 700;
		}			
};


// Decorator class
class TennisDecorator: public CourtBooking
{
	protected:
		CourtBooking *m_courtBooking;
	public:
		TennisDecorator(CourtBooking *baseCourtBooking):m_courtBooking(baseCourtBooking)
		{			
		}
		
		string serve()
		{
			return m_courtBooking->serve();
		}
		
		float cost()
		{
			return m_courtBooking->cost();
		}
		
};

// Now needs Ballpack with tennis court
class BallPack: public TennisDecorator
{
	public:
		BallPack(CourtBooking *baseCourtBooking):TennisDecorator(baseCourtBooking)
		{
		}
		
		string serve()
		{
			return m_courtBooking->serve() + " with ball pack";
		}
		
		float cost()
		{
			return m_courtBooking->cost() + 400;
		}
};


// Now needs Racket of some cost with court booking
class Racket: public TennisDecorator
{
	public:
		Racket(CourtBooking *baseCourtBooking):TennisDecorator(baseCourtBooking)
		{
		}
		
		string serve()
		{
			return m_courtBooking->serve() + " with tennis racket";
		}
		
		float cost()
		{
			return m_courtBooking->cost() + 500;
		}
};

int main()
{
	CourtBooking *baseCourtBooking = new HardCourtBooking;
	cout<<"Basic Hard court booking:"<<"\n";
	cout<<baseCourtBooking->serve()<<" "<<baseCourtBooking->cost();
	cout<<"\n";
	cout<<"\n";
	
	CourtBooking *C_baseCourtBooking = new ClayCourtBooking;
	cout<<"Basic clay court booking:"<<"\n";
	cout<<C_baseCourtBooking->serve()<<" "<<C_baseCourtBooking->cost();
	cout<<"\n";
	cout<<"\n";
	
	cout<<"HardCourt + BallPack:"<<"\n";
	CourtBooking *ballPackBooking = new BallPack(baseCourtBooking);
	cout<<ballPackBooking->serve()<<" "<<ballPackBooking->cost();
	cout<<"\n";
	cout<<"\n";
	
	delete ballPackBooking;
	
	
	cout<<"ClayBooking + Racket:"<<"\n";
	CourtBooking *racketClayBooking = new Racket(C_baseCourtBooking);
	cout<<racketClayBooking->serve()<<" "<<racketClayBooking->cost();
	
	cout<<"\n";
	
	delete racketClayBooking;
	delete baseCourtBooking;
	delete C_baseCourtBooking;
	
	return 0;
}