#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <windows.h>
#include <stdio.h>

using namespace std;

struct Kontakt
{
	int id;
	string imie = "", nazwisko = "", telefon = "", email = "", adres = "";
};

struct Uzytkownik
{
	int idUzytkownika = 0;
	string nazwa = "", haslo = "";
};

string zamienDaneNaString(Kontakt& kontakt, Uzytkownik* wybranyUzytkownik)
{
	return  to_string(kontakt.id) + "|"
		+ to_string(wybranyUzytkownik->idUzytkownika) + "|"
		+ kontakt.imie + "|" + kontakt.nazwisko + "|"
		+ kontakt.telefon + "|" + kontakt.email + "|"
		+ kontakt.adres + "|";
}

void zapiszDoPliku(string& daneZmienione, Uzytkownik* wybranyUzytkownik)
{
	fstream plik;
	fstream temp;

	plik.open("Adresaci.txt", ios::in);
	temp.open("Adresaci_temp.txt", ios::out);

	if (plik.good() == false)
	{
		system("cls");
		cout << "Nie ma mozliwosci zapisu do pliku" << endl;

		Sleep(1500);
		cin.sync();

		return;
	}

	string idZmienione = daneZmienione.substr(0, daneZmienione.find("|"));

	if (idZmienione[0] == '!')
	{
		idZmienione = idZmienione.substr(1, idZmienione.back());
		daneZmienione = "";
	}

	bool poczatek = true;

	while (!(plik.eof()))
	{
		string dane;

		getline(plik, dane);

		string idObecne = dane.substr(0, dane.find("|"));

		if (poczatek == true)
			poczatek = false;
		else
		{
			if(!(daneZmienione == "" && (idObecne == idZmienione)))
				temp << endl;
		}

		if (idObecne == idZmienione)
		{
			temp << daneZmienione;
		}
		else
		{
			temp << dane;
		}
	}

	plik.close();
	temp.close();

	remove("Adresaci.txt");
	rename("Adresaci_temp.txt", "Adresaci.txt");

	system("cls");
	cout << "Zapisano zmiany" << endl;

	Sleep(1500);
	cin.sync();
}

void wczytajKontaktZPliku(vector<Kontakt>& ksiazkaAdresowa, string& daneOsoby, Uzytkownik* wybranyUzytkownik)
{
	int iterator = 1;
	int dlugoscParametru;
	Kontakt kontakt;

	int poczatek = daneOsoby.find("|") + 1;
	int koniec = daneOsoby.find("|", poczatek);
	int idUzytkownika = atoi((daneOsoby.substr(poczatek, koniec - poczatek)).c_str());

	if ((wybranyUzytkownik->idUzytkownika) == idUzytkownika)
	{
		while (true)
		{
			dlugoscParametru = daneOsoby.find("|");

			switch (iterator)
			{
				case 1:
					kontakt.id = atoi((daneOsoby.substr(0, dlugoscParametru)).c_str());
					break;
				case 2:
					daneOsoby.erase(0, daneOsoby.find("|") + 1);
					kontakt.imie = daneOsoby.substr(0, daneOsoby.find("|"));
					break;
				case 3:
					kontakt.nazwisko = daneOsoby.substr(0, dlugoscParametru);
					break;
				case 4:
					kontakt.telefon = daneOsoby.substr(0, dlugoscParametru);
					break;
				case 5:
					kontakt.email = daneOsoby.substr(0, dlugoscParametru);
					break;
				case 6:
					kontakt.adres = daneOsoby.substr(0, dlugoscParametru);

					daneOsoby.clear();
					ksiazkaAdresowa.push_back(kontakt);
					return;
			}
			daneOsoby.erase(0, daneOsoby.find("|") + 1);
			iterator++;
		}
	}
	else
	{
		return;
	}
}

void wczytajDaneZPliku(vector<Kontakt>& ksiazkaAdresowa, Uzytkownik* wybranyUzytkownik)
{
	fstream plik;
	string daneOsoby;

	plik.open("Adresaci.txt", ios::in);

	if (plik.good() == false)
	{
		plik.close();
		return;
	}

	if (!(plik.peek() == '/n'))
	{
		for (size_t i = 0; !(plik.eof()); i++)
		{
			getline(plik, daneOsoby);
			wczytajKontaktZPliku(ksiazkaAdresowa, daneOsoby, wybranyUzytkownik);
		}
	}

	plik.close();
}

