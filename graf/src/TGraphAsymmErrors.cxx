// @(#)root/graf:$Name:  $:$Id: TGraphAsymmErrors.cxx,v 1.6 2000/12/13 15:13:50 brun Exp $
// Author: Rene Brun   03/03/99

/*************************************************************************
 * Copyright (C) 1995-2000, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

#include <string.h>
#include <fstream.h>

#include "TROOT.h"
#include "TGraphAsymmErrors.h"
#include "TStyle.h"
#include "TMath.h"
#include "TVirtualPad.h"

ClassImp(TGraphAsymmErrors)

//______________________________________________________________________________
//
//   A TGraphAsymmErrors is a TGraph with assymetric error bars.
//   The various format options to draw a TGraphAsymmErrors are explained in
//     TGraphAsymmErrors::Paint.
//
//  The picture below has been generated by the following macro:
//------------------------------------------------------------------------
//{
//   gROOT->Reset();
//   c1 = new TCanvas("c1","A Simple Graph with error bars",200,10,700,500);
//
//   c1->SetFillColor(42);
//   c1->SetGrid();
//   c1->GetFrame()->SetFillColor(21);
//   c1->GetFrame()->SetBorderSize(12);
//
//   Int_t n = 10;
//   Double_t x[n]  = {-0.22, 0.05, 0.25, 0.35, 0.5, 0.61,0.7,0.85,0.89,0.95};
//   Double_t y[n]  = {1,2.9,5.6,7.4,9,9.6,8.7,6.3,4.5,1};
//   Double_t exl[n] = {.05,.1,.07,.07,.04,.05,.06,.07,.08,.05};
//   Double_t eyl[n] = {.8,.7,.6,.5,.4,.4,.5,.6,.7,.8};
//   Double_t exh[n] = {.02,.08,.05,.05,.03,.03,.04,.05,.06,.03};
//   Double_t eyh[n] = {.6,.5,.4,.3,.2,.2,.3,.4,.5,.6};
//   gr = new TGraphAsymmErrors(n,x,y,exl,exh,eyl,eyh);
//   gr->SetTitle("TGraphAsymmErrors Example");
//   gr->SetMarkerColor(4);
//   gr->SetMarkerStyle(21);
//   gr->Draw("ALP");
//
//   c1->Update();
//}
//Begin_Html
/*
<img src="gif/gaerrors.gif">
*/
//End_Html
//

//______________________________________________________________________________
TGraphAsymmErrors::TGraphAsymmErrors(): TGraph()
{
//*-*-*-*-*-*-*-*-*-*-*TGraphAsymmErrors default constructor*-*-*-*-*-*-*-*-*-*-*-*
//*-*                  =====================================
   fEXlow       = 0;
   fEYlow       = 0;
   fEXhigh      = 0;
   fEYhigh      = 0;
}


//______________________________________________________________________________
TGraphAsymmErrors::TGraphAsymmErrors(Int_t n)
       : TGraph(n)
{
//*-*-*-*-*-*-*-*-*-*-*TGraphAsymmErrors normal constructor*-*-*-*-*-*-*-*-*-*-*-*-*
//*-*                  ====================================
//
//  the arrays are preset to zero

   if (n <= 0) {
      Error("TGraphAsymmErrors", "illegal number of points (%d)", n);
      return;
   }

   fEXlow       = new Double_t[n];
   fEYlow       = new Double_t[n];
   fEXhigh      = new Double_t[n];
   fEYhigh      = new Double_t[n];

   for (Int_t i=0;i<n;i++) {
      fEXlow[i]  = 0;
      fEXhigh[i] = 0;
      fEYlow[i]  = 0;
      fEYhigh[i] = 0;
   }
}


//______________________________________________________________________________
TGraphAsymmErrors::TGraphAsymmErrors(Int_t n, Float_t *x, Float_t *y, Float_t *exl, Float_t *exh, Float_t *eyl, Float_t *eyh)
       : TGraph(n,x,y)
{
//*-*-*-*-*-*-*-*-*-*-*TGraphAsymmErrors normal constructor*-*-*-*-*-*-*-*-*-*-*-*-*
//*-*                  ====================================
//
//  if exl,h or eyl,h are null, the corresponding arrays are preset to zero

   if (n <= 0) {
      Error("TGraphAsymmErrors", "illegal number of points (%d)", n);
      return;
   }

   fEXlow       = new Double_t[n];
   fEYlow       = new Double_t[n];
   fEXhigh      = new Double_t[n];
   fEYhigh      = new Double_t[n];

   for (Int_t i=0;i<n;i++) {
      if (exl) fEXlow[i]  = exl[i];
      else     fEXlow[i]  = 0;
      if (exh) fEXhigh[i] = exh[i];
      else     fEXhigh[i] = 0;
      if (eyl) fEYlow[i]  = eyl[i];
      else     fEYlow[i]  = 0;
      if (eyh) fEYhigh[i] = eyh[i];
      else     fEYhigh[i] = 0;
   }
}

