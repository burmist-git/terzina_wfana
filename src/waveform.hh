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
  
private : 
  Int_t _nPoints;
  Double_t *_wfA;
  Double_t *_wfT;
  
};

#endif
