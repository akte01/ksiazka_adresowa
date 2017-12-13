#include <iostream>
#include "kontakty.h"

using namespace std;

User::User(string userId, string userName, string userPassword)
{
    this -> userId = userId;
    this -> userName = userName;
    this -> userPassword = userPassword;
}

Person::Person(string IdNumber, string userId, string name, string lastName, string phoneNumber, string emailAddress, string address)
{
    this -> IdNumber = IdNumber;
    this -> userId = userId;
    this -> name = name;
    this -> lastName = lastName;
    this -> phoneNumber = phoneNumber;
    this -> emailAddress = emailAddress;
    this -> address = address;
}

string intToStringConversion(int IdNumber)
{
    ostringstream ss;
    ss << IdNumber;
    string str = ss.str();
    return str;
}

void ContactOptions::getPersonalData(vector <string> &singleContact, string personalDataSeparatedByLine)
{
    string singleContactDetails = "";
    int singleContactDetailsNumber = 1;

    for (int charPosition = 0; charPosition < personalDataSeparatedByLine.length(); charPosition++)
    {
        if (personalDataSeparatedByLine[charPosition] != '|')
        {
            singleContactDetails += personalDataSeparatedByLine[charPosition];
        }
        else
        {
            switch(singleContactDetailsNumber)
            {
            case 1:
                singleContact.push_back(singleContactDetails);
                break;
            case 2:
                singleContact.push_back(singleContactDetails);
                break;
            case 3:
                singleContact.push_back(singleContactDetails);
                break;
            case 4:
                singleContact.push_back(singleContactDetails);
                break;
            case 5:
                singleContact.push_back(singleContactDetails);
                break;
            case 6:
                singleContact.push_back(singleContactDetails);
                break;
            case 7:
                singleContact.push_back(singleContactDetails);
                break;
            }
            singleContactDetails = "";
            singleContactDetailsNumber++;
        }
    }
}
void ContactOptions::importAllContacts(vector <Person> &addressData)
{
    vector <string> singleContact;
    string personalDataSeparatedByLine = "";
    fstream contactDatabase;
    contactDatabase.open("kontakty.txt", ios::in);

    if (contactDatabase.good() == true)
    {
        while (getline(contactDatabase, personalDataSeparatedByLine))
        {
            ContactOptions collection;
            collection.getPersonalData(singleContact, personalDataSeparatedByLine);
            addressData.push_back(Person(singleContact[0], singleContact[1],
                                         singleContact[2], singleContact[3],
                                         singleContact[4], singleContact[5],
                                         singleContact[6]));
            singleContact.clear();
        }
        contactDatabase.close();
    }
}

int ContactOptions::giveLastContactNumber (vector <Person> addressData)
{
    ContactOptions import;
    import.importAllContacts(addressData);
    if (addressData.empty())
        return 0;
    else
    {
        int lastContactNumber = addressData.size() - 1;
        return atoi(addressData[lastContactNumber].IdNumber.c_str());
    }
}
void UserOptions::importUserData(vector <User> &users)
{
    string downloadedTextLine;
    int downloadedTextLineNumber = 1;
    fstream userDatabase;
    userDatabase.open("uzytkownicy.txt", ios::in | ios::app);
    if (userDatabase.good() == true)
    {
        while (getline(userDatabase, downloadedTextLine))
        {
            string userData;
            istringstream streamLine(downloadedTextLine);
            vector <string> singleUser;

            while(getline(streamLine, userData, '|'))
            {
                istringstream streamData(userData);
                string singleUserData;
                streamData >> singleUserData;
                singleUser.push_back(singleUserData);
            }
           users.push_back(User(singleUser[0], singleUser[1],
                                             singleUser[2]));
            downloadedTextLineNumber++;
        }
        userDatabase.close();
    }
}

