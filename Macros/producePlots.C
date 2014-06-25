#include<TStyle.h>
#include<TFile.h>
#include<TDirectory.h>
#include<TTree.h>
#include<TCanvas.h>
#include<TPaveText.h>
#include<TH1F.h>
#include<TLegend.h>
#include<TROOT.h>
#include <fstream>
#include <THStack.h>
#include <TLatex.h>
#include <iostream>
#include <utility>
#include <TColor.h>
#include <algorithm>
#include <TLorentzVector.h>
#include<TGraphErrors.h>
#include "TStyle.h"
#include "TPad.h"
#include "./plotter.C"


void producePlots()
{

  TString inputfilename = "tree.root";
  TString outputdirname = "plots/";

  PlottingClass *plotter = new PlottingClass();

  plotter->initialize( inputfilename );

  TString var = "pho_pt";         plotter->makePlot( var,50,0,500,0);

}
