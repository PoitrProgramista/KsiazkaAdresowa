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

void zapiszDoPliku(vector<Kontakt>& ksiazkaAdresowa)
{
	fstream plik;
	plik.open("ksiazka_adresowa.txt", ios::out);

	if (plik.good() == false)
	{
		system("cls");
		cout << "Nie ma mozliwosci zapisu do pliku" << endl;

		Sleep(1500);
		cin.sync();

		return;
	}

	for (int i = 0; i < ksiazkaAdresowa.size(); i++)
	{
		plik << ksiazkaAdresowa[i].id << "|" << ksiazkaAdresowa[i].imie << "|" << ksiazkaAdresowa[i].nazwisko << "|" << ksiazkaAdresowa[i].telefon << "|" << ksiazkaAdresowa[i].email << "|" << ksiazkaAdresowa[i].adres << "|";

		if (!(i == ksiazkaAdresowa.size() - 1))
			plik << endl;
	}

	plik.close();

	system("cls");
	cout << "Zapisano zmiany" << endl;

	Sleep(1500);
	cin.sync();
}
void wczytajKontaktZPliku(vector<Kontakt>& ksiazkaAdresowa, string& daneOsoby, int pozycja)
{
	int iterator = 1;
	size_t dlugoscParametru;

	while (true)
	{
		dlugoscParametru = daneOsoby.find("|");

		switch (iterator)
		{
			case 1:
				ksiazkaAdresowa[pozycja].id = atoi((daneOsoby.substr(0, dlugoscParametru)).c_str());
				break;
			case 2:
				ksiazkaAdresowa[pozycja].imie = daneOsoby.substr(0, dlugoscParametru);
				break;
			case 3:
				ksiazkaAdresowa[pozycja].nazwisko = daneOsoby.substr(0, dlugoscParametru);
				break;
			case 4:
				ksiazkaAdresowa[pozycja].telefon = daneOsoby.substr(0, dlugoscParametru);
				break;
			case 5:
				ksiazkaAdresowa[pozycja].email = daneOsoby.substr(0, dlugoscParametru);
				break;
			case 6:
				ksiazkaAdresowa[pozycja].adres = daneOsoby.substr(0, dlugoscParametru);
				daneOsoby.clear();

				return;
		}
		daneOsoby.erase(0, dlugoscParametru + 1);
		iterator++;
	}
}
bool wczytajDaneZPliku(vector<Kontakt>& ksiazkaAdresowa)
{
	fstream plik;
	string daneOsoby;
	Kontakt kontakt;

	plik.open("ksiazka_adresowa.txt", ios::in);

	if (plik.good() == false)
	{
		plik.close();

		system("cls");
		cout << "Nie mozna otworzyc pliku" << endl;

		Sleep(1500);
		cin.sync();

		return false;
	}

	if (!(plik.peek() == '/n'))
	{
		for (size_t i = 0; !(plik.eof()); i++)
		{
			getline(plik, daneOsoby);
			ksiazkaAdresowa.push_back(kontakt);
			wczytajKontaktZPliku(ksiazkaAdresowa, daneOsoby, i);
		}
	}

	plik.close();

	return true;
}
void wyswietlKontakt(const Kontakt& kontakt)
{
	cout << endl << "ID: " << kontakt.id << endl << kontakt.imie << " " << kontakt.nazwisko << endl << "Telefon: " << kontakt.telefon << endl << "Email: " << kontakt.email << endl << "Adres: " << kontakt.adres << endl;
}
void dodajKontakt(vector<Kontakt>& ksiazkaAdresowa)
{
	system("cls");

	Kontakt kontakt;
	if (ksiazkaAdresowa.size() == 0)
		kontakt.id = 1;
	else
		kontakt.id = ksiazkaAdresowa.back().id + 1;

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

	ksiazkaAdresowa.push_back(kontakt);

	zapiszDoPliku(ksiazkaAdresowa);

}
void edytujKontakt(vector<Kontakt>& ksiazkaAdresowa)
{
	system("cls");

	int id;
	bool kontaktIstnieje = false;
	char wybor;
	Kontakt* wybranyKontakt = NULL;
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
		cout << endl << "Brak kontaktu o podanym ID" << endl;
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

		cin >> wybor;
		cout << "Podaj dane: ";
		cin >> dane;

		switch (wybor)
		{
			case '1':
				wybranyKontakt->imie = dane;
				zapiszDoPliku(ksiazkaAdresowa);
				return;
			case '2':
				wybranyKontakt->nazwisko = dane;
				zapiszDoPliku(ksiazkaAdresowa);
				return;
			case '3':
				wybranyKontakt->telefon = dane;
				zapiszDoPliku(ksiazkaAdresowa);
				return;
			case '4':
				wybranyKontakt->email = dane;
				zapiszDoPliku(ksiazkaAdresowa);
				return;
			case '5':
				wybranyKontakt->adres = dane;
				zapiszDoPliku(ksiazkaAdresowa);
				return;
			case '6':
				return;
			default:
				system("cls");
				cout << "Prosze podac poprawny numer" << endl;

				Sleep(1500);
				cin.sync();
		}
	}
}
void usunKontakt(vector<Kontakt>& ksiazkaAdresowa)
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
		cout << endl << "Brak kontaktu o podanym ID" << endl;
		return;
	}

	ksiazkaAdresowa.erase(ksiazkaAdresowa.begin() + pozycja);

	zapiszDoPliku(ksiazkaAdresowa);
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

int main()
{
	char wybor;
	vector<Kontakt> ksiazkaAdresowa;

	if (!(wczytajDaneZPliku(ksiazkaAdresowa)))
	{
		cout << "Nacisnij przycisk aby zakonczyc program" << endl;
		cin.get();
		exit(0);
	}

	while (true)
	{
		system("cls");
		cin.sync();

		cout << "1. Dodaj kontakt" << endl;
		cout << "2. Edytuj kontakt" << endl;
		cout << "3. Usun kontakt" << endl;
		cout << "4. Wyswietl wszystkie kontakty" << endl;
		cout << "5. Wyszukaj po imieniu" << endl;
		cout << "6. Wyszukaj po nazwisku" << endl;
		cout << "7. Zakoncz" << endl;

		cin >> wybor;

		switch (wybor)
		{
			case '1':
				dodajKontakt(ksiazkaAdresowa);
				break;
			case '2':
				edytujKontakt(ksiazkaAdresowa);
				break;
			case '3':
				usunKontakt(ksiazkaAdresowa);
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
				exit(0);
			default:
				system("cls");
				cout << "Prosze podac poprawny numer" << endl;
				Sleep(1500);
		}
	}
	return 0;
}