#include <iostream>
#include "kontakty.h"
using namespace std;

int main()
{
    int idZalogowanegoUzytkownika = 0;
    while(1)
    {
        vector <Uzytkownik> uzytkownicy;
        OpcjeUzytkownikow import;
        import.importujDaneUzytkownikow(uzytkownicy);

        int wybor;

        if (idZalogowanegoUzytkownika == 0)
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

            cin>>wybor;

            switch (wybor)
            {
            case 1:
            {
                OpcjeUzytkownikow rejestracja;
                rejestracja.zarejestrujUzytkownika(uzytkownicy);
            }
            break;
            case 2:
            {
                OpcjeUzytkownikow logowanie;
                idZalogowanegoUzytkownika = logowanie.zalogujUzytkownika(uzytkownicy);
            }
            break;
            case 3:
                exit(0);
                break;
            }
        }
        else
        {
            vector <Osoba> daneAdresowe;
            int wybranaOpcja;
            OpcjeKontaktow import;
            import.importujKontaktyDlaZalogownegoUzytkownika(daneAdresowe, idZalogowanegoUzytkownika);
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
            cin>>wybranaOpcja;

            switch(wybranaOpcja)
            {
            case 1:

            {
                OpcjeKontaktow dodawanie;
                dodawanie.dodajKontakt(daneAdresowe, idZalogowanegoUzytkownika);
            }

            break;

            case 2:
            {
                OpcjeKontaktow wyszukiwaniePoImieniu;
                wyszukiwaniePoImieniu.wyszukajKontaktPoImieniu(daneAdresowe);
            }
            break;

            case 3:
            {
                OpcjeKontaktow wyszukiwaniePoNazwisku;
                wyszukiwaniePoNazwisku.wyszukajKontaktPoNazwisku(daneAdresowe);
            }
            break;

            case 4:
            {
                OpcjeKontaktow wyswietlanie;
                wyswietlanie.wyswietlWszystkieKontakty(daneAdresowe);
            }

            break;

            case 5:
                {
                 OpcjeKontaktow edycja;
                 edycja.edytujKontakt(daneAdresowe, idZalogowanegoUzytkownika);
                }
                break;

            case 6:
                {
                   OpcjeKontaktow usuwanie;
                   usuwanie.usunKontakt(daneAdresowe, idZalogowanegoUzytkownika);
                }
                break;

            case 7:
            {
                OpcjeUzytkownikow haslo;
                haslo.zmianaHasla(uzytkownicy, idZalogowanegoUzytkownika);
            }
            break;

            case 8:
            {
                idZalogowanegoUzytkownika = 0;
                cout<<"Wylogowales sie!"<<endl;
                Sleep(1000);
            }
            break;
            }
        }
    }
    return 0;
}