//______________________________________________________________________________
TGraphAsymmErrors::TGraphAsymmErrors(Int_t n, Double_t *x, Double_t *y, Double_t *exl, Double_t *exh, Double_t *eyl, Double_t *eyh)
       : TGraph(n,x,y)
{
//*-*-*-*-*-*-*-*-*-*-*TGraphAsymmErrors normal constructor*-*-*-*-*-*-*-*-*-*-*-*-*
//*-*                  ====================================
//
//  if exl,h or eyl,h are null, the corresponding arrays are preset to zero

   if (n <= 0) {
      Error("TGraphAsymmErrors", "illegal number of points (%d)", n);
      return;
   }

   fEXlow       = new Double_t[n];
   fEYlow       = new Double_t[n];
   fEXhigh      = new Double_t[n];
   fEYhigh      = new Double_t[n];

   for (Int_t i=0;i<n;i++) {
      if (exl) fEXlow[i]  = exl[i];
      else     fEXlow[i]  = 0;
      if (exh) fEXhigh[i] = exh[i];
      else     fEXhigh[i] = 0;
      if (eyl) fEYlow[i]  = eyl[i];
      else     fEYlow[i]  = 0;
      if (eyh) fEYhigh[i] = eyh[i];
      else     fEYhigh[i] = 0;
   }
}

//______________________________________________________________________________
TGraphAsymmErrors::~TGraphAsymmErrors()
{
//*-*-*-*-*-*-*-*-*-*-*TGraphAsymmErrors default destructor*-*-*-*-*-*-*-*-*-*-*-*-*
//*-*                  ===============================

   delete [] fEXlow;
   delete [] fEXhigh;
   delete [] fEYlow;
   delete [] fEYhigh;
}

//______________________________________________________________________________
void TGraphAsymmErrors::ComputeRange(Double_t &xmin, Double_t &ymin, Double_t &xmax, Double_t &ymax)
{
  for (Int_t i=0;i<fNpoints;i++) {
     if (fX[i] -fEXlow[i]  < xmin) xmin = fX[i]-fEXlow[i];
     if (fX[i] +fEXhigh[i] > xmax) xmax = fX[i]+fEXhigh[i];
     if (fY[i] -fEYlow[i]  < ymin) ymin = fY[i]-fEYlow[i];
     if (fY[i] +fEYhigh[i] > ymax) ymax = fY[i]+fEYhigh[i];
  }
}

//______________________________________________________________________________
Double_t TGraphAsymmErrors::GetErrorX(Int_t i) const
{
//    This function is called by GraphFitChisquare.
//    It returns the quadratic error along X at point i.

   if (i < 0 || i >= fNpoints) return -1;
   if (!fEXlow && !fEXhigh) return -1;
   Double_t elow=0, ehigh=0;
   if (fEXlow)  elow  = fEXlow[i];
   if (fEXhigh) ehigh = fEXhigh[i];
   return TMath::Sqrt(elow*elow + ehigh*ehigh);
}

//______________________________________________________________________________
Double_t TGraphAsymmErrors::GetErrorY(Int_t i) const
{
//    This function is called by GraphFitChisquare.
//    It returns the quadratic error along Y at point i.

   if (i < 0 || i >= fNpoints) return -1;
   if (!fEYlow && !fEYhigh) return -1;
   Double_t elow=0, ehigh=0;
   if (fEYlow)  elow  = fEYlow[i];
   if (fEYhigh) ehigh = fEYhigh[i];
   return TMath::Sqrt(elow*elow + ehigh*ehigh);
}

