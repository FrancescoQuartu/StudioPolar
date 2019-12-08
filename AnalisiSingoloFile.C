// primo programma studio Polar

// da compilare e poi lanciare con 
// ./AnalisiSingoloFile.exe percorsofileinput nomefileoutput

// il programma analizza un file root, il cui indirizzo e nome
// è fornito in input al programma
// fitta il grafico dei deltaT con un esponenziale e ne ricava chi quadro e rate
// qualunque sia il chi quadro, scrive dentro un file testo le seguenti informazioni:
// rate1(fit), rate2(media), chiquadro, latitudine, pressione, giorno, mese, anno

//poi bisognerà fare uno script che legga questo file e crei il file root

#include <TFile.h>
#include <TFitResult.h>
#include <Riostream.h>
#include <TH1F.h>
#include <TLeaf.h>
#include <stdio.h>
#include <TTree.h>

using namespace std;

//argv[1] : posizione e nome file
//argv[2] : nome file output (ad esempio Rate.txt) //da aggiungere ancora questa opzionalità
int main(int argc, char *argv[])
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
	/////////////apro i files/////////////////
	Char_t *mNomeFile = argv[1]; //bisogna dare sia indirizzo che nome del file
	//ad esempio:	/mnt/c/Users/casa/Desktop/Tesi/StudioPolar/POLA-01/2019-01-31/POLA-01-2019-01-31-381284802_dst.root
	cout << "Analisi in corso del file: " << mNomeFile << endl;
	TFile *mFileIn = new TFile(mNomeFile);
	Char_t *mNomeFileOut = argv[2];
	ofstream mOut(mNomeFileOut, ios::out | ios::app);
	if(!mOut.is_open())
	{
		cout << "Errore apertura file " << mNomeFileOut <<  endl;
		return 1;
	}
	/////////////////////////////////////////////
	
	
	//fitto la distribuzione dei tempi con un esponenziale
	TH1F *mDeltaT=(TH1F *)mFileIn->Get("DeltaTime");
	mDeltaT->Fit("expo");
	TFitResultPtr r = mDeltaT->Fit("expo","SNQ");	//S per salvare in r; N per non plottare; Q per minimizzare l'output a terminale

	//memorizzo chi quadro e rate
	Double_t mChiSquare = r->Chi2() / r->Ndf();
	Double_t mRate1 = -r->Value(1);  //rate1: slope del fit
	Double_t mErrRate1   = r->ParError(1); //errore rate1
	
	Double_t mRate2 = 1/mDeltaT->GetMean(); //frequenza media = 1/DeltaTMedio
	Double_t mStdDevMean = mDeltaT->GetMean() / sqrt(mDeltaT->GetEntries());
	Double_t mErrRate2 = mRate2 / mDeltaT->GetMean() * mStdDevMean; //
	
	////////////////salvo pressione e temperaturaoutdoor//////////////
	TTree *mWeatherTree = (TTree *)mFileIn->Get("Weather");
	Int_t nEvents = mWeatherTree->GetEntries();
	Float_t mPressure;
	Float_t mOutdoorTemp;
	mWeatherTree->SetBranchAddress("Pressure",&mPressure);
	mWeatherTree->SetBranchAddress("OutdoorTemperature",&mOutdoorTemp);
	mWeatherTree->SetBranchStatus("*",0);
	mWeatherTree->SetBranchStatus("Pressure",1);
	mWeatherTree->SetBranchStatus("OutdoorTemperature",1);
	
	mWeatherTree->GetEntry(0);
	//////////////////////////////////////////////////////////////////
	
	/////dall'header prendo numero medio di satelliti, giorno, mese anno e latitudine media/////////
	TTree *mHeaderTree = (TTree *)mFileIn->Get("Header");
	Int_t mDay, mMonth, mYear;
	Float_t mNSatellites, mLatitudine, mLongitudine, mAltitudine;
	mHeaderTree->SetBranchAddress("day",&mDay);
	mHeaderTree->SetBranchAddress("month",&mMonth);
	mHeaderTree->SetBranchAddress("year",&mYear);
	mHeaderTree->SetBranchAddress("latitude",&mLatitudine);
	mHeaderTree->SetBranchAddress("longitude",&mLongitudine);
	mHeaderTree->SetBranchAddress("altitude",&mAltitudine);
	mHeaderTree->SetBranchAddress("nSatellites",&mNSatellites);
	
	mHeaderTree->GetEntry(0);
	
	//////////////////////////////////////////////////////////////////
	
	
	////////////////scrivo nel file output///////////////////
	mOut << mRate1 << "\t" << mErrRate1 << "\t" << mRate2 << "\t" << mErrRate2 << "\t" << mLatitudine << "\t" << mOutdoorTemp << "\t" << mLongitudine << "\t" << mAltitudine << "\t" << mChiSquare << "\t" << mPressure << "\t" << mNSatellites << "\t" << mDay << "\t" << mMonth << "\t" << mYear << endl;
	
	//chiudo i files
	mOut.close();
	mFileIn->Close();
	return 0;
}