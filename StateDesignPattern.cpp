//Vending machine designing code
//Link refer: https://medium.com/swlh/vending-machine-design-a-state-design-pattern-approach-5b7e1a026cd2


#include <iostream>
#include <string>
#include <map>
#include <set>

using namespace std;

class VendingMachine;

class State {
public:
    virtual void collectCash(int cash) = 0;
    virtual void dispenseChange(string productCode) = 0;
    virtual void dispenseItem(string productCode) = 0;
    virtual void cancelTransaction() = 0;
};

class VendingMachine {
private:
    int collectedCash;
    State* state;
    map<string, set<string>> productCodeItemMap;
    map<string, int> productCodePriceMap;

public:
    void addCollectedCash(int collectedCash) {
        this->collectedCash += collectedCash;
    }

    VendingMachine* setCollectedCash(int collectedCash) {
        this->collectedCash = collectedCash;
        return this;
    }

    State* getState() {
        return state;
    }

    VendingMachine* setState(State* state) {
        this->state = state;
        return this;
    }

    void removeProduct(string productCode) {

    }

    void dispenseChange(string productCode) {
        this->state->dispenseChange(productCode);
    }

    void cancelTransaction() {
        this->state->cancelTransaction();
    }

    int calculateChange(string productCode) {
        return collectedCash - productCodePriceMap.find(productCode)->second;
    }

    void dispenseItem(string productCode) {
        this->state->dispenseItem(productCode);
    }

    int getCollectedCash() {
        return collectedCash;
    }
};

class DispenseChange : public State
{
private:
    VendingMachine* vendingMachine;
public:
    DispenseChange(VendingMachine* vendingMachine) :vendingMachine{ vendingMachine } {}

    void collectCash(int cash) override {
        throw std::runtime_error("Dispense Change, Unable to collect the cash");
    }
    void dispenseChange(string productCode) override {
        int change = this->vendingMachine->calculateChange(productCode);
        std::cout << "Change of " << change << " returned";

        this->vendingMachine->setState(new DispenseItem(this->vendingMachine));
        this->vendingMachine->dispenseItem(productCode);
    }
    void dispenseItem(string productCode) override {
        throw std::runtime_error("Dispense Change, Unable to dispense item");
    }
    void cancelTransaction() override {
        throw std::runtime_error("Dispense Change, Unable to cancel transaction");
    }
};

class DispenseItem : public State
{
private:
    VendingMachine* vendingMachine;
public:
    DispenseItem(VendingMachine* vendingMachine) :vendingMachine{ vendingMachine } {}

    void collectCash(int cash) override {
        throw std::runtime_error("Dispense Change, Unable to collect the cash");
    }
    void dispenseChange(string productCode) override {
        throw std::runtime_error("Dispense Change, Unable to dispense change");
    }
    void dispenseItem(string productCode) override {
       
        this->vendingMachine->removeProduct(productCode);
        std::cout << "Dispense Item " << productCode << ".\n";

        this->vendingMachine->setState(new Ready(this->vendingMachine));
    }
    void cancelTransaction() override {
        throw std::runtime_error("Dispense Change, Unable to cancel transaction");
    }
};


class Ready : public State
{
private:
    VendingMachine* vendingMachine;
public:
    Ready(VendingMachine* vendingMachine) :vendingMachine{ vendingMachine } {}

    void collectCash(int cash) override {
        throw std::runtime_error("Dispense Change, Unable to collect the cash");
    }
    void dispenseChange(string productCode) override {
        throw std::runtime_error("Dispense Change, Unable to dispense change");
    }
    void dispenseItem(string productCode) override {
        throw std::runtime_error("Dispense Change, Unable to dispense Item");
    }
    void cancelTransaction() override {
        this->vendingMachine->setState(new TransactionCancelled(this->vendingMachine));
        this->vendingMachine->cancelTransaction();
    }
};

class TransactionCancelled : public State
{
private:
    VendingMachine* vendingMachine;
public:
    TransactionCancelled(VendingMachine* vendingMachine) :vendingMachine{ vendingMachine } {}

    void collectCash(int cash) override {
        throw std::runtime_error("Dispense Change, Unable to collect the cash");
    }
    void dispenseChange(string productCode) override {
        throw std::runtime_error("Dispense Change, Unable to dispense change");
    }
    void dispenseItem(string productCode) override {
        throw std::runtime_error("Dispense Change, Unable to dispense Item");
    }
    void cancelTransaction() override {
        cout << "Returned collected cash" << vendingMachine->getCollectedCash();
        this->vendingMachine->setState(new TransactionCancelled(this->vendingMachine));
        this->vendingMachine->cancelTransaction();
    }
};

int main()
{

}
