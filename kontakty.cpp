#include <iostream>
#include "kontakty.h"

using namespace std;

Uzytkownik::Uzytkownik(string idUzytkownika, string nazwaUzytkownika, string hasloUzytkownika)
{
    this -> idUzytkownika = idUzytkownika;
    this -> nazwaUzytkownika = nazwaUzytkownika;
    this -> hasloUzytkownika = hasloUzytkownika;
}

Osoba::Osoba(string numerID, string idUzytkownika, string imie, string nazwisko, string telefon, string mail, string adres)
{
    this -> numerID = numerID;
    this -> idUzytkownika = idUzytkownika;
    this -> imie = imie;
    this -> nazwisko = nazwisko;
    this -> telefon = telefon;
    this -> mail = mail;
    this -> adres = adres;
}

string konwersjaIntNaString(int numerID)
{
    ostringstream ss;
    ss << numerID;
    string str = ss.str();
    return str;
}

void OpcjeKontaktow::pobierzDaneOsoby(vector <string> &pojedynczyKontakt, string daneOsobyOddzieloneKreskami)
{
    string pojedynczeDaneKontaktu = "";
    int numerPojedynczychDanychKontaktu = 1;

    for (int pozycjaZnaku = 0; pozycjaZnaku < daneOsobyOddzieloneKreskami.length(); pozycjaZnaku++)
    {
        if (daneOsobyOddzieloneKreskami[pozycjaZnaku] != '|')
        {
            pojedynczeDaneKontaktu += daneOsobyOddzieloneKreskami[pozycjaZnaku];
        }
        else
        {
            switch(numerPojedynczychDanychKontaktu)
            {
            case 1:
                pojedynczyKontakt.push_back(pojedynczeDaneKontaktu);
                break;
            case 2:
                pojedynczyKontakt.push_back(pojedynczeDaneKontaktu);
                break;
            case 3:
                pojedynczyKontakt.push_back(pojedynczeDaneKontaktu);
                break;
            case 4:
                pojedynczyKontakt.push_back(pojedynczeDaneKontaktu);
                break;
            case 5:
                pojedynczyKontakt.push_back(pojedynczeDaneKontaktu);
                break;
            case 6:
                pojedynczyKontakt.push_back(pojedynczeDaneKontaktu);
                break;
            case 7:
                pojedynczyKontakt.push_back(pojedynczeDaneKontaktu);
                break;
            }
            pojedynczeDaneKontaktu = "";
            numerPojedynczychDanychKontaktu++;
        }
    }
}
void OpcjeKontaktow::importujWszystkieKontakty(vector <Osoba> &daneAdresowe)
{
    vector <string> pojedynczyKontakt;
    string daneOsobyOddzieloneKreskami = "";
    fstream bazaKontaktow;
    bazaKontaktow.open("kontakty.txt", ios::in);

    if (bazaKontaktow.good() == true)
    {
        while (getline(bazaKontaktow, daneOsobyOddzieloneKreskami))
        {
            OpcjeKontaktow pobieranie;
            pobieranie.pobierzDaneOsoby(pojedynczyKontakt, daneOsobyOddzieloneKreskami);
            daneAdresowe.push_back(Osoba(pojedynczyKontakt[0], pojedynczyKontakt[1],
                                         pojedynczyKontakt[2], pojedynczyKontakt[3],
                                         pojedynczyKontakt[4], pojedynczyKontakt[5],
                                         pojedynczyKontakt[6]));
            pojedynczyKontakt.clear();
        }
        bazaKontaktow.close();
    }
}

