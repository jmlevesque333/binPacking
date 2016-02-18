//Jean-Michel Levesque A00172309

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <iomanip>

using namespace std;

class bin
{
public:
	double size; // size du bin
	double sizeLeft; // size qui reste dans le bin
	bin()
	{
		size = 1.0; // size mit a 1
		sizeLeft = 1.0; //size restante de 1
	}
	void addItem(double size)
	{
		sizeLeft = sizeLeft - size; // diminue la size restante de le size de l'item
	}
	void removeNode(double size)
	{
		sizeLeft = sizeLeft + size; // augmenete la size restante de la size de l'item
	}

	void printBin() // imprime chaque bin
	{
		cout << "size: " << size << " ";
		cout << "sizeLeft: " << sizeLeft << endl;
	}
};

class binLine
{
public:
	vector <bin> line;

	binLine()
	{
	}
	
	void addIttemToTheList(double size)
	{
		double spaceRemaining = 1.0; // ce qui va garder la size du bin ou l'item fit le mieux
		int smallestBin = -1; // le bin ou l'item fit le mieux
		for (unsigned int i = 0; i < line.size(); i++)
		{
			if (0 < line[i].sizeLeft - size && line[i].sizeLeft - size < spaceRemaining)
			{
				smallestBin = i; 
				spaceRemaining =line[i].sizeLeft - size;

			}

		}
		if (smallestBin == -1) // fit pas nule par
		{
			bin a; // cree un nouveau bin
			addBin(a, size); // ajoute l'item a celui ci
		}
		else
			line[smallestBin].addItem(size); // ajoute l'item au bin existant
	}

	void addBin(bin a, double size) // ajoute bin a la liste et lui met un item dedans
	{
		a.sizeLeft = a.sizeLeft - size;
		line.push_back(a);

	}

	void printBinListe()
	{
		for (unsigned int i = 0; i < line.size(); i++)
		{
			cout << "bin: " << i << " "; // print la liste de bin
			line[i].printBin();
		}
	}

};

double makedoubleNumber(string mot) // transfomre un string en double
{
	double temp;
	if(mot[mot.size()-1] == ',') // si a une virgule , on l'enleve
		mot.pop_back();
	temp = stod(mot); // sring to double
	return temp;
}

int main()
{
	vector <double> shoppingList; // liste item
	string mot;
	fstream file;
	double number = 0.0;
	file.open("input.txt");
	while (file >> mot)
	{
		number = makedoubleNumber(mot); // transformer mot en double
		shoppingList.push_back(number); // mettre l'item dans la liste
	}
	sort(shoppingList.rbegin(), shoppingList.rend()); // mettre la liste en ordre decroissant

	binLine line;
	for (unsigned int i = 0; i < shoppingList.size(); i++)
		line.addIttemToTheList(shoppingList[i]); // met les items dans les bins

	line.printBinListe(); // Dans mon programme, quand je fais la transformation de string a double puis je divise par 100, mon double pert de la precision. Ceci peux causer des fautes de bin (ex, sizeLeft = 17, size = 17.000000004, il ne pourra pas entrer dans le bin qui lui est destiner) 
	return 0;
}