int UserOptions::logInUser(vector <User> &users)
{
    system("cls");
    cout<< ">>>LOGOWANIE<<<" <<endl;
    cout<< "---------------" <<endl;
    cout<< endl;
    string userName, userPassword;
    cout<< "Podaj login: ";
    cin>> userName;
    int vectorPosition = 0;
    while(vectorPosition<users.size())
    {
        if (users[vectorPosition].userName == userName)
        {
            for(int attempt = 0; attempt < 3; attempt++)
            {
                cout<< "Podaj haslo. Pozostalo prob " << 3 - attempt << ": ";
                cin>> userPassword;
                cout<< endl;
                if (users[vectorPosition].userPassword == userPassword)
                {
                    cout<< "Zalogowales sie!" <<endl;
                    Sleep(1000);
                    return atoi(users[vectorPosition].userId.c_str());
                }
            }
            cout<< "Podaje 3 razy bledne haslo. Poczekaj 3 sekundy przed kolejna proba!" <<endl;
            Sleep(3000);
            return 0;
        }
        vectorPosition++;
    }
    cout<< "Nie ma takiego uzytkownika!" <<endl;
    Sleep(1500);
    return 0;
}

void UserOptions::registerUser(vector <User> users)
{
    system("cls");
    cout<< ">>>REJESTRACJA NOWEGO UZYTKOWNIKA<<<" <<endl;
    cout<< "------------------------------------" <<endl;
    cout<< endl;
    vector <User> usersForExport;
    string userName, userPassword, userId;
    cout<< "Podaj nazwe uzytkownika: ";
    cin>> userName;
    int vectorPosition = 0;
    while(vectorPosition < users.size())
    {
        if (users[vectorPosition].userName == userName)
        {
            cout<< "Taki uzytkownik istnieje. Podaj inna nazwe uzytkownika: ";
            cin>> userName;
            vectorPosition = 0;
        }
        else
        {
            vectorPosition++;
        }
    }
    cout<< "Podaj haslo: ";
    cin>> userPassword;
    userId = intToStringConversion(users.size() + 1);
    usersForExport.push_back(User(userId, userName, userPassword));
    fstream userDatabase;
    userDatabase.open("uzytkownicy.txt",ios::out|ios::app);
    if (userDatabase.good() == true)
    {
        for(int vectorPosition = 0; vectorPosition < usersForExport.size(); vectorPosition++)
        {
            userDatabase<< usersForExport[vectorPosition].userId + "|"
                            + usersForExport[vectorPosition].userName + "|"
                            + usersForExport[vectorPosition].userPassword + "|";
            userDatabase <<endl;
        }

        userDatabase.close();
        usersForExport.clear();
        cout<< endl;
        cout<< "Uzytkownik zostal dodany!" <<endl;
        Sleep(1500);
    }

    else
    {
        cout<< "Nie odnaleziono takiego pliku" <<endl;
        Sleep(1500);
    }
}


void ContactOptions::importContactsForLoggedUsers(vector <Person> &addressData, int loggedUserId)
{
    vector <string> singleContact;
    string personalDataSeparatedByLine = "";
    fstream contactDatabase;
    contactDatabase.open("kontakty.txt", ios::in);
    if (contactDatabase.good() == true)
    {
        while (getline(contactDatabase, personalDataSeparatedByLine))
        {
            getPersonalData(singleContact, personalDataSeparatedByLine);
            if (intToStringConversion(loggedUserId) == singleContact[1])
            {
                addressData.push_back(Person(singleContact[0], singleContact[1],
                                             singleContact[2], singleContact[3],
                                             singleContact[4], singleContact[5],
                                             singleContact[6]));
            }
            singleContact.clear();
        }
        contactDatabase.close();
    }
}

