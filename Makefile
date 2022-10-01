RELVERSION  = $(shell cat .release)

ROOTCFLAGS    = $(shell $(ROOTSYS)/bin/root-config --cflags)
ROOTLIBS      = $(shell $(ROOTSYS)/bin/root-config --libs)
ROOTGLIBS     = $(shell $(ROOTSYS)/bin/root-config --glibs)

MakefileFullPath = $(abspath $(lastword $(MAKEFILE_LIST)))
MakefileDirFullPath = $(shell dirname $(MakefileFullPath))
INSTALLDIR = $(MakefileDirFullPath)/install.$(RELVERSION)/


CXX  = g++
CXX += -I./
CXX += -I./obj/
CXX += -I./src/

CXXFLAGS  = -g -Wall -fPIC -Wno-deprecated
CXXFLAGS += $(ROOTCFLAGS)
CXXFLAGS += $(ROOTLIBS)
CXXFLAGS += $(ROOTGLIBS)
CXXFLAGS += -std=c++14
CXXFLAGS += -fconcepts

OUTLIB = ./obj/

#----------------------------------------------------#

all: makedir runwaveform

makedir:
	mkdir -p $(OUTLIB);

.PHONY: printmakehelp_and_reminder
printmakehelp_and_reminder: runterzina_wfSim.cpp Makefile
	$(info  /******************************************************************************/)
	$(info  * task --> printmakehelp_and_reminder: runterzina_wfSim.cpp Makefile          *)
	$(info  * $$@ ----> $@                                         *)
	$(info  * $$< --------------------------------> $<                   *)
	$(info  * $$^ --------------------------------> $^          *)
	$(info  /******************************************************************************/)

obj/waveform.o: src/waveform.cpp src/waveform.hh
	$(CXX) -c -o $@ $< $(CXXFLAGS) 

obj/libwfana.so: obj/waveform.o
	$(CXX) -shared -o $@ $^

runwaveform: runwaveform.cpp obj/waveform.o
	$(CXX) -o $@ $^ $(CXXFLAGS)

install: makedir obj/libwfana.so
	mkdir -p $(INSTALLDIR);
	cp $(OUTLIB)libwfana.so $(INSTALLDIR)libwfana.so
	cp src/*.hh $(INSTALLDIR).

cleaninstall:
	rm -rf $(INSTALLDIR)

clean:
	rm -f runwaveform
	rm -f *~
	rm -f src/*~
	rm -f $(OUTLIB)*.o
	rm -f $(OUTLIB)*.so