int OpcjeKontaktow::podajNumerOstatniegoKontaktu (vector <Osoba> daneAdresowe)
{
    OpcjeKontaktow import;
    import.importujWszystkieKontakty(daneAdresowe);
    if (daneAdresowe.empty())
        return 0;
    else
    {
        int numerOstatniegoKontaktu = daneAdresowe.size() - 1;
        return atoi(daneAdresowe[numerOstatniegoKontaktu].numerID.c_str());
    }
}
void OpcjeUzytkownikow::importujDaneUzytkownikow(vector <Uzytkownik> &uzytkownicy)
{
    string liniaTekstuDoPobrania;
    int nrLiniiDoPobrania = 1;
    fstream bazaUzytkownikow;
    bazaUzytkownikow.open("uzytkownicy.txt", ios::in | ios::app);
    if (bazaUzytkownikow.good() == true)
    {
        while (getline(bazaUzytkownikow, liniaTekstuDoPobrania))
        {
            string daneUzytkownika;
            istringstream strumienLinii(liniaTekstuDoPobrania);
            vector <string> pojedynczyUzytkownik;

            while(getline(strumienLinii, daneUzytkownika, '|'))
            {
                istringstream strumienDanych(daneUzytkownika);
                string pojedynczeDaneUzytkownika;
                strumienDanych >> pojedynczeDaneUzytkownika;
                pojedynczyUzytkownik.push_back(pojedynczeDaneUzytkownika);
            }
           uzytkownicy.push_back(Uzytkownik(pojedynczyUzytkownik[0], pojedynczyUzytkownik[1],
                                             pojedynczyUzytkownik[2]));
            nrLiniiDoPobrania++;
        }
        bazaUzytkownikow.close();
    }
}

int OpcjeUzytkownikow::zalogujUzytkownika(vector <Uzytkownik> &uzytkownicy)
{
    system("cls");
    cout<< ">>>LOGOWANIE<<<" <<endl;
    cout<< "---------------" <<endl;
    cout<< endl;
    string nazwa, haslo;
    cout<< "Podaj login: ";
    cin>> nazwa;
    int i = 0;
    while(i<uzytkownicy.size())
    {
        if (uzytkownicy[i].nazwaUzytkownika == nazwa)
        {
            for(int j = 0; j < 3; j++)
            {
                cout<< "Podaj haslo. Pozostalo prob " << 3 - j << ": ";
                cin>> haslo;
                cout<< endl;
                if (uzytkownicy[i].hasloUzytkownika == haslo)
                {
                    cout<< "Zalogowales sie!" <<endl;
                    Sleep(1000);
                    return atoi(uzytkownicy[i].idUzytkownika.c_str());
                }
            }
            cout<< "Podaje 3 razy bledne haslo. Poczekaj 3 sekundy przed kolejna proba!" <<endl;
            Sleep(3000);
            return 0;
        }
        i++;
    }
    cout<< "Nie ma takiego uzytkownika!" <<endl;
    Sleep(1500);
    return 0;
}

