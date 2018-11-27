//: https://en.wikipedia.org/wiki/Observer_pattern
//: https://sourcemaking.com/design_patterns/observer/cpp/3

#include <iostream>
#include <vector>
#include <string>

class Observer;
// Subject Class
class Subject
{
public:
	virtual ~Subject(){}
	// Attach observer
	void Attached(Observer *obs){
		mObservers.push_back(obs);
	}
	// Detach observer
	virtual void Detach (Observer *obs)
	{
		int count = mObservers.size();
		
		int i;
		for(i = 0; i<count; i++)
		{
			if(mObservers[i] == 0)
				break;
			
			if(i < count)
			{
				mObservers.erase(mObservers.begin() + i);
			}
		}
	}
	
	void setValue(int x)
	{
		value = x;
		notify();
	}	
	
	int getValue()
	{
		return value;
	}
	
	// Notify observer
	void notify();

private:
	std::vector<Observer *> mObservers;
	int value;
};

class Observer
{
private:
	Subject *sub;
	int denom;
public:
	Observer(Subject *s, int div):sub(s), denom(div) {
		sub->Attached(this);
	}
	
	Subject *getSubject()
	{
		return sub;
	}
	
	int getDivisor()
	{
		return denom;
	}
	
	virtual void update() = 0;
};

void Subject::notify()
{
	int count = mObservers.size(); 

	for (int i = 0; i < count; i++) {
		(mObservers[i])->update();
	}
}

class ObserverA : public Observer
{
public:
	explicit ObserverA(Subject *s, int div) : Observer(s, div) {}
	void update()
	{
		int v = getSubject()->getValue();
		int d = getDivisor();
		std::cout << "v: " <<v << " d: "<< d << " divison: "<< v/d << std::endl;		
	}
};

class ObserverB : public Observer
{
public:
	explicit ObserverB(Subject *s, int div) : Observer(s, div) {}
	void update()
	{
		int v = getSubject()->getValue();
		int d = getDivisor();
		std::cout << "v: " <<v << " d: "<< d << " mod: "<< v%d << std::endl;		
	}
};

int main(int argc, char **argv) 
{
	Subject sub;
	Observer *obserA = new ObserverA(&sub, 3);
	Observer *obserB = new ObserverB(&sub, 5);
	
	sub.setValue(30);

	return 0;
}