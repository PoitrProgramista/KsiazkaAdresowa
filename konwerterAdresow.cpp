#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

struct Kontakt
{
	int id;
	string imie, nazwisko, telefon, email, adres;
};

void zapiszDoPliku(vector<Kontakt>& ksiazkaAdresowa, string& nazwaPliku)
{
	fstream plik;

	nazwaPliku.erase(nazwaPliku.end()-4, nazwaPliku.end());

	plik.open(nazwaPliku + "_nowy_format.txt", ios::out);

	if (plik.good() == false)
	{
		system("cls");
		cout << "Nie ma mozliwosci zapisu do pliku" << endl;
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
	cin.sync();
}

bool wczytajDaneZPliku(vector<Kontakt>& ksiazkaAdresowa, string& nazwaPliku)
{
	string daneOsoby;
	fstream plik;
	Kontakt kontakt;
	int pozycja = 0;

	plik.open(nazwaPliku, ios::in);

	if (plik.good() == false)
	{
		system("cls");
		cout << "Nie znaleziono pliku" << endl;

		cin.sync();

		return false;
	}
	else if (plik.peek() == '/n')
	{
		system("cls");
		cout << "Plik jest pusty" << endl;

		cin.sync();

		return false;
	}

	for (size_t i = 1; !(plik.eof()); i++)
	{
		getline(plik, daneOsoby);

		switch (i % 6)
		{
			case 1:
				kontakt.id = atoi(daneOsoby.c_str());
				break;
			case 2:
				kontakt.imie = daneOsoby;
				break;
			case 3:
				kontakt.nazwisko = daneOsoby;
				break;
			case 4:
				kontakt.telefon = daneOsoby;
				break;
			case 5:
				kontakt.email = daneOsoby;
				break;
			case 0:
				kontakt.adres = daneOsoby;
				ksiazkaAdresowa.push_back(kontakt);
				pozycja++;
				break;
		}
	}
}

int main()
{
	char wybor;
	vector<Kontakt> ksiazkaAdresowa;
	string nazwaPliku;

	cout << "Podaj nazwe pliku: ";
	cin >> nazwaPliku;

	if (!(wczytajDaneZPliku(ksiazkaAdresowa, nazwaPliku)))
	{
		cout << "Nacisnij przycisk aby zakonczyc program" << endl;
		cin.get();
		cin.get();
		exit(0);
	}

	zapiszDoPliku(ksiazkaAdresowa, nazwaPliku);
}