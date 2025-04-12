#include <iostream> //input/output
#include <fstream> //lavorare con i file
#include <sstream>
#include<iomanip>
#include<string>
#include "Utils.hpp"


using namespace std;

//funzione per gestire l'apertura e la creazione dell'output, per poi creare l'asset
bool Data(const string& path, size_t& n, double& S, double*& w, double*& r)
{
	
	ifstream InputFile(path); //apro in lettura
	if(InputFile.fail())
    {
        cerr << "File not found" << endl;
        return false;
    }

	
	string tmp; 
	getline(InputFile, tmp,';'); //ignoro la parte testuale prima di ';'
	//memorizzo il valore del capitale iniziale S
	InputFile >> S; 
	InputFile.ignore(); //ignoro il carattere di newline
	
	getline(InputFile, tmp,';'); 
	//memorizzo il numero di assets
	InputFile >> n;
	InputFile.ignore();
	
	getline(InputFile, tmp);	//ignoro la riga successiva
	
	w = new double[n];
	r = new double[n];
	
	double posiz;
	
	for(unsigned int i = 0; i < n; i++)
	{
		getline(InputFile, tmp); //trovo la posizione di ; nella riga
		posiz = tmp.find(';');
		
		//estrazione della sottostinga prima di ;(ovvero componenti di w)
		w[i] = stod(tmp.substr(0, posiz));
		
		//analogo con r
		r[i] = stod(tmp.substr(posiz+1));
	} 
	InputFile.close();
    return true;
}

//funzione per creare il rate of return totale (somma delle r pesate con quanto vengono prese dal capitale iniziale tramite la percentuale w)
//poiché ho salvato w ed r in vettori, la loro somma pesata è data dal prodotto scalare
double DotProd(const size_t& n, const double* const& w, const double* const& r)		
{
	double r_tot = 0;
	for(unsigned int i = 0; i < n; i++)
    {
		r_tot += w[i] * r[i];
    }
   return r_tot;
}

//valore finale del portafoglio, applicando la formula: V =(1+rendimento)*S
double S_tot(const double &r_tot, const double &S)
{
	return (1+r_tot)*S;
}

//file di output
bool Results(const string& outputFilePath, const size_t& n, const double* const& w, const double* const& r, const double& S, const double& r_tot, const double& V)
{
    ofstream file;
    file.open(outputFilePath);

    if (file.fail())
    {
        cerr<< "File open failed"<< endl;
        return false;
    }
	
	//scrittura su file
    file << "S = " << fixed << setprecision(2) << S << ", n = " << n << endl;
	
	//ripristino del formato predefinito 
	file.unsetf(ios::fixed); //disattivo la notazione decimale forzata
	file << setprecision(4); //precisione totale
	
	//converto w ed r oin stringhe tramite la funzione ArrayToString
    file << "w = " << ArrayToString(n,w) << endl;		
	file << "r = " << ArrayToString(n,r) <<endl;
    file << "Rate of return: " << r_tot << endl;
	file << "V: " << fixed << setprecision(2) << V << endl;  	
	
	/* Stampa sul terminale*/
	cout << "S = " << fixed << setprecision(2) << S << ", n = " << n << endl;
	
	//Ripristino anche sul cout
	cout.unsetf(ios::fixed);		
	cout << setprecision(4);		
	
    cout << "w = " << ArrayToString(n,w ) << endl;
	cout << "r = " << ArrayToString(n,r) << endl;
    cout << "Rate of return of the portfolio: " << r_tot << endl;
	cout << "V: " << fixed << setprecision(2) << V << endl; //il valore finale viene stampato in notazione fissa con due cifre decimali
    file.close();
    return true;
}

//converto un'array di double in una steinga formattata
string ArrayToString(const size_t& n, const double* const& v)
{
    string str;
    ostringstream toString;
    toString << "[ ";
    for (unsigned int i = 0; i < n; i++)
        toString<< v[i]<< " ";
    toString << "]";

    return toString.str();
}
