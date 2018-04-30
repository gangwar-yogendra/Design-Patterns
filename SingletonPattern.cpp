/* Thread safe Singleton pattern */
#include <iostream>
#include <semaphore.h>
#include <pthread.h>

sem_t mutex;

class Singleton
{
	private:
		int value;
		static Singleton *_reference;
		Singleton() { }		
		Singleton(const Singleton &rhs) { }
		Singleton & operator =(const Singleton &rhs) { }
		
	public:
		static Singleton *getReference();
		void setValue(int x)
		{
			value = x;			
		}
		
		int getValue()
		{
			return value;
		}
};

Singleton *Singleton::_reference = 0;

Singleton *Singleton::getReference()
{
	if(_reference == NULL)
	{
		sem_wait(&mutex);
		if(_reference == NULL)
		{
			_reference = new Singleton;			
		}
		sem_post(&mutex);
	}	
	return _reference;
}

void* SetFirst(void*)
{
	Singleton::getReference()->setValue(100);
	std::cout << "SetFirst: " << Singleton::getReference()->getValue() << "\n";
}

void* SetSecond(void*)
{
	Singleton::getReference()->setValue(200);
	std::cout << "SetSecond: " << Singleton::getReference()->getValue() << "\n";
}


int main()
{
	Singleton::getReference()->setValue(0);
	std::cout << "Main: " << Singleton::getReference()->getValue() << "\n";
	pthread_t tid1;
	pthread_t tid2;
	
	sem_init(&mutex, 0, 1);
	
	pthread_create(&tid1, NULL, SetFirst, NULL);
	pthread_create(&tid1, NULL, SetSecond, NULL);
	
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
		
	sem_destroy(&mutex);
	pthread_exit(0);
	return 0;
}