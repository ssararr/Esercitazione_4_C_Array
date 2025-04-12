#include <iostream> //input/output
#include <fstream> //lavorare con i file
#include <sstream> 
#include <iomanip>
#include "Utils.hpp" 

using namespace std;

int main()
{
	string path = "data.txt";		

	size_t n; //n assets nel portfolio 
	double S; //capitale iniziale
	
	//puntatori a memoria dinamica per i vettori dei pesi e dei rendimenti degli asset
	double* w = nullptr;
	double* r  = nullptr;
	
	//variabili che conterranno i risultati
	double r_tot; //valore del rendimento totale
	double S_finale; //valore finale del portafoglio 
	
	//richiamo la funzione che importa i dati da file e riempio le variabili
	Data(path, n, S, w, r);
	
	/* Calcolo il rendimento portafoglio come prodotto scalare tra il vettore dei pesi e quello dei rendimenti */
	r_tot = DotProd(n, w, r);
	
	/*Applico la formula per il valore finale del portafoglio: V = S * ( 1 + r) */
	S_finale = S_tot(r_tot, S);
	
	/* Esporto i risultati su file e li stampo a schermo: questa funzione fa entrambe le cose */
	Results("results.txt", n, w, r, S, r_tot, S_finale);
	
	/* libero la memoria dinamica allocata per i vettori , per evitare memory leak */
	
	delete [] w;
	delete [] r;
    return 0;
}