//______________________________________________________________________________
void TGraphAsymmErrors::Paint(Option_t *option)
{
   // Paint this TGraphAsymmErrors with its current attributes
   //
   // by default horizonthal and vertical small lines are drawn at
   // the end of the error bars. if option "z" or "Z" is specified,
   // these lines are not drawn.

   const Int_t BASEMARKER=8;
   Double_t s2x, s2y, symbolsize;
   Double_t x, y, xl1, xl2, xr1, xr2, yup1, yup2, ylow1, ylow2, tx, ty;
   static Float_t cxx[11] = {1,1,0.6,0.6,1,1,0.6,0.5,1,0.6,0.6};
   static Float_t cyy[11] = {1,1,1,1,1,1,1,1,1,0.5,0.6};

   Bool_t endLines = kTRUE;
   if (strchr(option,'z')) endLines = kFALSE;
   if (strchr(option,'Z')) endLines = kFALSE;

   TGraph::Paint(option);

   TAttLine::Modify();

   symbolsize  = GetMarkerSize();
   Int_t mark  = GetMarkerStyle();
   Double_t cx  = 0;
   Double_t cy  = 0;
   if (mark >= 20 && mark < 31) {
      cx = cxx[mark-20];
      cy = cyy[mark-20];
   }

//*-*-      define the offset of the error bars due to the symbol size
   s2x  = gPad->PixeltoX(Int_t(0.5*symbolsize*BASEMARKER)) - gPad->PixeltoX(0);
   s2y  =-gPad->PixeltoY(Int_t(0.5*symbolsize*BASEMARKER)) + gPad->PixeltoY(0);
   tx   = 0.50*s2x;
   ty   = 0.50*s2y;

   gPad->SetBit(kClipFrame, TestBit(kClipFrame));
   for (Int_t i=0;i<fNpoints;i++) {
      x  = gPad->XtoPad(fX[i]);
      y  = gPad->YtoPad(fY[i]);
      if (x < gPad->GetUxmin()) continue;
      if (x > gPad->GetUxmax()) continue;
      if (y < gPad->GetUymin()) continue;
      if (y > gPad->GetUymax()) continue;
      xl1 = x - s2x*cx;
      xl2 = gPad->XtoPad(fX[i] - fEXlow[i]);
      if (xl1 > xl2) {
         gPad->PaintLine(xl1,y,xl2,y);
         if (endLines) gPad->PaintLine(xl2,y-ty,xl2,y+ty);
      }
      xr1 = x + s2x*cx;
      xr2 = gPad->XtoPad(fX[i] + fEXhigh[i]);
      if (xr1 < xr2) {
         gPad->PaintLine(xr1,y,xr2,y);
         if (endLines) gPad->PaintLine(xr2,y-ty,xr2,y+ty);
      }
      yup1 = y + s2y*cy;
      yup2 = gPad->YtoPad(fY[i] + fEYhigh[i]);
      if (yup2 > gPad->GetUymax()) yup2 =  gPad->GetUymax();
      if (yup2 > yup1) {
         gPad->PaintLine(x,yup1,x,yup2);
         if (endLines) gPad->PaintLine(x-tx,yup2,x+tx,yup2);
      }
      ylow1 = y - s2y*cy;
      ylow2 = gPad->YtoPad(fY[i] - fEYlow[i]);
      if (ylow2 < gPad->GetUymin()) ylow2 =  gPad->GetUymin();
      if (ylow2 < ylow1) {
         gPad->PaintLine(x,ylow1,x,ylow2);
         if (endLines) gPad->PaintLine(x-tx,ylow2,x+tx,ylow2);
      }
   }
   gPad->ResetBit(kClipFrame);
}


//______________________________________________________________________________
void TGraphAsymmErrors::Print(Option_t *) const
{
//*-*-*-*-*-*-*-*-*-*-*Print graph and errors values*-*-*-*-*-*-*-*-*-*-*-*
//*-*                  =============================
//

   for (Int_t i=0;i<fNpoints;i++) {
      printf("x[%d]=%g, y[%d]=%g, exl[%d]=%g, exh[%d]=%g, eyl[%d]=%g, eyh[%d]=%g\n"
         ,i,fX[i],i,fY[i],i,fEXlow[i],i,fEXhigh[i],i,fEYlow[i],i,fEYhigh[i]);
   }
}

//______________________________________________________________________________
void TGraphAsymmErrors::SavePrimitive(ofstream &out, Option_t *option)
{
    // Save primitive as a C++ statement(s) on output stream out

   char quote = '"';
   out<<"   "<<endl;
   if (gROOT->ClassSaved(TGraphAsymmErrors::Class())) {
       out<<"   ";
   } else {
       out<<"   TGraphAsymmErrors *";
   }
   out<<"grae = new TGraphAsymmErrors("<<fNpoints<<");"<<endl;
   out<<"   grae->SetName("<<quote<<GetName()<<quote<<");"<<endl;
   out<<"   grae->SetTitle("<<quote<<GetTitle()<<quote<<");"<<endl;

   SaveFillAttributes(out,"grae",0,1001);
   SaveLineAttributes(out,"grae",1,1,1);
   SaveMarkerAttributes(out,"grae",1,1,1);

   for (Int_t i=0;i<fNpoints;i++) {
      out<<"   grae->SetPoint("<<i<<","<<fX[i]<<","<<fY[i]<<");"<<endl;
      out<<"   grae->SetPointError("<<i<<","<<fEXlow[i]<<","<<fEXhigh[i]<<","<<fEYlow[i]<<","<<fEYhigh[i]<<");"<<endl;
   }
   if (strstr(option,"multigraph")) {
      out<<"   multigraph->Add(grae);"<<endl;
      return;
   }
   out<<"   grae->Draw("
      <<quote<<option<<quote<<");"<<endl;
}