void wczytajDaneUzytkownika(vector<Uzytkownik>& uzytkownicy, string& daneOsoby, int pozycja)
{
	int iterator = 1;
	size_t dlugoscParametru;

	while (true)
	{
		dlugoscParametru = daneOsoby.find("|");

		switch (iterator)
		{
			case 1:
				uzytkownicy[pozycja].idUzytkownika = atoi((daneOsoby.substr(0, dlugoscParametru)).c_str());
				break;
			case 2:
				uzytkownicy[pozycja].nazwa = daneOsoby.substr(0, dlugoscParametru);
				break;
			case 3:
				uzytkownicy[pozycja].haslo = daneOsoby.substr(0, dlugoscParametru);
				daneOsoby.clear();

				return;
		}
		daneOsoby.erase(0, dlugoscParametru + 1);
		iterator++;
	}
}

void wczytajUzytkownikow(vector<Uzytkownik>& uzytkownicy)
{
	fstream plik;
	string daneOsoby;
	Uzytkownik uzytkownik;

	plik.open("Uzytkownicy.txt", ios::in);

	if (plik.good() == false)
	{
		plik.open("Uzytkownicy.txt", ios::out);
		plik.close();
		return;
	}

	if (!(plik.peek() == '/n'))
	{
		for (size_t pozycja = 0; !(plik.eof()); pozycja++)
		{
			getline(plik, daneOsoby);
			uzytkownicy.push_back(uzytkownik);
			wczytajDaneUzytkownika(uzytkownicy, daneOsoby, pozycja);
		}
	}

	plik.close();
}

void wyswietlKontakt(const Kontakt& kontakt)
{
	cout << endl << "ID: " << kontakt.id << endl << kontakt.imie << " " << kontakt.nazwisko << endl << "Telefon: " << kontakt.telefon << endl << "Email: " << kontakt.email << endl << "Adres: " << kontakt.adres << endl;
}

void dodajKontakt(vector<Kontakt>& ksiazkaAdresowa, Uzytkownik* wybranyUzytkownik)
{
	system("cls");

	Kontakt kontakt;
	fstream plik;

	cin.sync();
	cout << "Podaj imie:" << endl;
	cin >> kontakt.imie;
	cout << endl << "Podaj nazwisko:" << endl;
	cin >> kontakt.nazwisko;
	cout << endl << "Podaj telefon:" << endl;
	cin.ignore();
	getline(cin, kontakt.telefon);
	cout << endl << "Podaj email:" << endl;
	cin >> kontakt.email;
	cout << endl << "Podaj adres:" << endl;
	cin.ignore();
	getline(cin, kontakt.adres);

	plik.open("Adresaci.txt", ios::in | ios::out | ios::app);

	plik.seekg(0, ios::end);
	int length = plik.tellg();
	string bufor = "";

	if (length == 0)
	{
		kontakt.id = 1;
		plik.seekg(0, ios::end);
	}
	else
	{
		while (bufor != "\n" && (int)plik.tellg() != ios::beg)
		{
			plik.seekg(-2, ios::cur);
			bufor = plik.get();
		}

		kontakt.id = (int)plik.get() - 47;
		plik.seekg(0, ios::end);
		plik << endl;
	}

	plik << kontakt.id << "|"
		<< wybranyUzytkownik->idUzytkownika << "|"
		<< kontakt.imie << "|" << kontakt.nazwisko << "|"
		<< kontakt.telefon << "|" + kontakt.email << "|"
		<< kontakt.adres << "|";

	plik.close();

	ksiazkaAdresowa.push_back(kontakt);

	system("cls");
	cout << "Zapisano zmiany" << endl;

	Sleep(1500);
	cin.sync();
}

