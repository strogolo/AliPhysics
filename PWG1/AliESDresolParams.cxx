/**************************************************************************
 * Copyright(c) 1998-1999, ALICE Experiment at CERN, All rights reserved. *
 *                                                                        *
 * Author: The ALICE Off-line Project.                                    *
 * Contributors are mentioned in the code where appropriate.              *
 *                                                                        *
 * Permission to use, copy, modify and distribute this software and its   *
 * documentation strictly for non-commercial purposes is hereby granted   *
 * without fee, provided that the above copyright notice appears in all   *
 * copies and that both the copyright notice and this permission notice   *
 * appear in the supporting documentation. The authors make no claims     *
 * about the suitability of this software for any purpose. It is          *
 * provided "as is" without express or implied warranty.                  *
 **************************************************************************/

//************************************************************************
//
//   ESD track and V0 resolution parameterization
//   
//             
//    Origin: Marian Ivanov marian.ivanov@cern.ch
//-------------------------------------------------------------------------

/*
    Example usage:
    

*/


#include "TVectorD.h"
#include "TMath.h"
#include "TObjArray.h"
#include "AliESDresolParams.h"


ClassImp(AliESDresolParams)


 AliESDresolParams*    AliESDresolParams::fgInstance = 0; //! Instance of this class (singleton implementation)


AliESDresolParams::AliESDresolParams() :
  TObject(),  
  fResolDCAyy(0),            // resolution Y parameterization
  fResolDCAzz(0),            // resolution Z parameterization   
  fResolDCAphi(0),           // resolution phi parameterization - pt-theta
  fResolDCAth(0),            // resolution theta parameterization -pt-theta
  fResolDCA1pt(0),           // resolution 1/pt parameterization - pt-theta
  //
  fResolCyy(0),              // DCA resolution Y parameterization - r-pt
  fResolCzz(0),              // DCA resolution Z parameterization - r-pt
  fResolCphi(0),             // DCA resolution phi parameterization - r-pt
  fResolCth(0),              // DCA resolution theta parameterization - r-pt
  fResolC1pt(0)             // DCA resolution 1/pt parameterization - r-pt
{
  //
  // Default constructor
  //
}

Double_t AliESDresolParams::GetResolPrim(Int_t param, Float_t onept, Float_t tanth) const {
  //
  // Resolution at primary vertex
  // simple Resolution parameterization 
  // polynom of second order in 2D 
  // 
  if (!fResolDCAyy) return 0;
  TVectorD * pvec     = fResolDCAyy;
  if (param==1)  pvec = fResolDCAzz;
  if (param==2)  pvec = fResolDCAphi;
  if (param==3)  pvec = fResolDCAth;
  if (param==4)  pvec = fResolDCA1pt;
  TVectorD &vec = *pvec;
  //
  Float_t val = vec[0];
  val+= vec[1]*TMath::Abs(onept);
  val+= vec[2]*TMath::Abs(onept*onept);
  val+= vec[3]*TMath::Abs(tanth);
  val+= vec[4]*TMath::Abs(tanth*tanth);
  val+= vec[5]*TMath::Abs(onept*tanth);
  val*=val;
  return val;
}

Double_t AliESDresolParams::GetResolR(Int_t param, Float_t onept, Float_t radius) const {
  //
  // simple DCA resolution parameterization
  // polynom of second order in 2D 
  // 
  if (!fResolCyy) return 0;
  TVectorD * pvec     = fResolCyy;
  if (param==1)  pvec = fResolCzz;
  if (param==2)  pvec = fResolCphi;
  if (param==3)  pvec = fResolCth;
  if (param==4)  pvec = fResolC1pt;
  TVectorD &vec = *pvec;
  //
  Float_t val = vec[0];
  val+= vec[1]*TMath::Abs(onept);
  val+= vec[2]*TMath::Abs(radius);
  val+= vec[3]*TMath::Abs(onept*onept);
  val+= vec[4]*TMath::Abs(radius*radius);
  val+= vec[5]*TMath::Abs(radius*onept);
  val+= vec[6]*TMath::Abs(radius*radius*onept);
  val*=val;
  return val;
}

void AliESDresolParams::SetResolPrim(TObjArray* array){
  //
  // Set parameters - resolution at prim vertex
  //
  if (!array) return;  
  if (array->At(0)) 
    fResolDCAyy = new TVectorD(*((TVectorD*)array->At(0))); 
  if (array->At(1)) 
    fResolDCAzz = new TVectorD(*((TVectorD*)array->At(1))); 
  if (array->At(2)) 
    fResolDCAphi = new TVectorD(*((TVectorD*)array->At(2))); 
  if (array->At(3)) 
    fResolDCAth = new TVectorD(*((TVectorD*)array->At(3))); 
  if (array->At(4)) 
    fResolDCA1pt = new TVectorD(*((TVectorD*)array->At(4))); 
}

void AliESDresolParams::SetResolR(TObjArray* array){
  //
  // Set parameters - resolution at prim vertex
  //
  if (!array) return;  
  if (array->At(0)) 
    fResolCyy = new TVectorD(*((TVectorD*)array->At(0))); 
  if (array->At(1)) 
    fResolCzz = new TVectorD(*((TVectorD*)array->At(1))); 
  if (array->At(2)) 
    fResolCphi = new TVectorD(*((TVectorD*)array->At(2))); 
  if (array->At(3)) 
    fResolCth = new TVectorD(*((TVectorD*)array->At(3))); 
  if (array->At(4)) 
    fResolC1pt = new TVectorD(*((TVectorD*)array->At(4)));   
}




