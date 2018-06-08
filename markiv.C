#include "TH1.h"
#include "TF1.h"

void markiv() {

	
	Int_t counter = 0;
	Int_t bins = 500;
	Float_t minHist = -0.015;
	Float_t maxHist = 0.015;

	//Para ver cuántos datos se tiene

	ifstream datos("wDM.txt");
	string line;
	while(getline(datos,line)){
		Float_t event = 0;
		event = atof(line.c_str());
		if (event <= 0.015 && event >= -0.015)
		counter ++;
	}	

	datos.close();
        cout<<counter<<endl;

	//Función que generará el histograma
	TH1F *h = new TH1F("h","wDM",bins,minHist,maxHist); //( , , #bin,Inf,Max)

	//Llenar el histograma
	ifstream datos2("wDM.txt");
	//string line;

        while(getline(datos2,line)){
		Float_t event = 0;
		event = atof(line.c_str());
		h->Fill(event);
	}	

	datos2.close();
	
	//Parámetros para el ajuste
	Double_t par[3];

	//Gaussianas
	TF1 *g1    = new TF1("g1","gaus",minHist,maxHist);
	//TF1 *g2    = new TF1("g2","gaus",1000,1500);
	//TF1 *g3    = new TF1("g3","gaus",1500,2700);
	//TF1 *g4    = new TF1("g4","gaus",3000,maxHist);


	//Modelo
	TF1 *total = new TF1("total","gaus(0)+gaus(3)+gaus(6)+gaus(9)",minHist,maxHist);
	total->SetLineColor(2);

	//Nombrar parámetros para el modelo
	total->SetParName(0,"Yield 1");
  	total->SetParName(1,"Mean 1");
  	total->SetParName(2,"Sigma 1");
  	//total->SetParName(3,"Yield 2");
  	//total->SetParName(4,"Mean 2");
  	//total->SetParName(5,"Sigma 2");
	//total->SetParName(6,"Yield 3");
  	//total->SetParName(7,"Mean 3");
  	//total->SetParName(8,"Sigma 3");
	//total->SetParName(9,"Yield 4");
  	//total->SetParName(10,"Mean 4");
  	//total->SetParName(11,"Sigma 4");


	//Ajuste de cada gaussiana
	h->Fit(g1,"R");
	//h->Fit(g2,"R+");
	//h->Fit(g3,"R+");
	//h->Fit(g4,"R+");

	//Se obtienen los parámetros de cada gaussiana ajustada y se guardan en el arreglo par
	g1->GetParameters(&par[0]);
   	//g2->GetParameters(&par[3]);
	//g3->GetParameters(&par[6]);
	//g4->GetParameters(&par[9]);



	//Se toman los parámetros para el ajuste total desde el arreglo par
	total->SetParameters(par);

	//Se hace el ajuste total
	total->SetLineColor(kBlack);
	//g1->SetLine
   	h->SetStats(0);
  	h->Fit(total,"R+");

	//Graficar	
	TCanvas* c = new TCanvas("Window1","Window1",800,600);
	c->cd();
	h->Draw();

	//Chi² reducida
	Double_t Chi2 = total->GetChisquare();
	Double_t NDF = total->GetNDF();
	Double_t Chi2NDF = Chi2/NDF; 
	cout<<"Chisquare: "<<Chi2<<endl;
	cout<<"NDF: "<<NDF<<endl;
	cout<<"Chisquare/ndf: "<<Chi2NDF<<endl;


}