void ContactOptions::showAllContacts(vector <Person> addressData)
{
    system("cls");
    cout<< ">>>LISTA WSZYSTKICH KONTAKTOW<<<" <<endl;
    cout<< "--------------------------------" <<endl;
    cout<< endl;
    if (!addressData.empty())
    {
        for (int vectorPosition = 0; vectorPosition < addressData.size(); vectorPosition++)
        {
            cout<< addressData[vectorPosition].IdNumber <<endl;
            cout<< addressData[vectorPosition].name <<endl;
            cout<< addressData[vectorPosition].lastName <<endl;
            cout<< addressData[vectorPosition].phoneNumber <<endl;
            cout<< addressData[vectorPosition].emailAddress <<endl;
            cout<< addressData[vectorPosition].address <<endl;
        }
        system("pause");
    }
    else
    {
        cout << "Ksiazka adresowa jest pusta." <<endl;
        Sleep(1500);
    }
}
void ContactOptions::exportContactIntoFile(vector <Person> &addressDataForExport)
{
fstream contactDatabase;
    contactDatabase.open("kontakty.txt",ios::out|ios::app);
    if (contactDatabase.good() == true)
    {
        for(int vectorPosition = 0; vectorPosition < addressDataForExport.size(); vectorPosition++)
        {
            contactDatabase<< addressDataForExport[vectorPosition].IdNumber + "|" + addressDataForExport[vectorPosition].userId
                         + "|" + addressDataForExport[vectorPosition].name + "|" + addressDataForExport[vectorPosition].lastName
                         + "|" + addressDataForExport[vectorPosition].phoneNumber + "|" + addressDataForExport[vectorPosition].emailAddress
                         + "|" + addressDataForExport[vectorPosition].address + "|";
            contactDatabase <<endl;
        }

        contactDatabase.close();
        cout<< "Kontakt zostal dodany!"<<endl;
        Sleep(1500);
    }

    else
    {
        cout<<"Nie odnaleziono takiego pliku"<<endl;
        Sleep(1500);
    }
}
void ContactOptions::addContact(vector <Person> &addressData, int loggedUserId)
{
    system("cls");
    cout<< ">>>DODAJ NOWY KONTAKT<<<" <<endl;
    cout<< "------------------------" <<endl;
    cout<< endl;
    vector <Person> addressDataForExport;
    string name, lastName, phoneNumber, emailAddress, address;
    ContactOptions lastNumber;
    int contactNumber = lastNumber.giveLastContactNumber(addressData) + 1;
    string IdNumber = intToStringConversion(contactNumber);
    string loggedUserIdNumber = intToStringConversion(loggedUserId);

    cout<< "Podaj imie: ";
    cin>> name;

    cout<< "Podaj nazwisko: ";
    cin>> lastName;

    cout<< "Podaj numer telefonu: ";
    cin.sync();
    getline(cin, phoneNumber);

    cout<< "Podaj adres e-mail: ";
    cin>> emailAddress;

    cout<< "Podaj adres zamieszkania: ";
    cin.sync();
    getline(cin, address);

    addressDataForExport.push_back(Person(IdNumber, loggedUserIdNumber, name, lastName, phoneNumber, emailAddress, address));
    ContactOptions contactExport;
    contactExport.exportContactIntoFile(addressDataForExport);
}

void ContactOptions::searchContactByName(vector <Person> addressData)
{
    system("cls");
    cout<< ">>>WYSZUKAJ KONTAKT PO IMIENIU<<<" <<endl;
    cout<< "---------------------------------" <<endl;
    cout<< endl;
    string nameToCheck;
    cout<< "Podaj imie: ";
    cin>> nameToCheck;
    int vectorPosition = 0;
    while(vectorPosition < addressData.size())
    {
        if (addressData[vectorPosition].name == nameToCheck)
        {
            cout<< addressData[vectorPosition].IdNumber <<". "<< addressData[vectorPosition].name <<" "<< addressData[vectorPosition].lastName <<endl;
            Sleep(1500);
            vectorPosition++;
        }

        else
            vectorPosition++;
    }

    string selectedOption;
    cout<< "Wybierz kontakt lub wybierz 0, aby przejsc do menu glownego: ";
    cin>> selectedOption;

    for(int vectorPosition = 0; vectorPosition < addressData.size(); vectorPosition++)
    {
        if (addressData[vectorPosition].IdNumber == selectedOption)
        {
            cout<< addressData[vectorPosition].name <<" " <<addressData[vectorPosition].lastName <<endl;
            cout<< addressData[vectorPosition].phoneNumber <<endl;
            cout<< addressData[vectorPosition].emailAddress <<endl;
            cout<< addressData[vectorPosition].address <<endl;
            system("pause");
        }

        else if (selectedOption == "0")
            Sleep(500);
    }
}

