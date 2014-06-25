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
#include "./photonTree.C"

using namespace std;

class PlottingClass{
public:

  PlottingClass( );   // input, output ?

  void initialize( TString & ); // filename
  void makePlot( TString &, int, float, float, int ); // varname, nbins, xmin, xmax, islog

  void setTDRStyle();
    
  photonTree* treeobj;



};


// ********************************************************


PlottingClass::PlottingClass( )
{

}

void PlottingClass::initialize( TString &filename )
{

  treeobj = new photonTree( filename );

}

void PlottingClass::setTDRStyle()
{
    
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetCanvasColor(kWhite);
  gStyle->SetCanvasDefH(1500); //Height of canvas
  gStyle->SetCanvasDefW(1500); //Width of canvas
  gStyle->SetCanvasDefX(0);   //POsition on screen
  gStyle->SetCanvasDefY(0);
	
  gStyle->SetPadBorderMode(0);
  gStyle->SetPadColor(kWhite);
  gStyle->SetPadGridX(false);
  gStyle->SetPadGridY(false);
  gStyle->SetGridColor(0);
  gStyle->SetGridStyle(3);
  gStyle->SetGridWidth(1);
  
  gStyle->SetFrameBorderMode(0);
  gStyle->SetFrameBorderSize(0.1);
  gStyle->SetFrameFillColor(0);
  gStyle->SetFrameFillStyle(0);
  gStyle->SetFrameLineColor(1);
  gStyle->SetFrameLineStyle(1);
  gStyle->SetFrameLineWidth(0.1);
  
  gStyle->SetHistLineColor(1);
  gStyle->SetHistLineStyle(0);
  gStyle->SetHistLineWidth(0.1);
  
  gStyle->SetEndErrorSize(2);
  gStyle->SetErrorX(0.);
  gStyle->SetEndErrorSize(1.2);
  gStyle->SetMarkerStyle(20);
  
  gStyle->SetOptFit(1);
  gStyle->SetFitFormat("5.4g");
  gStyle->SetFuncColor(2);
  gStyle->SetFuncStyle(1);
  gStyle->SetFuncWidth(1);
  
  gStyle->SetOptDate(0);
  gStyle->SetOptStat(0);
  
  // Margins:
  gStyle->SetPadTopMargin(0.05);
  gStyle->SetPadBottomMargin(0.13);
  gStyle->SetPadLeftMargin(0.16);
  gStyle->SetPadRightMargin(0.02);
  
  // For the Global title:
  
  gStyle->SetOptTitle(0);
  gStyle->SetTitleFont(42);
  gStyle->SetTitleColor(1);
  gStyle->SetTitleTextColor(1);
  gStyle->SetTitleFillColor(10);
  gStyle->SetTitleFontSize(0.05);
  
  // For the axis titles:
  
  gStyle->SetTitleColor(1, "XYZ");
  gStyle->SetTitleFont(42, "XYZ");
  gStyle->SetTitleSize(0.06, "XYZ");
  // gStyle->SetTitleXSize(Float_t size = 0.02); // Another way to set the size?
  // gStyle->SetTitleYSize(Float_t size = 0.02);
  gStyle->SetTitleXOffset(0.9);
  gStyle->SetTitleYOffset(1.25);
  // gStyle->SetTitleOffset(1.1, "Y"); // Another way to set the Offset
  
  // For the axis labels:
  
  gStyle->SetLabelColor(1, "XYZ");
  gStyle->SetLabelFont(42, "XYZ");
  gStyle->SetLabelOffset(0.007, "XYZ");
  gStyle->SetLabelSize(0.045, "XYZ");
  
  // For the axis:
  
  gStyle->SetAxisColor(1, "XYZ");
  gStyle->SetStripDecimals(kTRUE);
  gStyle->SetTickLength(0.03, "XYZ");
  gStyle->SetNdivisions(510, "XYZ");
  gStyle->SetPadTickX(1);  // To get tick marks on the opposite side of the frame
  gStyle->SetPadTickY(1);
  
  // Change for log plots:
  gStyle->SetOptLogx(0);
  gStyle->SetOptLogy(0);
  gStyle->SetOptLogz(0);
  
  gROOT->ForceStyle();
}


void PlottingClass::makePlot( TString &varname, int nbins, float xmi, float xma, int log )
{

  setTDRStyle();
  TH1F::SetDefaultSumw2(kTRUE);

  TString Variable = varname;
  int     Nbin = nbins;
  float   xmin = xmi;
  float   xmax = xma;
  int     isLog = log;
  //float binw = (xmax - xmin)/(float)Nbin;

  TH1F *histo = new TH1F( "histo", "", Nbin, xmin, xmax );  // this will turn into a vector
 
  int nentries;
  nentries = treeobj->fChain->GetEntriesFast();

  for( int ientry = 0; ientry < nentries; ientry++ ) {
    treeobj->GetEntry( ientry );

    cout << " var " <<  Variable << " " << treeobj->photonBranch_phoPt << " " << treeobj->StringToFloat(Variable) << endl;

    histo->Fill( treeobj->StringToFloat(Variable) );
    histo->GetXaxis()->SetTitle( treeobj->StringToTitle(Variable) );

  } // end of event loop

  
  //delete histo;

}
