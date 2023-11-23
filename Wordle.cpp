#include <bits/stdc++.h>
#include <windows.h>
using namespace std;


void mudarCor(int cor)
{
 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), cor);
}

int main()
{
	setlocale(LC_ALL,"Portuguese");
	srand((unsigned) time(NULL));
	vector<string> palavras;
	ifstream input;
	input.open("validas.txt");
	if (!input.is_open())
		return 1;
	string linha;
	while (getline(input,linha))
	{
		palavras.push_back(linha);
	}
	int num = rand() % palavras.size() - 1;
	unordered_map<char,int> mapcerta;
	unordered_map<char,int> mapcores = {
		{'C', 02},
		{'A', 06},
		{'E', 04},
	};
	string certa = palavras[num];
	cout << "Palavra certa (segredo para o usuario): " << certa << "\n\n\n\n";
	for (const char& c : certa)
	{
		if (mapcerta.find(c) != mapcerta.end())
			mapcerta[c]++;
		else
			mapcerta[c] = 1;
	}
	int cont = 1; 
	cout << "Você tem 6 tentativas para adivinhar a palavra de 5 letras que eu estou pensando! \n";
	bool perdeu = true;
	while(cont!=6)
	{
		fflush(stdin);
		string res;
		string chute;
		do {
			cout << "Tentiva " << cont << ": ";
			cin >> chute;
			if (chute.size() != 5)
			{
				cout << "O input deve ser de 5 letras! \n";
				continue;
			}
			break;
		} while(true);
		string cores = "";
		for (int i=0; i<chute.size(); i++)
		{
			if (chute[i] == certa[i])
			{
				cores+="C";
			}
			else if (mapcerta.find(chute[i]) != mapcerta.end())
			{
				if(mapcerta.at(chute[i]) != 0) 
					cores += "A";
				mapcerta[chute[i]]--;
			}
			else
				cores += "E";
		}
		cout << "O resultado foi: ";
		for (int i=0; i<chute.size(); i++)
		{
			mudarCor(mapcores.at(cores[i]));
			cout << chute[i];
		}
		if (cores == "CCCCCC")
		{
			cout << "\nVocê acertou, parabéns!!";
			break;
		}
		mudarCor(7);
		cout << endl << endl;
		cont++;
	}
	if (perdeu)
		cout << "Você perdeu!!! A palavra certa era " << certa;
	return 0;
}
