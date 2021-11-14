/*
	Example of 'Strategy' Design Pattern in C++
	This is an example of a game with different fighters and
	the different behavior of fight for different fighters
	for detail please refer the below link:-
	https://www.geeksforgeeks.org/strategy-pattern-set-2/
*/

#include <iostream>

/* Interface class kick Behavior */
class KickBehavior
{
public:
	KickBehavior() { };
	~KickBehavior() { };
	virtual void kick() = 0;
};

/* Subclass of interface KickBehavior */
class HighKick : public KickBehavior
{
public:
	HighKick() { };
	~HighKick() { };

	void kick() {
		std::cout << "High Kick" << std::endl;
	}
};

/* Subclass of interface KickBehavior */
class LowKick : public KickBehavior
{
public:
	LowKick() {	};
	~LowKick() { };

	void kick() {
		std::cout << "Low Kick" << std::endl;
	}
};

/* Subclass of interface KickBehavior */
class NoKick : public KickBehavior
{
public:
	NoKick() {	};
	~NoKick() { };

	void kick() {
		std::cout << "Not allow to Kick" << std::endl;
	}
};


// Abstract Fighter (main) class
// Composition with Interfaces
class Fighter
{
private:
	KickBehavior* b_kick;

public:
	Fighter() :b_kick(NULL) {};
	Fighter(KickBehavior* m_kick) :b_kick{ m_kick } { }
	virtual ~Fighter() { }

	void setKick(KickBehavior* kick)
	{
		b_kick = kick;
	}

	void kick()
	{
		b_kick->kick();
	}

	void punch()
	{
		std::cout << "Default Punch" << std::endl;
	}

	virtual void display() = 0;
};

class FighterTypeA : public Fighter
{
public:
	FighterTypeA(KickBehavior* m_kick) : Fighter(m_kick) {
	}
	void display()
	{
		std::cout << "FighterTypeA" << std::endl;
	}
};

class FighterTypeB : public Fighter
{
public:
	FighterTypeB(KickBehavior* m_kick) : Fighter(m_kick) { 	}

	void display()
	{
		std::cout << "FighterTypeB" << std::endl;
	}
};

int main(int argc, char** argv)
{
	KickBehavior* kickBehaviorA = new HighKick;

	Fighter* fighterA = new FighterTypeA(kickBehaviorA);
	fighterA->display();
	fighterA->punch();
	fighterA->kick();


	std::cout << "\n";
	KickBehavior* kickBehaviorB = new NoKick;
	Fighter* fighterB = new FighterTypeB(kickBehaviorB);
	fighterB->display();
	fighterB->punch();
	fighterB->kick();

	delete kickBehaviorA;
	delete kickBehaviorB;

	delete fighterA;
	delete fighterB;

	return 0;
}