void OpcjeUzytkownikow::zarejestrujUzytkownika(vector <Uzytkownik> uzytkownicy)
{
    system("cls");
    cout<< ">>>REJESTRACJA NOWEGO UZYTKOWNIKA<<<" <<endl;
    cout<< "------------------------------------" <<endl;
    cout<< endl;
    vector <Uzytkownik> uzytkownicyDoEksportu;
    string nazwa, haslo, numerID;
    cout<< "Podaj nazwe uzytkownika: ";
    cin>> nazwa;
    int i = 0;
    while(i < uzytkownicy.size())
    {
        if (uzytkownicy[i].nazwaUzytkownika == nazwa)
        {
            cout<< "Taki uzytkownik istnieje. Podaj inna nazwe uzytkownika: ";
            cin>> nazwa;
            i = 0;
        }
        else
        {
            i++;
        }
    }
    cout<< "Podaj haslo: ";
    cin>> haslo;
    numerID = konwersjaIntNaString(uzytkownicy.size() + 1);
    uzytkownicyDoEksportu.push_back(Uzytkownik(numerID, nazwa, haslo));
    fstream bazaUzytkownikow;
    bazaUzytkownikow.open("uzytkownicy.txt",ios::out|ios::app);
    if (bazaUzytkownikow.good() == true)
    {
        for(int i = 0; i < uzytkownicyDoEksportu.size(); i++)
        {
            bazaUzytkownikow<< uzytkownicyDoEksportu[i].idUzytkownika + "|"
                            + uzytkownicyDoEksportu[i].nazwaUzytkownika + "|"
                            + uzytkownicyDoEksportu[i].hasloUzytkownika + "|";
            bazaUzytkownikow <<endl;
        }

        bazaUzytkownikow.close();
        uzytkownicyDoEksportu.clear();
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


void OpcjeKontaktow::importujKontaktyDlaZalogownegoUzytkownika(vector <Osoba> &daneAdresowe, int idZalogowanegoUzytkownika)
{
    vector <string> pojedynczyKontakt;
    string daneOsobyOddzieloneKreskami = "";
    fstream bazaKontaktow;
    bazaKontaktow.open("kontakty.txt", ios::in);
    if (bazaKontaktow.good() == true)
    {
        while (getline(bazaKontaktow, daneOsobyOddzieloneKreskami))
        {
            pobierzDaneOsoby(pojedynczyKontakt, daneOsobyOddzieloneKreskami);
            if (konwersjaIntNaString(idZalogowanegoUzytkownika) == pojedynczyKontakt[1])
            {
                daneAdresowe.push_back(Osoba(pojedynczyKontakt[0], pojedynczyKontakt[1],
                                             pojedynczyKontakt[2], pojedynczyKontakt[3],
                                             pojedynczyKontakt[4], pojedynczyKontakt[5],
                                             pojedynczyKontakt[6]));
            }
            pojedynczyKontakt.clear();
        }
        bazaKontaktow.close();
    }
}

void OpcjeKontaktow::wyswietlWszystkieKontakty(vector <Osoba> daneAdresowe)
{
    system("cls");
    cout<< ">>>LISTA WSZYSTKICH KONTAKTOW<<<" <<endl;
    cout<< "--------------------------------" <<endl;
    cout<< endl;
    if (!daneAdresowe.empty())
    {
        for (int i = 0; i < daneAdresowe.size(); i++)
        {
            cout<< daneAdresowe[i].numerID <<endl;
            cout<< daneAdresowe[i].imie <<endl;
            cout<< daneAdresowe[i].nazwisko <<endl;
            cout<< daneAdresowe[i].telefon <<endl;
            cout<< daneAdresowe[i].mail <<endl;
            cout<< daneAdresowe[i].adres <<endl;
        }
        system("pause");
    }
    else
    {
        cout << "Ksiazka adresowa jest pusta." <<endl;
        Sleep(1500);
    }
}
void OpcjeKontaktow::eksportujKontaktDoPliku(vector <Osoba> &daneAdresoweDoEksportu)
{
fstream bazaKontaktow;
    bazaKontaktow.open("kontakty.txt",ios::out|ios::app);
    if (bazaKontaktow.good() == true)
    {
        for(int i = 0; i < daneAdresoweDoEksportu.size(); i++)
        {
            bazaKontaktow<< daneAdresoweDoEksportu[i].numerID + "|" + daneAdresoweDoEksportu[i].idUzytkownika
                         + "|" + daneAdresoweDoEksportu[i].imie + "|" + daneAdresoweDoEksportu[i].nazwisko
                         + "|" + daneAdresoweDoEksportu[i].telefon + "|" + daneAdresoweDoEksportu[i].mail
                         + "|" + daneAdresoweDoEksportu[i].adres + "|";
            bazaKontaktow <<endl;
        }

        bazaKontaktow.close();
        cout<< "Kontakt zostal dodany!"<<endl;
        Sleep(1500);
    }

    else
    {
        cout<<"Nie odnaleziono takiego pliku"<<endl;
        Sleep(1500);
    }
}
void OpcjeKontaktow::dodajKontakt(vector <Osoba> &daneAdresowe, int idZalogowanegoUzytkownika)
{
    system("cls");
    cout<< ">>>DODAJ NOWY KONTAKT<<<" <<endl;
    cout<< "------------------------" <<endl;
    cout<< endl;
    vector <Osoba> daneAdresoweDoEksportu;
    string imie, nazwisko, telefon, mail, adres;
    OpcjeKontaktow ostatniNumer;
    int numerKontaktu = ostatniNumer.podajNumerOstatniegoKontaktu(daneAdresowe) + 1;
    string numerID = konwersjaIntNaString(numerKontaktu);
    string numerIdZalogowanegoUzytkownika = konwersjaIntNaString(idZalogowanegoUzytkownika);

    cout<< "Podaj imie: ";
    cin>> imie;

    cout<< "Podaj nazwisko: ";
    cin>> nazwisko;

    cout<< "Podaj numer telefonu: ";
    cin.sync();
    getline(cin, telefon);

    cout<< "Podaj adres e-mail: ";
    cin>> mail;

    cout<< "Podaj adres zamieszkania: ";
    cin.sync();
    getline(cin, adres);

    daneAdresoweDoEksportu.push_back(Osoba(numerID, numerIdZalogowanegoUzytkownika, imie, nazwisko, telefon, mail, adres));
    OpcjeKontaktow eksportKontaktu;
    eksportKontaktu.eksportujKontaktDoPliku(daneAdresoweDoEksportu);
}

void OpcjeKontaktow::wyszukajKontaktPoImieniu(vector <Osoba> daneAdresowe)
{
    system("cls");
    cout<< ">>>WYSZUKAJ KONTAKT PO IMIENIU<<<" <<endl;
    cout<< "---------------------------------" <<endl;
    cout<< endl;
    string imieDoSprawdzenia;
    cout<< "Podaj imie: ";
    cin>> imieDoSprawdzenia;
    int licznikKontaktow = 0;
    while(licznikKontaktow < daneAdresowe.size())
    {
        if (daneAdresowe[licznikKontaktow].imie == imieDoSprawdzenia)
        {
            cout<< daneAdresowe[licznikKontaktow].numerID <<". "<< daneAdresowe[licznikKontaktow].imie <<" "<< daneAdresowe[licznikKontaktow].nazwisko <<endl;
            Sleep(1500);
            licznikKontaktow++;
        }

        else
            licznikKontaktow++;
    }

    string wybranaOpcja;
    cout<< "Wybierz kontakt lub wybierz 0, aby przejsc do menu glownego: ";
    cin>> wybranaOpcja;

    for(int i = 0; i < daneAdresowe.size(); i++)
    {
        if (daneAdresowe[i].numerID == wybranaOpcja)
        {
            cout<< daneAdresowe[i].imie <<" " <<daneAdresowe[i].nazwisko <<endl;
            cout<< daneAdresowe[i].telefon <<endl;
            cout<< daneAdresowe[i].mail <<endl;
            cout<< daneAdresowe[i].adres <<endl;
            system("pause");
        }

        else if (wybranaOpcja == "0")
            Sleep(500);
    }
}

void OpcjeKontaktow::wyszukajKontaktPoNazwisku(vector <Osoba> daneAdresowe)
{
    system("cls");
    cout <<">>>WYSZUKAJ KONTAKT PO NAZWISKU<<<" <<endl;
    cout <<"----------------------------------" <<endl;
    cout <<endl;
    string nazwiskoDoSprawdzenia;
    cout <<"Podaj nazwisko: ";
    cin>> nazwiskoDoSprawdzenia;
    int licznikKontaktow = 0;
    while(licznikKontaktow < daneAdresowe.size())
    {
        if (daneAdresowe[licznikKontaktow].nazwisko == nazwiskoDoSprawdzenia)
        {
            cout<< daneAdresowe[licznikKontaktow].numerID <<". "<< daneAdresowe[licznikKontaktow].imie <<" "<< daneAdresowe[licznikKontaktow].nazwisko <<endl;
            Sleep(1500);
            licznikKontaktow++;
        }

        else
            licznikKontaktow++;
    }

    string wybranaOpcja;
    cout<< "Wybierz kontakt lub wybierz 0, aby przejsc do menu glownego: ";
    cin>> wybranaOpcja;

    for(int i = 0; i < daneAdresowe.size(); i++)
    {
        if (daneAdresowe[i].numerID == wybranaOpcja)
        {
            cout<< daneAdresowe[i].imie <<" " <<daneAdresowe[i].nazwisko <<endl;
            cout<< daneAdresowe[i].telefon <<endl;
            cout<< daneAdresowe[i].mail <<endl;
            cout<< daneAdresowe[i].adres <<endl;
            system("pause");
        }

        else if (wybranaOpcja == "0")
            Sleep(500);
    }
}

void OpcjeUzytkownikow::zmianaHasla(vector <Uzytkownik> &uzytkownicy, int idZalogowanegoUzytkownika)
{
    system("cls");
    cout<< ">>>ZMIANA HASLA<<<" <<endl;
    cout<< "------------------" <<endl;
    cout<< endl;
    string noweHaslo;
    cout<< "Podaj nowe haslo: ";
    cout<< endl;
    cin>> noweHaslo;
    for(int i = 0; i < uzytkownicy.size(); i++)
    {
        if (uzytkownicy[i].idUzytkownika == konwersjaIntNaString(idZalogowanegoUzytkownika))
        {
            uzytkownicy[i].hasloUzytkownika = noweHaslo;
        }
    }
    fstream bazaUzytkownikow;
    bazaUzytkownikow.open("uzytkownicy.txt",ios::out);
    if (bazaUzytkownikow.good() == true)
    {
        for(int i = 0; i < uzytkownicy.size(); i++)
        {
            bazaUzytkownikow<< uzytkownicy[i].idUzytkownika + "|"
                            + uzytkownicy[i].nazwaUzytkownika + "|"
                            + uzytkownicy[i].hasloUzytkownika + "|";
            bazaUzytkownikow <<endl;
        }
        bazaUzytkownikow.close();
        cout<< "Haslo zostalo zmienione!" <<endl;
        Sleep(1500);
    }
    else
    {
        cout<< "Nie odnaleziono takiego pliku" <<endl;
        Sleep(1500);
    }
}

bool OpcjeKontaktow::sprawdzCzyKontaktIstnieje(vector <Osoba> daneAdresowe, int numerKontaktuDoEdycji)
{
    vector <string> numeryID;
    for(int i = 0; i < daneAdresowe.size(); i++)
    {
        numeryID.push_back(daneAdresowe[i].numerID);
    }

    vector <string> ::iterator itr;
    itr = find (numeryID.begin(), numeryID.end(), konwersjaIntNaString(numerKontaktuDoEdycji));
    if (itr != numeryID.end()) return true;
    else return false;
}

int OpcjeKontaktow::podajPozycjeWWektorze(vector <Osoba> daneAdresowe, int numerKontaktuDoEdycji)
{
    vector <string> numeryID;
    for(int i = 0; i < daneAdresowe.size(); i++)
    {
        numeryID.push_back(daneAdresowe[i].numerID);
    }

    for (int i = 0; i < numeryID.size(); i++)
    {
        if (numeryID[i] == konwersjaIntNaString(numerKontaktuDoEdycji))

            return i;
    }
}

void OpcjeKontaktow::aktualizujDaneAdresowe(vector <Osoba> &daneAdresowe)
{
  fstream bazaKontaktow;
        bazaKontaktow.open("kontakty.txt",ios::out);
        if (bazaKontaktow.good() == true)
        {
            for(int i = 0; i < daneAdresowe.size(); i++)
            {
                bazaKontaktow<< daneAdresowe[i].numerID + "|" + daneAdresowe[i].idUzytkownika + "|"
                             + daneAdresowe[i].imie + "|" + daneAdresowe[i].nazwisko
                             + "|" + daneAdresowe[i].telefon + "|" + daneAdresowe[i].mail
                             + "|" + daneAdresowe[i].adres + "|";
                bazaKontaktow <<endl;
            }
            bazaKontaktow.close();
            cout<< "Kontakt zostal zmieniony!" <<endl;
            Sleep(1500);
        }
        else
        {
            cout<< "Nie odnaleziono takiego pliku" <<endl;
            Sleep(1500);
        }
}

void OpcjeKontaktow::edytujKontakt(vector <Osoba> &daneAdresowe, int idZalogowanegoUzytkownika)
{
    system("cls");
    cout <<">>>EDYCJA WYBRANEGO KONTAKTU<<<" <<endl;
    cout <<"-------------------------------" <<endl;
    cout <<endl;
    daneAdresowe.clear();
    importujWszystkieKontakty(daneAdresowe);
    string nowyTelefon, nowyMail, nowyAdres;
    int opcja;
    int numerKontaktuDoEdycji;
    cout<< "Podaj numer kontaktu, ktory chcesz edytowac: ";
    cin>> numerKontaktuDoEdycji;
    OpcjeKontaktow pozycja;
    int pozycjaWWektorze = pozycja.podajPozycjeWWektorze(daneAdresowe, numerKontaktuDoEdycji);
    OpcjeKontaktow obecnosc;
    if ((obecnosc.sprawdzCzyKontaktIstnieje(daneAdresowe, numerKontaktuDoEdycji) == 1) || (daneAdresowe[pozycjaWWektorze].idUzytkownika == konwersjaIntNaString(idZalogowanegoUzytkownika)))
    {
        for(int i = 0; i < daneAdresowe.size(); i++)
        {
            if (daneAdresowe[i].numerID == konwersjaIntNaString(numerKontaktuDoEdycji))
            {
                cout<< daneAdresowe[i].imie << " " << daneAdresowe[i].nazwisko <<endl;
                cout<< daneAdresowe[i].telefon <<endl;
                cout<< daneAdresowe[i].mail <<endl;
                cout<< daneAdresowe[i].adres <<endl;
            }

        }

        cout<< "Wybierz dane do zmiany: " <<endl;
        cout<< "1. Numer telefonu" <<endl;
        cout<< "2. Adres mailowy" <<endl;
        cout<< "3. Adres zamieszkania" <<endl;
        cout<< "4. Wyjscie" <<endl;
        cin>> opcja;
        switch(opcja)
        {
        case 1:
        {
            cout<< "Podaj nowy numer telefonu: ";
            cin.sync();
            getline(cin, nowyTelefon);
            daneAdresowe[pozycjaWWektorze].telefon = nowyTelefon;
        }
        break;

        case 2:
        {
            cout<< "Podaj nowy adres mailowy: ";
            cin>> nowyMail;
            daneAdresowe[pozycjaWWektorze].mail = nowyMail;
        }
        break;

        case 3:
        {
            cout<< "Podaj nowy adres zamieszkania: ";
            cin.sync();
            getline(cin, nowyAdres);
            daneAdresowe[pozycjaWWektorze].adres = nowyAdres;
        }
        break;

        case 4:
            exit(0);
            break;
        }

      OpcjeKontaktow aktualizacja;
      aktualizacja.aktualizujDaneAdresowe(daneAdresowe);
    }
    else
    {
        cout<< "Kontakt o podanym numerze ID nie istnieje!" <<endl;
        Sleep(1500);
    }
}
void OpcjeKontaktow::usunKontakt(vector <Osoba> daneAdresowe, int idZalogowanegoUzytkownika)
{
    system("cls");
    cout<< ">>>USUWANIE WYBRANEGO KONTAKTU<<<" <<endl;
    cout<< "---------------------------------" <<endl;
    cout<< endl;
    daneAdresowe.clear();
    importujWszystkieKontakty(daneAdresowe);
    int numerKontaktu;
    cout<< "Podaj numer kontaktu, ktory chcesz usunac: ";
    cin>> numerKontaktu;
    OpcjeKontaktow obecnosc;
    if ((obecnosc.sprawdzCzyKontaktIstnieje(daneAdresowe, numerKontaktu)) == 1 && (daneAdresowe[numerKontaktu-1].idUzytkownika == konwersjaIntNaString(idZalogowanegoUzytkownika)))
    {
        vector <string > tymczas;
        ifstream in("kontakty.txt");
        string liniaDoUsuniecia;
        while( getline( in, liniaDoUsuniecia ) ) tymczas.push_back( liniaDoUsuniecia );
        in.close();
        ofstream out("kontakty.txt");
        for( int i = 0; i < tymczas.size(); i++ )
        {
            if( i + 1 != numerKontaktu) out << tymczas[i] <<endl;
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