void edytujKontakt(vector<Kontakt>& ksiazkaAdresowa, Uzytkownik* wybranyUzytkownik)
{
	system("cls");

	int id;
	bool kontaktIstnieje = false;
	Kontakt* wybranyKontakt = NULL;
	string daneZmienione;
	string dane;

	cin.sync();
	cout << "Podaj ID kontaktu do edycji: ";
	cin >> id;

	for (size_t i = 0; i < ksiazkaAdresowa.size(); i++)
	{
		if (ksiazkaAdresowa[i].id == id)
		{
			kontaktIstnieje = true;
			wybranyKontakt = &ksiazkaAdresowa[i];
			break;
		}
	}
	if (!(kontaktIstnieje))
	{
		system("cls");
		cout << endl << "Brak kontaktu o podanym ID" << endl;
		Sleep(1500);
		return;
	}

	while (true)
	{
		cout << "Wybierz dane do edycji: " << endl;
		cout << "1. Imie" << endl;
		cout << "2. Nazwisko" << endl;
		cout << "3. Telefon" << endl;
		cout << "4. Email" << endl;
		cout << "5. Adres" << endl;
		cout << "6. Powrot" << endl;

		char wybor;
		cin >> wybor;

		if (wybor == '6')
			return;

		cout << "Podaj dane: ";

		switch (wybor)
		{
			case '1':
				cin.ignore();
				getline(cin, dane);
				wybranyKontakt->imie = dane;
				daneZmienione = zamienDaneNaString(*wybranyKontakt, wybranyUzytkownik);
				zapiszDoPliku(daneZmienione, wybranyUzytkownik);
				return;
			case '2':
				cin.ignore();
				getline(cin, dane);
				wybranyKontakt->nazwisko = dane;
				daneZmienione = zamienDaneNaString(*wybranyKontakt, wybranyUzytkownik);
				zapiszDoPliku(daneZmienione, wybranyUzytkownik);
				return;
			case '3':
				cin.ignore();
				getline(cin, dane);
				wybranyKontakt->telefon = dane;
				daneZmienione = zamienDaneNaString(*wybranyKontakt, wybranyUzytkownik);
				zapiszDoPliku(daneZmienione, wybranyUzytkownik);
				return;
			case '4':
				cin.ignore();
				getline(cin, dane);
				wybranyKontakt->email = dane;
				daneZmienione = zamienDaneNaString(*wybranyKontakt, wybranyUzytkownik);
				zapiszDoPliku(daneZmienione, wybranyUzytkownik);
				return;
			case '5':
				cin.ignore();
				getline(cin, dane);
				wybranyKontakt->adres = dane;
				daneZmienione = zamienDaneNaString(*wybranyKontakt, wybranyUzytkownik);
				zapiszDoPliku(daneZmienione, wybranyUzytkownik);
				return;
			default:
				system("cls");
				cout << "Prosze podac poprawny numer" << endl;

				Sleep(1500);
				cin.sync();
		}
	}
}

void usunKontakt(vector<Kontakt>& ksiazkaAdresowa, Uzytkownik* wybranyUzytkownik)
{
	system("cls");

	int id;
	bool kontaktIstnieje = false;
	unsigned int pozycja;

	cin.sync();
	cout << "Podaj ID kontaktu do usuniecia: ";
	cin >> id;

	for (pozycja = 0; pozycja < ksiazkaAdresowa.size(); pozycja++)
	{
		if (ksiazkaAdresowa[pozycja].id == id)
		{
			kontaktIstnieje = true;
			break;
		}
	}

	if (!(kontaktIstnieje))
	{
		system("cls");
		cout << endl << "Brak kontaktu o podanym ID" << endl;
		Sleep(1500);
		return;
	}

	string daneZmienione = "!" + zamienDaneNaString(ksiazkaAdresowa[pozycja], wybranyUzytkownik);
	zapiszDoPliku(daneZmienione, wybranyUzytkownik);

	ksiazkaAdresowa.erase(ksiazkaAdresowa.begin() + pozycja);
}

