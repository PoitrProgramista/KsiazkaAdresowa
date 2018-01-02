#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <windows.h>

using namespace std;

struct Kontakt
{
	int id;
	string imie, nazwisko, telefon, email, adres;
};


void wpiszKontakt(vector<Kontakt>& ksiazka, string dane, int pozycja)
{
	int iterator = 1;
	int koniec;
	while (1)
	{
		koniec = dane.find(" ");
		switch (iterator)
		{
			case 1:
				ksiazka[pozycja].id = atof((dane.substr(0, koniec)).c_str());
				break;
			case 2:
				ksiazka[pozycja].imie = dane.substr(0, koniec);
				break;
			case 3:
				ksiazka[pozycja].nazwisko = dane.substr(0, koniec);
				break;
			case 4:
				ksiazka[pozycja].telefon = dane.substr(0, koniec);
				break;
			case 5:
				ksiazka[pozycja].email = dane.substr(0, koniec);
				break;
			case 6:
				ksiazka[pozycja].adres = dane;
				dane.clear();
				return;
		}
		dane.erase(0, koniec + 1);
		iterator++;
	}
}
bool wczytajDane(vector<Kontakt>& ksiazka)
{
	fstream plik;
	string linia;

	plik.open("ksiazka_adresowa.txt", ios::in);

	if (plik.good() == false)
	{
		plik.close();
		cout << "Nie mozna otworzyc pliku" << endl;
		return false;
	}

	for (int i = 0; !(plik.eof()); i++)
	{
		Kontakt kontakt;
		cin.sync();
		getline(plik, linia);

		if (i >= ksiazka.capacity() - 1)
			ksiazka.resize(ksiazka.capacity() * 2);

		ksiazka.push_back(kontakt);
		wpiszKontakt(ksiazka, linia, i);
	}

	plik.close();
	return true;
}
void wyswietlKontakt(Kontakt kontakt)
{
	cout << endl << kontakt.id << " " << kontakt.imie << " " << kontakt.nazwisko << " " << kontakt.telefon << " " << kontakt.email << " " << kontakt.adres << endl;
}
void dodajKontakt(vector<Kontakt>& ksiazka)
{
	Kontakt kontakt;
	fstream plik;
	system("cls");
	kontakt.id = ksiazka.back().id + 1;

	cout << "Podaj imie:" << endl;
	cin >> kontakt.imie;
	cout << endl << "Podaj nazwisko:" << endl;
	cin >> kontakt.nazwisko;
	cout << endl << "Podaj telefon:" << endl;
	cin >> kontakt.telefon;
	cout << endl << "Podaj email:" << endl;
	cin >> kontakt.email;
	cout << endl << "Podaj adres:" << endl;
	cin.ignore();
	getline(cin, kontakt.adres);

	plik.open("ksiazka_adresowa.txt", ios::out | ios::app);
	plik << endl;
	plik << kontakt.id << " " << kontakt.imie << " " << kontakt.nazwisko << " " << kontakt.telefon << " " << kontakt.email << " " << kontakt.adres;
	plik.close();

	ksiazka.push_back(kontakt);
}
void wyszukajPoImieniu(const vector<Kontakt>& ksiazka)
{
	system("cls");
	string imie;
	bool czySaKontakty = false;
	cout << "Podaj imie: " << endl;
	cin >> imie;
	for (int i = 0; i < ksiazka.size(); i++)
	{
		if (ksiazka[i].imie == imie)
		{
			wyswietlKontakt(ksiazka[i]);
			czySaKontakty = true;
		}
	}
	if (!(czySaKontakty))
		cout << endl << "Brak kontaktow o podanym imieniu" << endl;

	cout << endl << "Wcisnij przycisk aby wrocic do menu glownego" << endl;
	cin.ignore();
	cin.get();
}
void wyszukajPoNazwisku(const vector<Kontakt>& ksiazka)
{
	system("cls");
	string nazwisko;
	bool czySaKontakty = false;
	cout << "Podaj nazwisko: " << endl;
	cin >> nazwisko;
	for (int i = 0; i < ksiazka.size(); i++)
	{
		if (ksiazka[i].nazwisko == nazwisko)
		{
			wyswietlKontakt(ksiazka[i]);
			czySaKontakty = true;
		}
	}
	if (!(czySaKontakty))
		cout << endl << "Brak kontaktow o podanym nazwisku" << endl;

	cout << endl << "Wcisnij przycisk aby wrocic do menu glownego" << endl;
	cin.ignore();
	cin.get();
}
void wyswietlWszystkieKontakty(const vector<Kontakt>& ksiazka)
{
	system("cls");
	bool czySaKontakty = false;
	for (int i = 0; i < ksiazka.size(); i++)
	{
		wyswietlKontakt(ksiazka[i]);
		czySaKontakty = true;
	}
	if (!(czySaKontakty))
		cout << endl << "Brak kontaktow do wyswietlenia" << endl;

	cout << endl << "Wcisnij przycisk aby wrocic do menu glownego" << endl;
	cin.ignore();
	cin.get();
}

int main()
{
	int wybor;
	vector<Kontakt> ksiazka;
	ksiazka.reserve(100);

	if (!(wczytajDane(ksiazka)))
	{
		cout << "Nacisnij przycisk aby zakonczyc program" << endl;
		cin.get();
		exit(0);
	}

	while (1)
	{
		system("cls");
		cout << "1. Dodaj kontakt" << endl;
		cout << "2. Wyszukaj po imieniu" << endl;
		cout << "3. Wyszukaj po nazwisku" << endl;
		cout << "4. Wyswietl wszystkie kontakty" << endl;
		cout << "5. Zakoncz" << endl;

		cin >> wybor;

		switch (wybor)
		{
			case 1:
				dodajKontakt(ksiazka);
				break;
			case 2:
				wyszukajPoImieniu(ksiazka);
				break;
			case 3:
				wyszukajPoNazwisku(ksiazka);
				break;
			case 4:
				wyswietlWszystkieKontakty(ksiazka);
				break;
			case 5:
				exit(0);
			default:
				cout << "Prosze podac poprawny numer" << endl;
				Sleep(2000);
		}
	}

	return 0;
}