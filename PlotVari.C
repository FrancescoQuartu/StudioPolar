void PlotVari()
{
	ifstream mIn ("TagliPOLA-01.txt" , ios::in);
	//leggo dalla riga N1 alla riga N2
	Int_t NMAX = 16000;
	Int_t N1 = 0;//3100;
	Int_t N2 = NMAX;//10900;
	
	Float_t vuoto;
	string vuota;
	getline(mIn, vuota); //la prima riga del file la salto
	Float_t Rate [N2-N1];
	Float_t Latitudine[N2-N1];
	Float_t Longitudine[N2-N1];
	Float_t Altitudine[N2-N1];
	Float_t Riga[N2-N1];
	for(int i = 0; i < N1; i++) 	getline(mIn, vuota); //salto le prime N1 righe
	for(int i = N1; i < N2; i++)	
	{
		mIn >>Rate[i-N1]>>Latitudine[i-N1]>>Longitudine[i-N1]>>Altitudine[i-N1]>>vuoto>>vuoto>>vuoto>>vuoto>>vuoto>>vuoto;
		Riga[i-N1] = i;
	}
	
	//TGraph *gr1 = new TGraph (N2-N1, Latitudine, Rate);
	TGraph *gr1 = new TGraph(N2-N1, Altitudine, Rate);
	
	
	//gr1->GetXaxis()->SetLimits(960,1035); //Per le x
	//gr1->GetHistogram()->SetMaximum(40.); //Per le          
    //gr1->GetHistogram()->SetMinimum(24.); //Y

	gr1->Draw("AP*");


	
	mIn.close();
}
