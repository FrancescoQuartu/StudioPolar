//questo programma prende in input il file Rate.txt o RateRIVELATORE.txt
//e calcola una media per ogni giorno di rate e latitudine, 
//per poter poi essere confrontata con gli altri rivelatori
//come spiegato nel file cose da fare.txt

#include <iostream>
#include <stdio.h>


using namespace std;

// argv[1] = posizione e nome file input
// argv[2] = nome file output
int main(int argc, char *argv[])  //
{
	const float CHIQUADROMIN = 2, LADITUDINEMIN = 5, LATITUDINEMAX = 85, RATEMIN = 20, RATEMAX = 45;
	
	
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
	
	int anno, mese, giorno, numDay, numFiles;
	ifstream mIn (argv[1] , ios::in);
	ofstream mOut(argv[2], ios::out | ios::app);
	
	float Rate1, Rate2, Latitudine, ChiQuadro, Pressione, NumSatelliti;
	int	Giorno, Mese, Anno;
	mOut << "Rate1\tRate2\tLatitudine\tGiorno\tMese\tAnno" << endl;
	while(mIn >> Rate1 >> Rate2 >> Latitudine >> ChiQuadro >> Pressione >> NumSatelliti >> Giorno >> Mese >> Anno)
	{
		int numDay = (Anno-2018) * 400 + Mese * 13 + Giorno * 33;
		int numFiles = 0;
		float sommaRate1 = 0;
		float sommaRate2 = 0;  // il primo dato lo perdo purtroppo
		float sommaLatitudine = 0;
		
		while(mIn >> Rate1 >> Rate2 >> Latitudine >> ChiQuadro >> Pressione >> NumSatelliti >> Giorno >> Mese >> Anno)
		{
			int newNumDay = (Anno-2018) * 400 + Mese * 13 + Giorno * 33;
			int Giorno1 = Giorno, Mese1 = Mese, Anno1 = Anno;
			if(newNumDay == numDay && ChiQuadro < CHIQUADROMIN && Latitudine > LADITUDINEMIN && Latitudine < LATITUDINEMAX && Rate1 > RATEMIN && Rate1 < RATEMAX)
			{
				numFiles++;
				sommaRate1 += Rate1;
				sommaRate2 += Rate2;
				sommaLatitudine += Latitudine;
			}
			else if(newNumDay == numDay) continue;
			else break;
		}
		
		float rateMedio1 = sommaRate1 / numFiles;
		float rateMedio2 = sommaRate2 / numFiles;
		float latitudineMedia = sommaLatitudine / numFiles;
		mOut << rateMedio1 << "\t" << rateMedio2 << "\t" << latitudineMedia << "\t" << Giorno1 << "\t" << Mese1 << "\t" << Anno1 << endl;
	}
	
	
	mOut.close();
	mIn .close();
	return 0;
}
