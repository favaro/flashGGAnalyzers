#define photonTree_cxx
#include "photonTree.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void photonTree::Loop()
{
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
   }
}


float photonTree::StringToFloat( TString &varname )
{

  float var = -999;

  if( varname == "pho_pt" )    var = photonBranch_phoPt;
   // add here all variables you want to plot 
    
  return var;
}


TString photonTree::StringToTitle( TString &varname )
{

  TString title = "";
  if( varname == "pho_pt" )   title = "p_{T}(#gamma) (GeV)"; 

  return title;
}

