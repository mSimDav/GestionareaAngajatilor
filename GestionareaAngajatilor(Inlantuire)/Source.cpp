#include<iostream>
#include<fstream>
#include <string>
#pragma warning(disable : 4996)
#define m 100
using namespace std;

ifstream f("angajati.txt", ios::in);
ofstream g("angajati.txt", ios::app);
ifstream f1("angajati1.txt");
ofstream g1("angajati1.txt");

struct nod
{
	char* CNP;
	int an_angajare, ore_lucrate, plata_pe_ora;
	char nume[20], prenume[20], functia[20], email[30], telefon[20];
	nod* next;
};

typedef nod* lista;
lista T[m];

int h(char* cnp)
{
	int sum = 0;
	if (cnp == NULL) { return -1; }
	for (; *cnp; cnp++) { sum += *cnp; }
	return(sum % m);
}

void inserare(char* cnp, int anang, int orelucr, int plataora, char num[20], char pren[20], char functie[20], char mail[30], char telef[20])
{
	int i = h(cnp);
	lista p;
	p = new(nothrow)nod;
	if (p == nullptr)
	{
		cout << "Alocare esuata!" << endl;
		exit(1);
	}
	p->CNP = new char[strlen(cnp) + 1];
	strcpy(p->CNP, cnp);
	p->an_angajare = anang;
	p->ore_lucrate = orelucr;
	p->plata_pe_ora = plataora;
	strcpy(p->nume, num);
	strcpy(p->prenume, pren);
	strcpy(p->functia, functie);
	strcpy(p->email, mail);
	strcpy(p->telefon, telef);
	p->next = T[i];
	T[i] = p;
}

lista cautare(char* cnp)
{
	int i = h(cnp);

	if (T[i] != nullptr)
	{
		lista p = T[i];
		while (p != nullptr)
		{
			if (strcmp(p->CNP, cnp) == 0)return p;
			p = p->next;
		}
		return p;
		p = p->next;
	}
	return nullptr;
}

void stergere(char* cnp)
{
	lista p;
	int i = h(cnp);
	string line;
	while (getline(f, line)) {

		if (line.find(cnp) == line.npos)
		{
			g1 << line << endl;
		}
	}
	lista q;
	if (T[i] != nullptr)
	{
		if (strcmp(T[i]->CNP, cnp) == 0)
		{
			q = T[i];
			T[i] = T[i]->next;
			delete q;
		}
		else
		{
			p = T[i];
			while (p->next != nullptr && p->next->CNP != cnp)
				p = p->next;
			if (p->next != nullptr)
			{
				q = p->next;
				p->next = q->next;
				delete q;
			}
		}
	}
}

int calcul_salariu(int ore_lucrate, int plata_pe_ora)
{
	int salariu;
	salariu = ore_lucrate * plata_pe_ora;
	return salariu;
}

int experienta(int an_angajare)
{
	time_t t = time(NULL);
	struct tm* T = localtime(&t);
	int an = T->tm_year + 1900;
	int exp;
	exp = an - an_angajare;
	return exp;
}

double spor(int ore_lucrate, int plata_pe_ora, int an_angajare)
{
	double salariu = calcul_salariu(ore_lucrate, plata_pe_ora);
	double exp = experienta(an_angajare);
	double s = 0;
	if (exp > 2 && exp < 5)
		s += salariu * 5 / 100;
	else if (exp >= 5 && exp <= 9)
		s += salariu * 15 / 100;
	else if (exp >= 10 && exp <= 15)
		s += salariu * 25 / 100;
	else if (exp > 15)
		s += salariu * 35 / 100;
	return s;
}

double salariu_primit(int ore_lucrate, int plata_pe_ora, int an_angajare)
{
	double spr = spor(ore_lucrate, plata_pe_ora, an_angajare);
	double sal = calcul_salariu(ore_lucrate, plata_pe_ora);
	double salariu = sal + spr;
	return salariu;
}