//______________________________________________________________________________
void TGraphAsymmErrors::SetPoint(Int_t i, Double_t x, Double_t y)
{
//*-*-*-*-*-*-*-*-*-*-*Set x and y values for point number i*-*-*-*-*-*-*-*-*
//*-*                  =====================================

   if (i < 0) return;
   if (i >= fNpoints) {
   // re-allocate the object
      Double_t *savex   = new Double_t[i+1];
      Double_t *savey   = new Double_t[i+1];
      Double_t *saveexl = new Double_t[i+1];
      Double_t *saveeyl = new Double_t[i+1];
      Double_t *saveexh = new Double_t[i+1];
      Double_t *saveeyh = new Double_t[i+1];
      if (fNpoints > 0) {
         memcpy(savex,  fX,     fNpoints*sizeof(Double_t));
         memcpy(savey,  fY,     fNpoints*sizeof(Double_t));
         memcpy(saveexl,fEXlow, fNpoints*sizeof(Double_t));
         memcpy(saveeyl,fEYlow, fNpoints*sizeof(Double_t));
         memcpy(saveexh,fEXhigh,fNpoints*sizeof(Double_t));
         memcpy(saveeyh,fEYhigh,fNpoints*sizeof(Double_t));
      }
      if (fX)      delete [] fX;
      if (fY)      delete [] fY;
      if (fEXlow)  delete [] fEXlow;
      if (fEYlow)  delete [] fEYlow;
      if (fEXhigh) delete [] fEXhigh;
      if (fEYhigh) delete [] fEYhigh;
      fX  = savex;
      fY  = savey;
      fEXlow  = saveexl;
      fEYlow  = saveeyl;
      fEXhigh = saveexh;
      fEYhigh = saveeyh;
      fNpoints = i+1;
   }
   fX[i] = x;
   fY[i] = y;
}

//______________________________________________________________________________
void TGraphAsymmErrors::SetPointError(Int_t i, Double_t exl, Double_t exh, Double_t eyl, Double_t eyh)
{
//*-*-*-*-*-*-*-*-*-*-*Set ex and ey values for point number i*-*-*-*-*-*-*-*
//*-*                  =======================================

   if (i < 0) return;
   if (i >= fNpoints) {
   // re-allocate the object
      TGraphAsymmErrors::SetPoint(i,0,0);
   }
   fEXlow[i]  = exl;
   fEYlow[i]  = eyl;
   fEXhigh[i] = exh;
   fEYhigh[i] = eyh;
}

//______________________________________________________________________________
void TGraphAsymmErrors::Streamer(TBuffer &b)
{
   // Stream an object of class TGraphAsymmErrors.

   if (b.IsReading()) {
      UInt_t R__s, R__c;
      Version_t R__v = b.ReadVersion(&R__s, &R__c);
      if (R__v > 2) {
         TGraphAsymmErrors::Class()->ReadBuffer(b, this, R__v, R__s, R__c);
         return;
      }
      //====process old versions before automatic schema evolution
      TGraph::Streamer(b);
      fEXlow  = new Double_t[fNpoints];
      fEYlow  = new Double_t[fNpoints];
      fEXhigh = new Double_t[fNpoints];
      fEYhigh = new Double_t[fNpoints];
      if (R__v < 2) {
         Float_t *exlow  = new Float_t[fNpoints];
         Float_t *eylow  = new Float_t[fNpoints];
         Float_t *exhigh = new Float_t[fNpoints];
         Float_t *eyhigh = new Float_t[fNpoints];
         b.ReadFastArray(exlow,fNpoints);
         b.ReadFastArray(eylow,fNpoints);
         b.ReadFastArray(exhigh,fNpoints);
         b.ReadFastArray(eyhigh,fNpoints);
         for (Int_t i=0;i<fNpoints;i++) {
            fEXlow[i]  = exlow[i];
            fEYlow[i]  = eylow[i];
            fEXhigh[i] = exhigh[i];
            fEYhigh[i] = eyhigh[i];
         }
         delete [] eylow;
         delete [] exlow;
         delete [] eyhigh;
         delete [] exhigh;
      } else {
         b.ReadFastArray(fEXlow,fNpoints);
         b.ReadFastArray(fEYlow,fNpoints);
         b.ReadFastArray(fEXhigh,fNpoints);
         b.ReadFastArray(fEYhigh,fNpoints);
      }
      b.CheckByteCount(R__s, R__c, TGraphAsymmErrors::IsA());
      //====end of old versions
      
   } else {
      TGraphAsymmErrors::Class()->WriteBuffer(b,this);
   }
}
