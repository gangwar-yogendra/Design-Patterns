/* 
	This is an example of a game with different fighters and
	the different behavior of fight for each fighter
	referenceLink: https://www.geeksforgeeks.org/strategy-pattern-set-2/
*/

#include <iostream>


class KickBehavior
{	
	public:
		KickBehavior(){ };
		~KickBehavior(){ };
		virtual void kick() = 0;		
};

class HighKick: public KickBehavior
{
	public:
		HighKick(){ };
		~HighKick(){ };
		
		void kick() {
			std::cout<<"High Kick"<<std::endl;
		}		
};

class LowKick: public KickBehavior 
{
	public:
		LowKick() {	};
		~LowKick() { };
		
		void kick() {
			std::cout<<"Low Kick"<<std::endl;
		}
};


class JumpBehavior
{
	public:
		JumpBehavior() {
		};
		~JumpBehavior() {
		};
		
		virtual void jump() = 0;
};

class HighJump: public JumpBehavior
{
	public:
		HighJump() {
		};
		~HighJump() {
		};
		
		void jump() {
			std::cout<<"High Jump"<<std::endl;
		}
};

class LowJump: public JumpBehavior
{
	public:
		LowJump() {
		};
		~LowJump() {
		};
		
		void jump() {
			std::cout<<"Low Jump"<<std::endl;
		}
};

// Abstract Fighter (main) class
class Fighter
{
	private:
		KickBehavior *b_kick;
		JumpBehavior *b_jump;
		
	public:
		Fighter():b_kick(NULL), b_jump(NULL) {};
		Fighter(KickBehavior *m_kick, JumpBehavior *m_jump):b_kick(m_kick), b_jump(m_jump) { }
		virtual ~Fighter() { }
		
		void punch()
		{
			std::cout<<"Default Punch"<<std::endl;
		}
		
		void kick()
		{
			b_kick->kick();
		}
		
		void jump()
		{
			b_jump->jump();
		}
		
		virtual void display() = 0;		
};

class FighterTypeA: public Fighter
{
	public:
		FighterTypeA(KickBehavior *m_kick, JumpBehavior *m_jump): Fighter(m_kick, m_jump) {
		}
		void display()
		{
			std::cout<<"FighterTypeA"<<std::endl;
		}
};

class FighterTypeB: public Fighter
{
	public:
		FighterTypeB(KickBehavior *m_kick, JumpBehavior *m_jump): Fighter(m_kick, m_jump) {
		}
		
		void display()
		{
			std::cout<<"FighterTypeB"<<std::endl;
		}
};

int main(int argc, char **argv)
{	
	KickBehavior *kickBehaviorA = new HighKick;
	JumpBehavior *jumpBehaviorA = new LowJump;	
	Fighter *fighterA = new FighterTypeA(kickBehaviorA, jumpBehaviorA);
	fighterA->display();
	fighterA->punch();
	fighterA->kick();
	fighterA->jump();
	
	
	std::cout<<"\n";
	JumpBehavior *jumpBehaviorB = new HighJump;
	KickBehavior *kickBehaviorB = new HighKick;
	Fighter *fighterB = new FighterTypeB(kickBehaviorB, jumpBehaviorB);
	fighterB->display();
	fighterB->punch();
	fighterB->kick();
	fighterB->jump();

	delete kickBehaviorA;
	delete kickBehaviorB;
	delete jumpBehaviorA;
	delete jumpBehaviorB;
	
	delete fighterA;
	delete fighterB;
	
	return 0;
}

