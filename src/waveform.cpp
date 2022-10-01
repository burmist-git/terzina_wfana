//my
#include "waveform.hh"

//root
#include <TGraph.h>
#include <TString.h>
#include <TCanvas.h>
#include <TLine.h>
#include <TPaveLabel.h>
#include <TString.h>
#include <TSpline.h>
#include <TMultiGraph.h>
#include <TFile.h>
#include <TH2D.h>
#include <TMath.h>

//C, C++
#include <iostream>
#include <fstream>
#include <assert.h>
#include <iomanip>
#include <stdio.h>

using namespace std;

waveform::waveform(){
  _nPoints = 0;
}

waveform::waveform(TGraph *gr){
  _nPoints = gr->GetN();
  _wfA = new double[_nPoints];
  _wfT = new double[_nPoints];
  Double_t t;
  Double_t a;
  for(int i = 0;i<_nPoints;i++){
    gr->GetPoint(i,t,a);
    _wfA[i] = a;
    _wfT[i] = t;    
  }
}

waveform::~waveform(){  
  delete _wfT;
  delete _wfA;
}
