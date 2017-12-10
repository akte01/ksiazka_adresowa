#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <windows.h>
#include <algorithm>

using namespace std;

class Uzytkownik
{
public:
    string idUzytkownika, nazwaUzytkownika, hasloUzytkownika;
    Uzytkownik(string idUzytkownika, string nazwaUzytkownika, string hasloUzytkownika);
};

class OpcjeUzytkownikow
{
public:
    vector <Uzytkownik> uzytkownicy;
    void importujDaneUzytkownikow(vector <Uzytkownik> &uzytkownicy);
    void zarejestrujUzytkownika(vector <Uzytkownik> uzytkownicy);
    int zalogujUzytkownika(vector <Uzytkownik> &uzytkownicy);
    void zmianaHasla(vector <Uzytkownik> &uzytkownicy, int idZalogowanegoUzytkownika);
};

class Osoba
{
public:
    string numerID, idUzytkownika, imie, nazwisko, telefon, mail, adres;
    Osoba(string numerID, string idUzytkownika, string imie, string nazwisko, string telefon, string mail, string adres);
};

class OpcjeKontaktow
{
    public:
    vector <Osoba> daneAdresowe;
    void importujKontaktyDlaZalogownegoUzytkownika(vector <Osoba> &daneAdresowe, int idZalogowanegoUzytkownika);
    void importujWszystkieKontakty(vector <Osoba> &daneAdresowe);
    void dodajKontakt(vector <Osoba> &daneAdresowe, int idZalogowanegoUzytkownika);
    void wyszukajKontaktPoImieniu(vector <Osoba> daneAdresowe);
    void wyszukajKontaktPoNazwisku(vector <Osoba> daneAdresowe);
    void wyswietlWszystkieKontakty(vector <Osoba> daneAdresowe);
    void edytujKontakt(vector <Osoba> &daneAdresowe, int idZalogowanegoUzytkownika);
    void usunKontakt(vector <Osoba> daneAdresowe, int idZalogowanegoUzytkownika);
    void pobierzDaneOsoby(vector <string> &pojedynczyKontakt, string daneOsobyOddzieloneKreskami);
    int podajNumerOstatniegoKontaktu (vector <Osoba> daneAdresowe);
    bool sprawdzCzyKontaktIstnieje(vector <Osoba> daneAdresowe, int numerKontaktuDoEdycji);
    int podajPozycjeWWektorze(vector <Osoba> daneAdresowe, int numerKontaktuDoEdycji);
    void eksportujKontaktDoPliku(vector <Osoba> &daneAdresoweDoEksportu);
    void aktualizujDaneAdresowe(vector <Osoba> &daneAdresowe);
};