void ContactOptions::searchContactByLastName(vector <Person> addressData)
{
    system("cls");
    cout <<">>>WYSZUKAJ KONTAKT PO NAZWISKU<<<" <<endl;
    cout <<"----------------------------------" <<endl;
    cout <<endl;
    string lastNameToCheck;
    cout <<"Podaj nazwisko: ";
    cin>> lastNameToCheck;
    int vectorPosition = 0;
    while(vectorPosition < addressData.size())
    {
        if (addressData[vectorPosition].lastName == lastNameToCheck)
        {
            cout<< addressData[vectorPosition].IdNumber <<". "<< addressData[vectorPosition].name <<" "<< addressData[vectorPosition].lastName <<endl;
            Sleep(1500);
            vectorPosition++;
        }

        else
            vectorPosition++;
    }

    string selectedOption;
    cout<< "Wybierz kontakt lub wybierz 0, aby przejsc do menu glownego: ";
    cin>> selectedOption;

    for(int vectorPosition = 0; vectorPosition < addressData.size(); vectorPosition++)
    {
        if (addressData[vectorPosition].IdNumber == selectedOption)
        {
            cout<< addressData[vectorPosition].name <<" " <<addressData[vectorPosition].lastName <<endl;
            cout<< addressData[vectorPosition].phoneNumber <<endl;
            cout<< addressData[vectorPosition].emailAddress <<endl;
            cout<< addressData[vectorPosition].address <<endl;
            system("pause");
        }

        else if (selectedOption == "0")
            Sleep(500);
    }
}

void UserOptions::changePassword(vector <User> &users, int loggedUserId)
{
    system("cls");
    cout<< ">>>ZMIANA HASLA<<<" <<endl;
    cout<< "------------------" <<endl;
    cout<< endl;
    string newUserPassword;
    cout<< "Podaj nowe haslo: ";
    cout<< endl;
    cin>> newUserPassword;
    for(int vectorPosition = 0; vectorPosition < users.size(); vectorPosition++)
    {
        if (users[vectorPosition].userId == intToStringConversion(loggedUserId))
        {
            users[vectorPosition].userPassword = newUserPassword;
        }
    }
    fstream userDatabase;
    userDatabase.open("uzytkownicy.txt",ios::out);
    if (userDatabase.good() == true)
    {
        for(int vectorPosition = 0; vectorPosition < users.size(); vectorPosition++)
        {
            userDatabase<< users[vectorPosition].userId + "|"
                            + users[vectorPosition].userName + "|"
                            + users[vectorPosition].userPassword + "|";
            userDatabase <<endl;
        }
        userDatabase.close();
        cout<< "Haslo zostalo zmienione!" <<endl;
        Sleep(1500);
    }
    else
    {
        cout<< "Nie odnaleziono takiego pliku" <<endl;
        Sleep(1500);
    }
}

bool ContactOptions::checkContactExistion(vector <Person> addressData, int contacktNumberForEditing)
{
    vector <string> idNumbers;
    for(int vectorPosition = 0; vectorPosition < addressData.size(); vectorPosition++)
    {
        idNumbers.push_back(addressData[vectorPosition].IdNumber);
    }

    vector <string> ::iterator itr;
    itr = find (idNumbers.begin(), idNumbers.end(), intToStringConversion(contacktNumberForEditing));
    if (itr != idNumbers.end()) return true;
    else return false;
}

int ContactOptions::givePositionInVector(vector <Person> addressData, int contacktNumberForEditing)
{
    vector <string> idNumbers;
    for(int vectorPosition = 0; vectorPosition < addressData.size(); vectorPosition++)
    {
        idNumbers.push_back(addressData[vectorPosition].IdNumber);
    }

    for (int vectorPosition = 0; vectorPosition < idNumbers.size(); vectorPosition++)
    {
        if (idNumbers[vectorPosition] == intToStringConversion(contacktNumberForEditing))

            return vectorPosition;
    }
}

void ContactOptions::updateAddressData(vector <Person> &addressData)
{
  fstream contactDatabase;
        contactDatabase.open("kontakty.txt",ios::out);
        if (contactDatabase.good() == true)
        {
            for(int vectorPosition = 0; vectorPosition < addressData.size(); vectorPosition++)
            {
                contactDatabase<< addressData[vectorPosition].IdNumber + "|" + addressData[vectorPosition].userId + "|"
                             + addressData[vectorPosition].name + "|" + addressData[vectorPosition].lastName
                             + "|" + addressData[vectorPosition].phoneNumber + "|" + addressData[vectorPosition].emailAddress
                             + "|" + addressData[vectorPosition].address + "|";
                contactDatabase <<endl;
            }
            contactDatabase.close();
            cout<< "Kontakt zostal zmieniony!" <<endl;
            Sleep(1500);
        }
        else
        {
            cout<< "Nie odnaleziono takiego pliku" <<endl;
            Sleep(1500);
        }
}

