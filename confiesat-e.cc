/** CONFIESAT-E by Ivan Gil Delgado
	* 24/12/2020
*/

/* ARREGLAR
	*no cambia letras con tilde
*/

#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <time.h>
using namespace std;

void communicate(string& f) {  // Cambia carácter alfabético por otro random.
	int n = f.size();          // Respeta may./min. sin tilde
	int r;                     // Vocales siguen siendo vocales, igual con consonantes
	for(int i = 0; i < n; ++i) {
		if((f[i] >= 'a' and f[i] <= 'z')) {
			if(f[i] == 'a' or f[i] == 'e' or f[i] == 'i' or f[i] == 'o' or f[i] == 'u') {
				r = rand() % 5; // {0-4}
				if(r == 0) f[i] = 'a';
				else if(r == 1) f[i] = 'e';
				else if(r == 2) f[i] = 'i';
				else if(r == 3) f[i] = 'o';
				else f[i] = 'u';
			}
			else {
				r = rand() % 26 + 97;
				while(r == 97 or r== 101 or r == 105 or r == 111 or r == 117) r = rand() % 26 + 97;
				f[i] = r;
			}
		}
		else if(f[i] >= 'A' and f[i] <= 'Z') {
			if(f[i] == 'A' or f[i] == 'E' or f[i] == 'I' or f[i] == 'O' or f[i] == 'U') {
				r = rand() % 5; // {0-4}
				if(r == 0) f[i] = 'A';
				else if(r == 1) f[i] = 'E';
				else if(r == 2) f[i] = 'I';
				else if(r == 3) f[i] = 'O';
				else f[i] = 'U';
			}
			else {
				r = rand() % 26 + 65;
				while(r == 'A' or r== 'E' or r == 'I' or r == 'O' or r == 'U') r = rand() % 26 + 65;
				f[i] = r;
			}
		}
	}
}

void imprimir(int output, string& s) { // output={0=terminal, 1=impresora}
	int max;
	if(output == 0) max = 113;
	else if(output == 1) max = 18;
	
	int length = s.size();
	string word;
	int i = 0;
	int width = 0;
	int count;
	while(i <= length) {
		count = 0;
		word = "";
		while(s[i] != ' ') {
			word += s[i];
			++count;
			++i;
			if(i > length) break;
		}
		word += " ";
		++count;
		width += count;
		if(width > max) {
			cout << endl;
			width = count;
		}
		cout << word;
		++i;
	}
	cout << endl;
}

int main() {
	srand(time(NULL));

	ofstream file;
	ofstream file2;
	//Backup streambuffer de cout
	streambuf* stream_buffer_cout = cout.rdbuf();
	//Streambuffer del archivo
	streambuf* stream_buffer_file = file.rdbuf();
	streambuf* stream_buffer_file2 = file2.rdbuf();

	string name;
	string feel;
	while(true) {
		system("clear");

		cout << " /* CONFIESAT-E */ " << endl;
		cout << endl << "Para comenzar, dime tu nombre (sólo tu nombre):" << endl;
		cin >> name;
		int n = name.size();
		for(int i = 0; i < n; ++i) {	//Convertir nombre a mayúsculas
			if(name[i] >= 'a' and name[i] <= 'z') name[i] = name[i] - 32;
		}
		
		file.open("confesiones.txt", ios::out | ios::app);
		file2.open("aux.txt", ios::out | ios::trunc);

		string intro = "Hola "+name+". Soy LA MÁQUINA. Puedes explicarme todo aquello que te preocupa, manifestar tus secretos y anhelos más profundos o contarme aquello que considerabas inconfesable. Descárgalo todo sobre mi. Guardaré con recelo tus confesiones, lo prometo.";

		string intro2 = "Al final de tu confesión, escribe END para que sepa que has terminado y pulsa 'INTRO' para enviarla.";
		
		system("clear");
		cout << " /* CONFIESAT-E */ " << endl;
		imprimir(0, intro);
		imprimir(0, intro2);
		
		cout.rdbuf(stream_buffer_file); //Redirigir output al archivo

		cout << name << " dijo:" << endl;

		cin >> feel;
		int chance;
		string confesion = "";
		while(feel != "END") {
			chance = rand() % 5; //Rango 0 - 4
			if(chance < 3) communicate(feel);  //60% de no cambiar la palabra
			confesion += feel;
			confesion += " ";
			cin >> feel;
		}
		
		imprimir(1, confesion);
		cout << endl;
		
		cout.rdbuf(stream_buffer_file2); //Output a aux.txt
		cout << name << " dijo:" << endl;
		imprimir(1, confesion);

		cout.rdbuf(stream_buffer_cout);  //Redirigir al backup (output normal)
		cout << endl << "Gracias por contármelo" << endl;
		system("lpr -P POS58 aux.txt");
		system("sleep 2");
		file.close();
		file2.close();
	}
}
