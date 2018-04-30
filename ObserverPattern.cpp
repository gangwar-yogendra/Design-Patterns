//: https://en.wikipedia.org/wiki/Observer_pattern
//: http://www.bogotobogo.com/DesignPatterns/observer.php

#include <iostream>
#include <vector>
#include <string>

// Observer class
class Observer
{
public:
	virtual ~Observer() {}
	virtual void update(int message) = 0;
};

// Subject Class
class Subject
{
public:
	virtual ~Subject();
	// Attach observer
	virtual void Attached(Observer *);
	// Detach observer
	virtual void Detach (Observer *);
	// Notify observer
	virtual void notify(int message);
private:
	std::vector<Observer *> mObservers;
};

Subject::~Subject()
{}

void Subject::Attached(Observer *observer)
{
	mObservers.push_back(observer);
}

void Subject::Detach(Observer *observer)
{
	int count = mObservers.size(); 
	int i; 

	for (i = 0; i < count; i++) { 
		if(mObservers[i] == 0) 
		break; 
	} 
	if(i < count) 
		mObservers.erase(mObservers.begin() + i);
}

void Subject::notify(int msg)
{
	int count = mObservers.size(); 

	for (int i = 0; i < count; i++) {
		(mObservers[i])->update(msg);
	}
}

class MySubject : public Subject
{
public:
	enum Message {ADD, REMOVE};
	void changeMessage(int value )
	{
		notify(value);
	}
};

class MyObserver : public Observer
{
public:
	explicit MyObserver(const std::string &str) : name(str) {}
	void update(int message)
	{
		std::cout << name << " Got message " << message << std::endl;
	}
private:
	std::string name;
};

int main(int argc, char **argv) 
{
	MyObserver observerA("observerA");
	MyObserver observerB("observerB");
	MyObserver observerC("observerC");

	MySubject subject;
	subject.Attached(&observerA);
	subject.Attached(&observerB);
	subject.Detach(&observerB);
	subject.Attached(&observerC);
	
	subject.changeMessage(MySubject::ADD);
	subject.changeMessage(MySubject::REMOVE);

	return 0;
}