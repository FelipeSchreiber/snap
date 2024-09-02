#include "stdafx.h"
#include "agm2.h"

int main(int argc, char* argv[]) {
  Env = TEnv(argc, argv, TNotify::StdNotify);
  Env.PrepArgs(TStr::Fmt("agmgen. build: %s, %s. Time: %s", __TIME__, __DATE__, TExeTm::GetCurTm()));
  TExeTm ExeTm;
  Try
  const TStr InFNm = Env.GetIfArgPrefixStr("-i:", "DEMO", "Community affiliation data");
  const TStr OutFPrx = Env.GetIfArgPrefixStr("-o:", "agm", "out file name prefix");
  const int RndSeed = Env.GetIfArgPrefixInt("-rs:", 10, "Seed for random number generation");
  const double DensityCoef= Env.GetIfArgPrefixFlt("-a:", 0.6, "Power-law Coefficient a of density (density ~ N^(-a)");
  const double ScaleCoef= Env.GetIfArgPrefixFlt("-c:", 1.3, "Scaling Coefficient c of density (density ~ c");
  const bool Draw = Env.GetIfArgPrefixBool("-d:", false, "Use GraphViz to draw the generated graph.");
  const TStr InProbs = Env.GetIfArgPrefixStr("-p:", "0.5,0.6,0.7", "Community probs data");
  const TStr InLambdas = Env.GetIfArgPrefixStr("-l:", "0.5,0.6,0.7", "Community lambda for exponential weights");
  const double PNoCom = Env.GetIfArgPrefixFlt("-pn:", 0.5, "prob of no communities");
  TStrV split_str;
  const char delim[] = ",";
  InProbs.SplitOnAllCh(*delim,split_str);
  TFltV CProbV;
  for (TVec<TStr>::TIter it = split_str.BegI(); it < split_str.EndI(); it++)
  {
    CProbV.Add(it->GetFlt());
  }

  InLambdas.SplitOnAllCh(*delim,split_str);
  TFltV CLambdasV;
  for (TVec<TStr>::TIter it = split_str.BegI(); it < split_str.EndI(); it++)
  {
    CLambdasV.Add(it->GetFlt());
  }

  TRnd Rnd(RndSeed);
  TVec<TIntV> CmtyVV;
  if(InFNm == "DEMO") {
    CmtyVV.Gen(2);
    TIntV NIdV;
    for(int i = 0; i < 25; i++) {
      TIntV& CmtyV = CmtyVV[0];
      CmtyV.Add(i + 1);
    }
    for(int i = 15; i < 40; i++) {
      TIntV& CmtyV = CmtyVV[1];
      CmtyV.Add(i+1);
    }
    printf("\nGenerate demo graph on 2 non-overlapping communities.\n");
  }
  else {
    int Membs = 0;
    TSsParser Ss(InFNm, ssfWhiteSep);
    while (Ss.Next()) {
      if(Ss.GetFlds() > 0) {
        TIntV CmtyV;
        for(int i = 0; i < Ss.GetFlds(); i++) {
          if (Ss.IsInt(i)) { CmtyV.Add(Ss.GetInt(i)); }
        }
        CmtyVV.Add(CmtyV);
        Membs += CmtyV.Len();
      }
    }
    printf("\nCommunity loading completed (%d communities, %d memberships)\n", CmtyVV.Len(), Membs);
  }
  // THash < TIntPr, TFlt > edges = TAGM::ModifiedGenAGM(CmtyVV,CProbV, CLambdasV, Rnd, PNoCom);
  THash < TIntPr, TFlt > edges = TAGM::ModifiedGenAGM(CmtyVV, DensityCoef, ScaleCoef, Rnd);
  FILE *F = fopen((OutFPrx + ".txt").CStr(), "wt");
  for (THash < TIntPr, TFlt >::TIter it = edges.BegI(); it < edges.EndI(); it++)
  {
    TFlt weight = Rnd.GetExpDev(CLambdasV[(int) it->Dat]);
    fprintf(F,"%d %d %f\n",it->Key.GetVal1(),it->Key.GetVal2(),weight);
  }
  fclose(F);
  Catch
  printf("\nrun time: %s (%s)\n", ExeTm.GetTmStr(), TSecTm::GetCurTm().GetTmStr().CStr());
  return 0;
}
