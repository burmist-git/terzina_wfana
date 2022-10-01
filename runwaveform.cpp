//my
#include "src/waveform.hh"

//C, C++
#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <fstream>
#include <iomanip>
#include <time.h>

//root
#include "TRandom3.h"

using namespace std;

int main(int argc, char *argv[]){
  //
  clock_t start, finish;
  start = clock();
  //
  if(argc == 1){
    TRandom3 *rnd = new TRandom3(123123);
    waveform *wf = new waveform();
    //
    delete rnd;
    delete wf;
  }
  else{
    cout<<"  wavefrom class test:            "<<endl
	<<"  (noinput parameters needed)     "<<endl;
  }
  //
  finish = clock();
  cout<<" time of work "<<((finish - start)/CLOCKS_PER_SEC)<<endl;
  //
  return 0;
}