void wyszukajPoImieniu(const vector<Kontakt>& ksiazkaAdresowa)
{
	system("cls");

	string imie;
	bool czySaKontakty = false;

	cout << "Podaj imie: " << endl;
	cin >> imie;
	for (size_t i = 0; i < ksiazkaAdresowa.size(); i++)
	{
		if (ksiazkaAdresowa[i].imie == imie)
		{
			wyswietlKontakt(ksiazkaAdresowa[i]);
			czySaKontakty = true;
		}
	}
	if (!(czySaKontakty))
		cout << endl << "Brak kontaktow o podanym imieniu" << endl;

	cout << endl << "Wcisnij przycisk aby wrocic do menu glownego" << endl;

	cin.ignore();
	cin.get();
}

void wyszukajPoNazwisku(const vector<Kontakt>& ksiazkaAdresowa)
{
	system("cls");

	string nazwisko;
	bool czySaKontakty = false;

	cout << "Podaj nazwisko: " << endl;
	cin >> nazwisko;
	for (size_t i = 0; i < ksiazkaAdresowa.size(); i++)
	{
		if (ksiazkaAdresowa[i].nazwisko == nazwisko)
		{
			wyswietlKontakt(ksiazkaAdresowa[i]);
			czySaKontakty = true;
		}
	}
	if (!(czySaKontakty))
		cout << endl << "Brak kontaktow o podanym nazwisku" << endl;

	cout << endl << "Wcisnij przycisk aby wrocic do menu glownego" << endl;

	cin.ignore();
	cin.get();
}

void zmianaHasla(vector<Uzytkownik>& uzytkownicy, Uzytkownik* wybranyUzytkownik)
{
	string noweHaslo;

	system("cls");
	cin.sync();

	cout << "Podaj nowe haslo: ";
	cin >> noweHaslo;
	wybranyUzytkownik->haslo = noweHaslo;

	fstream plik;
	plik.open("Uzytkownicy.txt", ios::out);

	if (plik.good() == false)
	{
		system("cls");
		cout << "Nie ma mozliwosci zapisu do pliku" << endl;

		Sleep(1500);
		cin.sync();

		return;
	}

	for (size_t i = 0; i < uzytkownicy.size(); i++)
	{
		plik << uzytkownicy[i].idUzytkownika << "|" << uzytkownicy[i].nazwa << "|" << uzytkownicy[i].haslo;

		if (!(i == uzytkownicy.size() - 1))
			plik << endl;
	}

	plik.close();

	system("cls");
	cout << "Zmieniono" << endl;

	Sleep(1500);
	cin.sync();
}

void wyswietlWszystkieKontakty(const vector<Kontakt>& ksiazkaAdresowa)
{
	system("cls");
	bool czySaKontakty = false;
	for (size_t i = 0; i < ksiazkaAdresowa.size(); i++)
	{
		wyswietlKontakt(ksiazkaAdresowa[i]);
		czySaKontakty = true;
	}
	if (!(czySaKontakty))
		cout << endl << "Brak kontaktow do wyswietlenia" << endl;

	cout << endl << "Wcisnij przycisk aby wrocic do menu glownego" << endl;

	cin.ignore();
	cin.get();
}

void otworzKsiazkeDlaUzytkownika(vector<Uzytkownik>& uzytkownicy, Uzytkownik* wybranyUzytkownik)
{
	char wybor;
	vector<Kontakt> ksiazkaAdresowa;

	wczytajDaneZPliku(ksiazkaAdresowa, wybranyUzytkownik);

	while (true)
	{
		system("cls");
		cin.sync();

		cout << "ZALOGOWANY UZYTKOWNIK: " << wybranyUzytkownik->nazwa << endl << endl;

		cout << "1. Dodaj adresata" << endl;
		cout << "2. Edytuj adresata" << endl;
		cout << "3. Usun adresata" << endl;
		cout << "4. Wyswietl wszystkich adresatow" << endl;
		cout << "5. Wyszukaj po imieniu" << endl;
		cout << "6. Wyszukaj po nazwisku" << endl;
		cout << "7. Zmien haslo" << endl;
		cout << "8. Wyloguj" << endl;

		cin >> wybor;

		switch (wybor)
		{
			case '1':
				dodajKontakt(ksiazkaAdresowa, wybranyUzytkownik);
				break;
			case '2':
				edytujKontakt(ksiazkaAdresowa, wybranyUzytkownik);
				break;
			case '3':
				usunKontakt(ksiazkaAdresowa, wybranyUzytkownik);
				break;
			case '4':
				wyswietlWszystkieKontakty(ksiazkaAdresowa);
				break;
			case '5':
				wyszukajPoImieniu(ksiazkaAdresowa);
				break;
			case '6':
				wyszukajPoNazwisku(ksiazkaAdresowa);
				break;
			case '7':
				zmianaHasla(uzytkownicy, wybranyUzytkownik);
				break;
			case '8':
				return;
			default:
				system("cls");
				cout << "Prosze podac poprawny numer" << endl;
				Sleep(1500);
		}
	}
}

