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
  _nPoints = 1;
  _wfA = new double[_nPoints];
  _wfT = new double[_nPoints];
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

void waveform::GetMaximumTimeAmpl_FWHM_FWTM( Double_t &wf_tm, Double_t &wf_am, Double_t &wf_sig_fwhm, Double_t &wf_sig_fwtm){
  wf_tm = -999.0;
  wf_am = -999.0;
  wf_sig_fwhm = -999.0;
  wf_sig_fwtm = -999.0;
  Int_t i_a_max = 0;
  for(Int_t i = 0;i<_nPoints;i++){
    if(wf_am < _wfA[i]){
      wf_am = _wfA[i];
      i_a_max = i;
    }
  }
  if(i_a_max>=0 && i_a_max<_nPoints){
    wf_tm = _wfT[i_a_max];
  }
  else
    assert(0);
  wf_sig_fwhm = findSigWidth(i_a_max,wf_am/2.0);
  wf_sig_fwtm = findSigWidth(i_a_max,wf_am/10.0);
}

Double_t waveform::findSigWidth( Int_t i0, Double_t th){
  Double_t wf_sig_t_L = 0.0;
  Double_t wf_sig_t_R = 0.0;
  for(Int_t i = i0;i>0;i--){
    if(_wfA[i]>th && _wfA[i-1]<=th){
      wf_sig_t_L = _wfT[i];
      break;
    }
  }
  for(Int_t i = i0;i<(_nPoints-1);i++){
    if(_wfA[i]>th && _wfA[i+1]<=th){
      wf_sig_t_R = _wfT[i];
      break;
    }
  }
  return (wf_sig_t_R - wf_sig_t_L);
}
