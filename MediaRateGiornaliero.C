//questo programma prende in input il file Rate.txt o RateRIVELATORE.txt
//e calcola una media per ogni giorno di rate e latitudine, 
//per poter poi essere confrontata con gli altri rivelatori
//come spiegato nel file cose da fare.txt
#include <TFile.h>
#include <TFitResult.h>
#include <Riostream.h>
#include <TH1F.h>
#include <TLeaf.h>
#include <stdio.h>
#include <TTree.h>

using namespace std;

// argv[1] = posizione e nome file input
// argv[2] = nome file output
int main(int argc, char *argv[])  //
{
	if(argc < 2)
	{ 
		cout << "Non hai inserito il nome del file input!" << endl;
		return 1;
	}
	else if(argc == 2)
	{
		cout << "Non hai inserito il nome del file output!" << endl;
		return 1;
	}
	
	Int_t anno, mese, giorno, numDay, numFiles;
	ifstream mIn (mNomeFileIn , ios::in);
	ofstream mOut(mNomeFileOut, ios::out | ios::app);
	
	mOut.close();
	mIn .close();
	return 0;
}
