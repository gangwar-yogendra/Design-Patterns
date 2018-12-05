/* Prototype Design Pattern */
/* Reference Link: https://cppcodetips.wordpress.com/tag/prototype-design-pattern/ */
#include <string>
#include <list>
using namespace std;

class IPerson
{
public:
    virtual IPerson* Clone() = 0;
    IPerson(const string& sName, int id):m_sName(sName),m_ID(id) { }
    IPerson(const IPerson& person) { this->m_sName = person.m_sName;
                                     this->m_ID      = person.m_ID;
                                   }
    void SetName(const string& sName) { m_sName = sName; }
    void SetID(int ID)                { m_ID = ID;       }
private:
    string m_sName;
    int m_ID;
};
 
class Student: public IPerson
{
public:
    Student(const string& sName, int id):IPerson(sName, id)
    {
 
    }
    Student(const Student& student):IPerson(student)
    {
 
    }
 
    IPerson* Clone()
    {
        return new Student(*this);
    }
};
class Teacher: public IPerson
{
public:
    Teacher(const string& sName, int id):IPerson(sName, id)
    {
 
    }
 
    Teacher(const Teacher& teacher):IPerson(teacher)
    {
 
    }
 
    IPerson* Clone()
    {
        return new Teacher(*this);
    }
};
 
class University
{
public:
 
    University(const string& sName):m_sName(sName)
    {
 
    }
    University(const University& univ):m_sName(univ.m_sName){
        for (auto it = univ.m_Members.begin(); it != univ.m_Members.end(); it++)
            m_Members.push_back((*it)->Clone());
    }
    void AddMember( IPerson* ptr) { m_Members.push_back(ptr); }
private:
    list<IPerson*> m_Members;
    string m_sName;
};
 
 
int main()
{
    University* pUniversity = new University("Oxford");
    IPerson* ptr1 = new Student("Messi",1);
    IPerson* ptr2 = new Student("Ronaldo",2);
    IPerson* ptr3 = new Teacher("Scolari",3);
    pUniversity->AddMember(ptr1);
    pUniversity->AddMember(ptr2);
    pUniversity->AddMember(ptr3);
   // calls copy constructor of University class, which in turn calls Clone()  method of Iperson
    University* pUniversity2 = new University(*pUniversity);
	
	return 0;
}