#include <iostream>
#include "kontakty.h"
using namespace std;

int main()
{
    int loggedUserId = 0;
    while(1)
    {
        vector <User> users;
        UserOptions import;
        import.importUserData(users);

        int userFirstChoice;

        if (loggedUserId == 0)
        {
            system("cls");
            cout<<">>>KSIAZKA ADRESOWA<<<"<<endl;
            cout<<"------------------"<<endl;
            cout<<endl;
            cout<< "1. Rejestracja"<<endl;
            cout<< "2. Logowanie"<<endl;
            cout<< "3. Zakoncz program"<<endl;
            cout<< "-------------------"<<endl;
            cout<< endl;
            cout<< "Wybierz opcje: ";

            cin>>userFirstChoice;

            switch (userFirstChoice)
            {
            case 1:
            {
                UserOptions registration;
                registration.registerUser(users);
            }
            break;
            case 2:
            {
                UserOptions login;
                loggedUserId = login.logInUser(users);
            }
            break;
            case 3:
                exit(0);
                break;
            }
        }
        else
        {
            vector <Person> addressData;
            int userSecondChoice;
            ContactOptions import;
            import.importContactsForLoggedUsers(addressData, loggedUserId);
            system("cls");
            cout<<">>>KSIAZKA ADRESOWA<<<"<<endl;
            cout<<"------------------"<<endl;
            cout<<endl;
            cout<< "1. Dodaj kontakt"<<endl;
            cout<< "2. Wyszukaj po imieniu"<<endl;
            cout<< "3. Wyszukaj po nazwisku"<<endl;
            cout<< "4. Wyswietl wszystkie kontakty"<<endl;
            cout<< "5. Edytuj wybrany kontakt"<<endl;
            cout<< "6. Usun wybrany kontakt"<<endl;
            cout<< "7. Zmien haslo"<<endl;
            cout<< "8. Wyloguj sie"<<endl;
            cout<<endl;
            cout<<"Wybierz opcje: ";
            cin>>userSecondChoice;

            switch(userSecondChoice)
            {
            case 1:

            {
                ContactOptions adding;
                adding.addContact(addressData, loggedUserId);
            }

            break;

            case 2:
            {
                ContactOptions searchingByName;
                searchingByName.searchContactByName(addressData);
            }
            break;

            case 3:
            {
                ContactOptions searchingByLastName;
                searchingByLastName.searchContactByLastName(addressData);
            }
            break;

            case 4:
            {
                ContactOptions showing;
                showing.showAllContacts(addressData);
            }

            break;

            case 5:
                {
                 ContactOptions edition;
                 edition.editContact(addressData, loggedUserId);
                }
                break;

            case 6:
                {
                   ContactOptions removal;
                   removal.removeContact(addressData, loggedUserId);
                }
                break;

            case 7:
            {
                UserOptions password;
                password.changePassword(users, loggedUserId);
            }
            break;

            case 8:
            {
                loggedUserId = 0;
                cout<<"Wylogowales sie!"<<endl;
                Sleep(1000);
            }
            break;
            }
        }
    }
    return 0;
}
