/*
    Object Pool Design Pattern 
    Reference: https://www.youtube.com/watch?v=4r0T0AHUcig&index=1&list=PLmCsXDGbJHdijIBjq-AXFWDTcUbl3f_s5
    Reference: https://sourcemaking.com/design_patterns/object_pool/cpp/1
*/


#include <iostream>
#include <list>
#include <string>
#include <pthread.h>

pthread_mutex_t mutex;

class Resource
{
private:
	int value;
public:
    Resource():value(0)
    {}
	void reset()
    {
        value = 0;
    }
    int getValue()
    {
        return value;
    }
    void setValue(int num)
    {
        value = num;
    }
};

/* Its an singleton class */
class ObjectPool
{
private:
    static ObjectPool *reference;
    std::list<Resource*> resources;
    ObjectPool(){}
    ObjectPool(const ObjectPool &obj){}
    ObjectPool& operator=(const ObjectPool& obj) {  
        return *this;
    }
	
public:
    /** 
        * Static method to access the class instance 
    */
    static ObjectPool* getReference() {
        if(reference == NULL)
        {
            pthread_mutex_lock(&mutex);
            if(reference == NULL)
            {
                reference = new ObjectPool();				
            }
            pthread_mutex_unlock(&mutex);
        }
        return reference;
    }
	
	/**
         * Returns instance of Resource.
         *
         * New resource will be created if all the resources
         * were used at the time of the request.
         *
         * @return Resource instance.
    */
    Resource* getResource()
    {
        if(resources.empty())
        {
            std::cout<<"Creating new Reusable object\n";
            return new Resource;
        }
        else
        {
            std::cout<<"Reusing existing reusable object\n";
            Resource* resource = resources.front();
            resources.pop_front();
            return resource;
        }
    }
	
	/**
         * Return resource back to the pool.
         *
         * The resource must be initialized back to
         * the default settings before someone else
         * attempts to use it.
         *
         * @param object Resource instance.
         * @return void
    */
    void returnResource(Resource* object)
    {
        object->reset();
        resources.push_back(object);
    }
	
};

ObjectPool* ObjectPool::reference = 0;

int main()
{
    ObjectPool* pool = ObjectPool::getReference();
	
    if(pthread_mutex_init(&mutex, NULL) != 0)
    {
        std::cout<<"\n mutex init has failed\n";
        return 1;
    }
	
    Resource* one;
    Resource* two;
    /* Resources will be created. */
    one = pool->getResource();
    one->setValue(10);
    std::cout << "one = " << one->getValue() << " [" << one << "]" << std::endl;
    two = pool->getResource();
    two->setValue(20);
    std::cout << "two = " << two->getValue() << " [" << two << "]" << std::endl;
    pool->returnResource(one);
    pool->returnResource(two);
    /* Resources will be reused.
     * Notice that the value of both resources were reset back to zero.
     */
    one = pool->getResource();
    std::cout << "one = " << one->getValue() << " [" << one << "]" << std::endl;
    two = pool->getResource();
    std::cout << "two = " << two->getValue() << " [" << two << "]" << std::endl;

	pthread_mutex_destroy(&mutex); 
    return 0;
}