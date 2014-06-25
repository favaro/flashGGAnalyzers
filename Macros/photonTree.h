//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Jun 24 10:28:25 2014 by ROOT version 5.34/10
// from TTree photonTree/per-photon tree
// found on file: tree.root
//////////////////////////////////////////////////////////

#ifndef photonTree_h
#define photonTree_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Fixed size dimensions of array or collections stored in the TTree if any.

class photonTree {
public :
   TTree          *fChain;  
   Int_t           fCurrent;

   TTree *tree;

   Float_t         photonBranch_phoPt;
   Float_t         photonBranch_phoEta;


   TBranch        *b_photonBranch; 

   photonTree( TString filename );  // CF
   virtual ~photonTree();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);

   float            StringToFloat( TString& );
   TString          StringToTitle( TString& ); 
};

#endif

#ifdef photonTree_cxx

photonTree::photonTree( TString filename ) : fChain(0)  // CF
{

  tree = 0;

   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject( filename );
      if (!f || !f->IsOpen()) {
         f = new TFile( filename );
      }
      tree = (TTree*)gDirectory->Get("commissioning/photonTree");

   }
   Init(tree);
}

photonTree::~photonTree()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t photonTree::GetEntry(Long64_t entry)
{

   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t photonTree::LoadTree(Long64_t entry)
{

   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void photonTree::Init(TTree *ttree)
{

   if (!ttree) return;
   fChain = ttree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("photonBranch", &photonBranch_phoPt, &b_photonBranch);
   Notify();
}

Bool_t photonTree::Notify()
{
 
   return kTRUE;
}

void photonTree::Show(Long64_t entry)
{

   if (!fChain) return;
   fChain->Show(entry);
}
Int_t photonTree::Cut(Long64_t entry)
{

   return 1;
}
#endif 