void afisare()
{
	cout << "CNP; NUME; FUNCTIE; AN ANGAJARE; ORE LUCRATE; PLATA PE ORA; EMAIL; TELEFON; SALARIU FARA SPOR; EXPERIENTA(ANI); SPOR; SALARIU PRIMIT:" << endl;
	for (int k = 0; k < m; k++)
	{
		if (T[k] != nullptr)
		{
			lista p = T[k];
			while (p != nullptr)
			{
				cout << p->CNP << "  " << p->nume << "  " << p->prenume << "  " << p->functia << "  " << p->an_angajare;
				cout << "  " << p->ore_lucrate << "  " << p->plata_pe_ora << "  " << p->email << "  " << p->telefon;
				cout << " " << calcul_salariu(p->ore_lucrate, p->plata_pe_ora);
				cout << " " << experienta(p->an_angajare);
				cout << " " << spor(p->ore_lucrate, p->plata_pe_ora, p->an_angajare);
				cout << " " << salariu_primit(p->ore_lucrate, p->plata_pe_ora, p->an_angajare) << ";" << endl;
				p = p->next;
			}
			cout << endl;
		}
	}
}

int main()
{
	char cnp[13];
	int n, anang, orelucr, plataora;
	char num[20], pren[20], functie[20], mail[20], telef[20];

	int optiune;
	do {

		cout << "Alegeti optiunea: " << endl;
		cout << "1. Inserare: " << endl;
		cout << "2. Stergere: " << endl;
		cout << "3. Cautare: " << endl;
		cout << "4. Afisarea tuturor angajatilor: " << endl;
		cout << "5. Afisarea listei actualizate cu angajati: " << endl;
		cout << "6. Terminare " << endl;
		cin >> optiune;

		switch (optiune) {
		case 1: {
			cout << "Introduceti numarul persoanelor pe care vreti sa le angajati: ";
			cin >> n;
			for (int i = 1; i <= n; i++)
			{
				cout << "CNP: ";
				cin >> cnp;
				cout << "Numele angajatului: ";
				cin >> num;
				cout << "Prenumele angajatului: ";
				cin >> pren;
				cout << "Functia angajatului: ";
				cin >> functie;
				cout << " Anul angajarii: ";
				cin >> anang;
				cout << "Ore lucrate: ";
				cin >> orelucr;
				cout << "Plata pe ora: ";
				cin >> plataora;
				cout << " Introduceti e-mail-ul angajatului: ";
				cin >> mail;
				cout << "Numarul de telefon al angajatului ";
				cin >> telef;
				inserare(cnp, anang, orelucr, plataora, num, pren, functie, mail, telef);

				g << "\n" << cnp << "  " << num << "  " << pren << "  " << functie << "  " << anang << "  " << orelucr << "  ";
				g << plataora << "  " << mail << "  " << telef;
				g << " " << calcul_salariu(orelucr, plataora);
				g << " " << experienta(anang);
				g << " " << spor(orelucr, plataora, anang);
				g << " " << salariu_primit(orelucr, plataora, anang) << ";" << endl;
			}
			afisare();
			cout << endl;
		}break;
		case 2: {
			cout << "Introduceti CNP-ul persoanei pe care doriti sa o stergeti: ";
			cin >> cnp;
			stergere(cnp);
			afisare();

			cout << endl;
		}break;
		case 3: {
			cout << "Introduceti CNP-ul angajatului pe care doriti sa il cautati: ";
			cin >> cnp;
			if (cautare(cnp) != nullptr)
				cout << "Aceasta persoana este angajata." << endl;
			else
				cout << "Aceasta persoana nu este angajata." << endl;
			cout << endl;
		}break;
		case 4: {
			cout << "Afisati lista tuturor angajatilor: ";
			string line;

			if (f.is_open())
			{

				while (getline(f, line))
				{
					cout << line << endl;
				}
				f.close();
			}
		}break;
		case 5: {
			cout << "Afisati lista actualizata a angajatilor: ";
			string line1;
			if (f1.is_open())
			{
				while (getline(f1, line1))
				{
					cout << line1 << endl;
				}
				f1.close();
			}
		}break;
		case 6: break;
		default: cout << " Introduceti un numar valid de optiune (1 -> 6) !" << endl;
		}
	} while (optiune != 6);

	system("pause");
	return 0;
}