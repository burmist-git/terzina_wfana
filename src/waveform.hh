#ifndef waveform_hh
#define waveform_hh

//root
#include <TROOT.h>

class TGraph;

class waveform{
  
public :
  waveform();
  waveform(TGraph *gr);
  ~waveform();
  inline Int_t GetnPoints(){return _nPoints;}
  void GetMaximumTimeAmpl_FWHM_FWTM( Double_t &wf_tm, Double_t &wf_am, Double_t &wf_sig_fwhm, Double_t &wf_sig_fwtm);
  Double_t findSigWidth( Int_t i0, Double_t th);
  
private : 
  Int_t _nPoints;
  Double_t *_wfA;
  Double_t *_wfT;
  
};

#endif
