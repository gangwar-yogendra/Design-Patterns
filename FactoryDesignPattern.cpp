/*
	Example of 'Factory' Design Pattern in C++
	Detail please refer the below link:-
	https://www.geeksforgeeks.org/design-patterns-set-2-factory-method/
*/

#include <iostream>

class Vehicle
{
public:
    virtual void printVehicle()=0;
};

class Twowheeler:public Vehicle
{
public:
    void printVehicle()
    {
        std::cout<<"Twowheeler\n";
    }
};

class Fourwheeler:public Vehicle
{
public:
    void printVehicle()
    {
        std::cout<<"Fourwheeler\n";
    }
};

class VehicleFactory
{
private:
    Vehicle *pVehicle;
public:
	~VehicleFactory() { 
        if(pVehicle) {
            delete pVehicle;
            pVehicle = NULL;
        }
    }
    Vehicle* getVehicleType(int index)
    {
        if(index == 1) {
            pVehicle = new Twowheeler;
        }
        else if(index == 2)
        {
            pVehicle = new Fourwheeler;
        }
        else {
            pVehicle = NULL;
        }
		
        return pVehicle;
    }
};

int main()
{
    VehicleFactory *factory = new VehicleFactory();
    Vehicle* pTwo = factory->getVehicleType(1);
    pTwo->printVehicle();
	
    Vehicle* pFour = factory->getVehicleType(2);
    pFour->printVehicle();
	
    Vehicle* pFour1 = factory->getVehicleType(3);
    if(pFour1) {
        pFour1->printVehicle();
    }
	
    return 0;
}