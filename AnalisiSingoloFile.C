// primo programma studio Polar

// il programma analizza un file root, il cui indirizzo e nome
// è fornito in input al programma
// fitta il grafico dei deltaT con un esponenziale e ne ricava chi quadro e rate
// se il chi quadro è minore di un valore massimo fissato,
// calcola e appende in un file il valore del rate e della latitudine media

#include <TFile.h>
#include <TFitResult.h>
#include <Riostream.h>
#include <TH1F.h>
#include <TLeaf.h>
#include <stdio.h>
#include <TTree.h>

using namespace std;

#define MAX_CHISQUARE 2

//argv[1] : posizione e nome file
//argv[2] : nome file output (ad esempio Rate.txt) //da aggiungere ancora questa opzionalità
int main(int argc, char *argv[])
{
	if(argc != 2)
	{ 
		cout << "Non hai inserito il nome del file!" << endl;
		return 1;
	}
	
	
	Char_t *mNomeFile = argv[1]; //bisogna dare sia indirizzo che nome del file
	//ad esempio:	/mnt/c/Users/casa/Desktop/Tesi/StudioPolar/POLA-01/2019-01-31/POLA-01-2019-01-31-381284802_dst.root
	cout << "Analisi in corso del file: " << mNomeFile << endl;
	TFile *mFileIn = new TFile(mNomeFile);
	const Char_t *mNomeFileOut = "Rate.txt";
	ofstream mOut(mNomeFileOut, ios::out | ios::app);
	
	
	TH1F *mDeltaT=(TH1F *)mFileIn->Get("DeltaTime");
	
	//fitto con un esponenziale
	mDeltaT->Fit("expo");
	TFitResultPtr r = mDeltaT->Fit("expo","SNQ");	//S per salvare in r; N per non plottare; Q per minimizzare l'output a terminale

	//memorizzo chi quadro e rate
	Double_t mChiSquare = r->Chi2() / r->Ndf();
	Double_t mRate1 = -r->Value(1);  //rate1: slope del fit
	
	Double_t mRate2 = 1/mDeltaT->GetMean();   //rate2: 1/tempomedio
	
	if(mChiSquare < MAX_CHISQUARE) //per ora è fissato a 2 il chi quadro massimo
	{
		if(!mOut.is_open())
		{
			cout << "Errore apertura file " << mNomeFileOut <<  endl;
			return 1;
		}
		
		//calcolo la latitudine media
		TTree *mGpsTree = (TTree *)mFileIn->Get("gps");
		Int_t nEvents = mGpsTree->GetEntries();
		Float_t mSingleLat;
		mGpsTree->SetBranchAddress("Latitude",&mSingleLat);
		mGpsTree->SetBranchStatus("*",0); //disable all branches per velocizzare
		mGpsTree->SetBranchStatus("Latitude",1);
		
		Double_t sumLatitude = 0;
		for(Int_t i = 0; i < nEvents; i++)
		{
			mGpsTree->GetEntry(i);
			sumLatitude += mSingleLat;
		}

		Double_t mLatitudine = sumLatitude / nEvents;
		
		//scrivo nel file output
		mOut << mRate1 << "\t" << mRate2 << "\t" << mLatitudine << endl;
	}
	
	//chiudo i files
	mOut.close();
	mFileIn->Close();
	return 0;
}