void rejestracja(vector<Uzytkownik>& uzytkownicy)
{
	Uzytkownik uzytkownik;
	if (uzytkownicy.size() == 0)
		uzytkownik.idUzytkownika = 1;
	else
		uzytkownik.idUzytkownika = uzytkownicy.back().idUzytkownika + 1;

	system("cls");
	cin.sync();

	cout << "Podaj nazwe uzytkownika: ";
	cin >> uzytkownik.nazwa;
	cout << "Podaj haslo uzytkownika: ";
	cin >> uzytkownik.haslo;

	fstream plik;
	plik.open("Uzytkownicy.txt", ios::out | ios::app);

	if (plik.good() == false)
	{
		system("cls");
		cout << "Nie ma mozliwosci zapisu do pliku" << endl;

		Sleep(1500);
		cin.sync();

		return;
	}

	uzytkownicy.push_back(uzytkownik);

	plik.seekg(0, ios::end);
	int length = plik.tellg();

	if (!(length == 0))
		plik << endl;

	plik << uzytkownik.idUzytkownika << "|" << uzytkownik.nazwa << "|" << uzytkownik.haslo;

	plik.close();

	system("cls");
	cout << "Zarejestrowano" << endl;

	Sleep(1500);
	cin.sync();
}

Uzytkownik* logowanie(vector<Uzytkownik>& uzytkownicy)
{
	string nazwaPodana;
	string hasloPodane;
	bool uzytkownikIstnieje = false;
	Uzytkownik* wybranyUzytkownik = nullptr;

	while (true)
	{
		system("cls");
		cin.sync();

		cout << "Podaj nazwe uzytkownika: ";
		cin >> nazwaPodana;

		for (size_t i = 0; i < uzytkownicy.size(); i++)
		{
			if (uzytkownicy[i].nazwa == nazwaPodana)
			{
				uzytkownikIstnieje = true;
				wybranyUzytkownik = &uzytkownicy[i];
				break;
			}
		}
		if (!(uzytkownikIstnieje))
		{
			system("cls");
			cout << endl << "Nie ma takiego uzytkownika" << endl;
			Sleep(1500);
		}
		else
		{
			cout << "Podaj haslo: ";
			cin >> hasloPodane;

			if (hasloPodane == wybranyUzytkownik->haslo)
			{
				system("cls");
				cout << endl << "Zalogowano" << endl;
				Sleep(1500);

				return wybranyUzytkownik;
			}
			else
			{
				system("cls");
				cout << endl << "Bledne haslo" << endl;
				Sleep(1500);
				return nullptr;
			}
		}
	}
}


int main()
{
	char wybor;
	Uzytkownik* wybranyUzytkownik;
	vector<Uzytkownik> uzytkownicy;

	wczytajUzytkownikow(uzytkownicy);

	while (true)
	{
		system("cls");
		cin.sync();

		cout << "1. Logowanie" << endl;
		cout << "2. Rejestracja" << endl;
		cout << "3. Zamknij program" << endl;

		cin >> wybor;

		switch (wybor)
		{
			case '1':
				if ((wybranyUzytkownik = logowanie(uzytkownicy)) == nullptr)
					break;
				otworzKsiazkeDlaUzytkownika(uzytkownicy, wybranyUzytkownik);
				break;
			case '2':
				rejestracja(uzytkownicy);
				break;
			case '3':
				exit(0);
			default:
				system("cls");
				cout << "Prosze podac poprawny numer" << endl;
				Sleep(1500);
		}
	}
	return 0;
}