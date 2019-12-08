#include <iostream>
#include <stdio.h>
#include <fstream>

//#Rate1	ErrRate1	Rate2	ErrRate2	Latitudine	TempOut	Longitudine	Altitudine	ChiQuadro	Pressione	NumSatelliti	Giorno	Mese	Anno

//nota: se non fai le dovute sostituzioni nel file testo input non funziona:
//nan         -> 10000
//inf         -> 10000
//1,79769e+38 -> 10000  (o eventuali altri numeri altissimi)

using namespace std;

// argv[1] = posizione e nome file input
// argv[2] = nome file output
int main(int argc, char *argv[])  //
{
	const float CHIQUADROMIN = 2, LATITUDINEMIN = 5, LATITUDINEMAX = 85, RATEMIN = 20, RATEMAX = 245, ALTITUDINEMAX = 10000, LONGITUDINEMAX = 10000;
	const int NUMRIGHE = 18640;
	
	
	int Anno, Mese, Giorno;
	float Rate1, ErrRate1, Rate2, ErrRate2, Latitudine, TempOut, Longitudine, Altitudine, ChiQuadro, Pressione,NumSatelliti;
	ifstream mIn ("RateTotalePOLA-01.txt" , ios::in);
	ofstream mOut("TagliPOLA-01.txt", ios::out);
	
	if(!mIn.is_open())
	{
		cout << "Errore file input" << endl;
		return 1;
	}
	if(!mOut.is_open())
	{
		cout << "Errore file output" << endl;
		return 1;
	}
	
	string vuota;		//la prima riga di commento
	getline(mIn, vuota); //la prima riga del file la salto	
	
	mOut << "Rate1\tErrRate1\tRate2\tErrRate2\tLatitudine\tTempOut\tLongitudine\tAltitudine\tChiQuadro\tPressione\tNumSatelliti\tGiorno\tMese\tAnno" << endl;
	for(int i = 0; i < NUMRIGHE; i++)
	{
		mIn >> Rate1 >> ErrRate1 >> Rate2 >> ErrRate2 >> Latitudine >> TempOut >> Longitudine >> Altitudine >> ChiQuadro >> 
		Pressione >> NumSatelliti >> Giorno >> Mese >> Anno;
		
		if(ChiQuadro < CHIQUADROMIN && Longitudine < LONGITUDINEMAX && Altitudine != 0 && Altitudine < ALTITUDINEMAX && Latitudine > LATITUDINEMIN 
			&& Latitudine < LATITUDINEMAX && Rate2 > RATEMIN && Rate2 < RATEMAX && Pressione > 0)
		
		mOut << Rate1 << "\t" << ErrRate1 << "\t" << Rate2 << "\t" << ErrRate2 << "\t" << Latitudine << "\t" << TempOut << "\t" << Longitudine << "\t" << 
			Altitudine << "\t" << ChiQuadro << "\t" << Pressione << "\t" << NumSatelliti << "\t" << Giorno << "\t" << Mese << "\t" << Anno << endl;
	}
	mOut.close();
	mIn .close();
	return 0;
}
