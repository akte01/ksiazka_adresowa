#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <windows.h>
#include <algorithm>

using namespace std;

class User
{
public:
    string userId, userName, userPassword;
    User(string userId, string userName, string userPassword);
};

class UserOptions
{
public:
    vector <User> users;
    void importUserData(vector <User> &users);
    void registerUser(vector <User> users);
    int logInUser(vector <User> &users);
    void changePassword(vector <User> &users, int loggedUserId);
};

class Person
{
public:
    string IdNumber, userId, name, lastName, phoneNumber, emailAddress, address;
    Person(string IdNumber, string userId, string name, string lastName, string phoneNumber, string emailAddress, string address);
};

class ContactOptions
{
    public:
    vector <Person> addressData;
    void importContactsForLoggedUsers(vector <Person> &addressData, int loggedUserId);
    void importAllContacts(vector <Person> &addressData);
    void addContact(vector <Person> &addressData, int loggedUserId);
    void searchContactByName(vector <Person> addressData);
    void searchContactByLastName(vector <Person> addressData);
    void showAllContacts(vector <Person> addressData);
    void editContact(vector <Person> &addressData, int loggedUserId);
    void removeContact(vector <Person> addressData, int loggedUserId);
    void getPersonalData(vector <string> &singleContact, string personalDataSeparatedByLine);
    int giveLastContactNumber (vector <Person> addressData);
    bool checkContactExistion(vector <Person> addressData, int contacktNumberForEditing);
    int givePositionInVector(vector <Person> addressData, int contacktNumberForEditing);
    void exportContactIntoFile(vector <Person> &addressDataForExport);
    void updateAddressData(vector <Person> &addressData);
};