void ContactOptions::editContact(vector <Person> &addressData, int loggedUserId)
{
    system("cls");
    cout <<">>>EDYCJA WYBRANEGO KONTAKTU<<<" <<endl;
    cout <<"-------------------------------" <<endl;
    cout <<endl;
    addressData.clear();
    importAllContacts(addressData);
    string newPhoneNumber, newEmailAddress, newAddress;
    int selectedOption;
    int contacktNumberForEditing;
    cout<< "Podaj numer kontaktu, ktory chcesz edytowac: ";
    cin>> contacktNumberForEditing;
    ContactOptions position;
    int positionInVector = position.givePositionInVector(addressData, contacktNumberForEditing);
    ContactOptions presence;
    if ((presence.checkContactExistion(addressData, contacktNumberForEditing) == 1) || (addressData[positionInVector].userId == intToStringConversion(loggedUserId)))
    {
        for(int vectorPosition = 0; vectorPosition < addressData.size(); vectorPosition++)
        {
            if (addressData[vectorPosition].IdNumber == intToStringConversion(contacktNumberForEditing))
            {
                cout<< addressData[vectorPosition].name << " " << addressData[vectorPosition].lastName <<endl;
                cout<< addressData[vectorPosition].phoneNumber <<endl;
                cout<< addressData[vectorPosition].emailAddress <<endl;
                cout<< addressData[vectorPosition].address <<endl;
            }

        }

        cout<< "Wybierz dane do zmiany: " <<endl;
        cout<< "1. Numer telefonu" <<endl;
        cout<< "2. Adres mailowy" <<endl;
        cout<< "3. Adres zamieszkania" <<endl;
        cout<< "4. Wyjscie" <<endl;
        cin>> selectedOption;
        switch(selectedOption)
        {
        case 1:
        {
            cout<< "Podaj nowy numer telefonu: ";
            cin.sync();
            getline(cin, newPhoneNumber);
            addressData[positionInVector].phoneNumber = newPhoneNumber;
        }
        break;

        case 2:
        {
            cout<< "Podaj nowy adres mailowy: ";
            cin>> newEmailAddress;
            addressData[positionInVector].emailAddress = newEmailAddress;
        }
        break;

        case 3:
        {
            cout<< "Podaj nowy adres zamieszkania: ";
            cin.sync();
            getline(cin, newAddress);
            addressData[positionInVector].address = newAddress;
        }
        break;

        case 4:
            exit(0);
            break;
        }

      ContactOptions update;
      update.updateAddressData(addressData);
    }
    else
    {
        cout<< "Kontakt o podanym numerze ID nie istnieje!" <<endl;
        Sleep(1500);
    }
}
void ContactOptions::removeContact(vector <Person> addressData, int loggedUserId)
{
    system("cls");
    cout<< ">>>USUWANIE WYBRANEGO KONTAKTU<<<" <<endl;
    cout<< "---------------------------------" <<endl;
    cout<< endl;
    addressData.clear();
    importAllContacts(addressData);
    int contactNumber;
    cout<< "Podaj numer kontaktu, ktory chcesz usunac: ";
    cin>> contactNumber;
    ContactOptions presence;
    if ((presence.checkContactExistion(addressData, contactNumber)) == 1 && (addressData[contactNumber-1].userId == intToStringConversion(loggedUserId)))
    {
        vector <string > temporary;
        ifstream in("kontakty.txt");
        string removedLine;
        while(getline(in, removedLine)) temporary.push_back(removedLine);
        in.close();
        ofstream out("kontakty.txt");
        for( int vectorPosition = 0; vectorPosition < temporary.size(); vectorPosition++)
        {
            if(vectorPosition + 1 != contactNumber) out << temporary[vectorPosition] <<endl;
        }
        out.close();
        cout<< "Kontakt zostal usuniety!" <<endl;
        Sleep(1500);
    }
    else
    {
        cout<< "Kontakt o podanym numerze ID nie istnieje!" <<endl;
        Sleep(1500);
    }
}
