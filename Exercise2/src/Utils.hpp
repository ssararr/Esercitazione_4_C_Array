#pragma once //evito inclusioni multiple
#include <iostream>
#include <fstream>
#include<string>

using namespace std;

//elenco di tutte le funzioni
bool Data(const string& path, size_t& n, double& S,double*& w,double*& r);

double DotProd(const size_t& n, const double* const& w, const double* const& r);

double S_tot(const double &r_tot, const double &S);

bool Results(const string& outputFilePath, const size_t& n, const double* const& w, const double* const& r,const double& S, const double& r_tot, const double& V);

string ArrayToString(const size_t& n, const double* const& v);