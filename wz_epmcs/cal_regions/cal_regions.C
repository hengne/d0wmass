#define cal_regions_C
#include "cal_regions.h"

////////////////////////////////////////////////////////////////////////////////
CAL_REGIONS::CAL_REGIONS()
{ init(NULL, 1, 1000000, 0);
}

CAL_REGIONS::CAL_REGIONS(int Ioption)
{ init(NULL, 1, 1000000, Ioption);
}

CAL_REGIONS::CAL_REGIONS(const char *runlumi_file, int FirstRun, int LastRun)
{ init(runlumi_file, FirstRun, LastRun, 0);
}

CAL_REGIONS::CAL_REGIONS(const char *runlumi_file, int FirstRun, int LastRun, int Ioption)
{ init(runlumi_file, FirstRun, LastRun, Ioption);
}

int CAL_REGIONS::random_run()
{ if (total_lumi > 0)
  { float randlumi = rand.Rndm() * total_lumi;  
    float lumi = 0;
    int run;
    map<int,float>::iterator i = runlumi.begin(); 
    while ((i != runlumi.end()) && (lumi < randlumi)) 
    { lumi+= (*i).second;
      run = (*i).first;
      i++;
    }
    return run;
  }
  else return -1;
}

float CAL_REGIONS::bad_lumi_frac(float eta, float phi)
{ if (total_lumi > 0)
  { vector<int> ibox;
    for (int i = 0; i < box_list.size(); i++)
      if (box_list[i].in_cell_box(eta,phi)) ibox.push_back(i);

    if (ibox.size() == 0) return 0;
    else if (ibox.size() == 1) return box_list[ibox[0]].lumi_frac;
    else  // boxes overlap
    { float lumi = 0;
      for (map<int,float>::iterator j = runlumi.begin(); j != runlumi.end(); j++)
      { int i = 0; bool in_range = false;
        while ((i < ibox.size()) && (!in_range))
        { if ( ((*j).first >= box_list[ibox[i]].firstrun) && 
               ((*j).first <= box_list[ibox[i]].lastrun) ) 
          { lumi+= (*j).second; 
            in_range = true;
          }
          i++;
        }
      }
      return lumi/total_lumi;
    }
  }
  else return -1;
}

bool CAL_REGIONS::in_region(float eta, float phi, int run)
{ bool in_list = false;
  for (int i = 0; i < box_list.size(); i++)
  { if (box_list[i].in_cell_box(eta,phi,run)) in_list = true;
  }
  return in_list;
}  

bool CAL_REGIONS::in_region(float eta, float phi)
{ bool in_list = false;
  for (int i = 0; i < box_list.size(); i++)
  { if (box_list[i].in_cell_box(eta,phi)) in_list = true;
  }
  return in_list;
}  

void CAL_REGIONS::draw(TCanvas *can)
{ can->cd();
  draw();
}

void CAL_REGIONS::draw()
{ for (int i = 0; i < box_list.size(); i++) box_list[i].draw();
}

void CAL_REGIONS::draw_numbers(TCanvas *can)
{ can->cd();
  draw_numbers();
}

void CAL_REGIONS::draw_numbers()
{ for (int i = 0; i < box_list.size(); i++) box_list[i].draw_number();
}

void CAL_REGIONS::draw_phi_proj(float phi1, float phi2, float eta, 
                                float y1, float y2, int run1, int run2)
{ if (run1 > run2) { int temp=run1; run1=run2; run2=temp; }
  if (phi1 > phi2) { float temp=phi1; phi1=phi2; phi2=temp; }
  TBox box;
  box.SetLineWidth(2);
  box.SetFillStyle(0);
  for (int i = 0; i < box_list.size(); i++)
  { if ((eta > box_list[i].eta_min) && (eta < box_list[i].eta_max) &&
        (run2 >= box_list[i].firstrun) && (run1 <= box_list[i].lastrun))
    { box.SetLineColor(box_list[i].color);
      float phi_min = box_list[i].phi_min;
      float phi_max = box_list[i].phi_max;
      if (phi1 > phi_min) phi_min = phi1;
      if (phi2 < phi_max) phi_max = phi2;
      if (phi_min < phi_max) box.DrawBox(phi_min, y1, phi_max, y2);
    }
  }
}

void CAL_REGIONS::draw_eta_proj(float eta1, float eta2, float phi, 
                                float y1, float y2, int run1, int run2)
{ if (run1 > run2) { int temp=run1; run1=run2; run2=temp; }
  if (eta1 > eta2) { float temp=eta1; eta1=eta2; eta2=temp; }
  TBox box;
  box.SetLineWidth(2);
  box.SetFillStyle(0);
  for (int i = 0; i < box_list.size(); i++)
  { if ((phi > box_list[i].phi_min) && (phi < box_list[i].phi_max) &&
        (run2 >= box_list[i].firstrun) && (run1 <= box_list[i].lastrun))
    { box.SetLineColor(box_list[i].color);
      float eta_min = box_list[i].eta_min;
      float eta_max = box_list[i].eta_max;
      if (eta1 > eta_min) eta_min = eta1;
      if (eta2 < eta_max) eta_max = eta2;
      if (eta_min < eta_max) box.DrawBox(eta_min, y1, eta_max, y2);
    }
  }
}

void CAL_REGIONS::init(const char *runlumi_file, int FirstRun, int LastRun, int Ioption)
{ firstrun = FirstRun; lastrun = LastRun;
  ioption = Ioption;
  total_lumi = -1;
  add_all_bad();

  if (runlumi_file != NULL)
  { int run; float lumi;
    FILE *file = fopen(runlumi_file,"r");
    if (file == NULL) printf("\nrunlumi file not found!!!\n\n"); 
    else
    { while (!feof(file))
      { fscanf(file, "%i %f", &run, &lumi);
        if ((run >= firstrun) && (run <= lastrun)) runlumi[run] = lumi;
      }

      total_lumi = 0;
      for (map<int,float>::iterator i = runlumi.begin(); i != runlumi.end(); i++)
      { total_lumi+= (*i).second; 
      }
    
      for (int i = 0; i < box_list.size(); i++)
      { float lumi = 0;
        for (map<int,float>::iterator j = runlumi.begin(); j != runlumi.end(); j++)
        { if ( ((*j).first >= box_list[i].firstrun) && 
               ((*j).first <= box_list[i].lastrun) ) 
            lumi+= (*j).second; 
        }
        box_list[i].lumi_frac = lumi/total_lumi;
      }
    
    }
    fclose(file);
  }

}

void CAL_REGIONS::add_cell_box(int ieta1, int ieta2, int iphi1, int iphi2,
                               int box_firstrun, int box_lastrun)
{ if ((box_firstrun <= lastrun) && (box_lastrun >= firstrun))
  { float eta_min, eta_max, phi_min, phi_max;
    if (ieta2 > ieta1)
    { eta_min = 0.1*ieta1 - deta; 
      eta_max = 0.1*ieta2 + deta;
    }
    else
    { eta_min = 0.1*ieta2 - deta;
      eta_max = 0.1*ieta1 + deta;
    }
    
    if (iphi2 > iphi1)
    { phi_min = 3.141592654/32*iphi1 - dphi;
      phi_max = 3.141592654/32*iphi2 + dphi;
    }
    else
    { phi_min = 3.141592654/32*iphi2 - dphi;
      phi_max = 3.141592654/32*iphi1 + dphi;
    }

    CAL_CELL_BOX c(eta_min, eta_max, phi_min, phi_max, color, box_firstrun, box_lastrun); 
    box_list.push_back(c);
  }
}

void CAL_REGIONS::add_tower2(int ieta, int iphi, bool tower3_bad,
                             int box_firstrun, int box_lastrun)
{ if ((box_firstrun <= lastrun) && (box_lastrun >= firstrun))
  { int ieta1, ieta2, iphi1, iphi2;
  
    if (ieta > 0) 
    { ieta1 = ieta - 2; ieta2 = ieta; 
      if (tower3_bad) { iphi1 = iphi - 2; iphi2 = iphi; }
      else { iphi1 = iphi -1; iphi2 = iphi; }
    }
    else
    { ieta1 = ieta; ieta2 = ieta + 2;
      if (tower3_bad) { iphi1 = iphi - 1; iphi2 = iphi + 1; }
      else { iphi1 = iphi - 1; iphi2 = iphi; }
    }
    add_cell_box(ieta1, ieta2, iphi1, iphi2, box_firstrun, box_lastrun);
  }
}

void CAL_REGIONS::add_all_tower2()
{ deta = 0.04; dphi = 0.04; color = 6;
  add_tower2(  2, 42, 0, 171604, 178274);
  add_tower2(  6, 32, 0, 171604, 178274);
  add_tower2(  6, 10, 0, 174478, 178274);
  add_tower2( 10,  2, 0, 171604, 178274);
  add_tower2( 10, 62, 0, 171604, 178274);
  add_tower2(  2, 58, 0, 171604, 178274);
  add_tower2(  6, 54, 0, 171604, 178274);
  add_tower2( -2, 51, 0, 171604, 178274);
  add_tower2( -2,  1, 0, 171604, 178274);
  add_tower2(-10,  5, 0, 171604, 178274);
  add_tower2(-14, 37, 0, 171604, 178308);
  add_tower2(-30, 43, 0, 171604, 178308);
  add_tower2(-14, 45, 0, 171604, 178308);
  add_tower2(-22, 25, 0, 171604, 178308);
  add_tower2( -4, 47, 1, 162004, 178308);
  add_tower2( 14, 50, 0, 171604, 178308);
  add_tower2(-24,  1, 0, 172661, 178308);
  add_tower2(-18,  7, 0, 171604, 178308);
  add_tower2(-22, 51, 0, 171604, 178308);
  add_tower2(-16, 53, 0, 171604, 178308);
  add_tower2(-32, 55, 0, 171604, 178308);
  add_tower2(-32, 57, 0, 171604, 178308);
  add_tower2(-20, 63, 0, 171604, 178308);
  add_tower2(-14, 55, 0, 171604, 178445);
  add_tower2(-22, 29, 0, 171604, 178445);
  add_tower2( -6, 41, 1, 172576, 178445);
  add_tower2(-28, 31, 0, 178369, 178445);
  add_tower2(-32, 15, 0, 178369, 178610);
  add_tower2(-18,  3, 0, 171604, 177318);
  add_tower2(-12, 41, 1, 177311, 177925);  
}

void CAL_REGIONS::add_all_cable_swap()
{ deta = 0.04; dphi = 0.04; color = 8;
 //signal cables swapped
  add_cell_box( 20, 22, 14, 16, 161973, 180956);
}

void CAL_REGIONS::add_all_crate9()
{ deta = 0.04; dphi = 0.04; color = 4;
  // crate 9 (energy sharing)
  add_cell_box(  8, 11, 10, 11, 171604, 175144);
  add_cell_box(  0, 11,  8,  9, 171604, 175144);
  add_cell_box( 12, 28, 30, 31, 171604, 175689);
  
  add_cell_box(-20,-32,  2,  3, 171604, 175689);
  add_cell_box(-12,-28,  8,  9, 171604, 175144);
  add_cell_box(-20,-32, 14, 15, 171604, 175689);
  add_cell_box( 20, 32, 29, 31, 171604, 175689);

}

void CAL_REGIONS::add_small_cb_boxes()
{ deta = 0.01; dphi = 0.01; color = 2;
  // use small boxes to remove as little as possible
  // large cb
  add_cell_box(-32,-29,  0, 16, 161973, 180956);
  add_cell_box(-29,-28,  3,  4, 161973, 180956);
  add_cell_box(-29,-28,  9, 10, 161973, 180956);
  add_cell_box(-29,-28, 13, 14, 161973, 180956);
  add_cell_box(-28,-27,  2,  3, 161973, 180956);
  add_cell_box(-28,-27,  4,  5, 161973, 180956);
  add_cell_box(-28,-27,  6,  7, 161973, 180956);
  add_cell_box(-28,-27,  8,  9, 161973, 180956);
  add_cell_box(-28,-27, 10, 11, 161973, 180956);
  add_cell_box(-28,-27, 12, 13, 161973, 180956);
  add_cell_box(-28,-27, 14, 15, 161973, 180956);
  add_cell_box(-27,-26,  5,  6, 161973, 180956);
  add_cell_box(-26,-25,  0,  1, 161973, 180956);
  add_cell_box(-26,-25,  2,  3, 161973, 180956);
  add_cell_box(-26,-25,  4,  5, 161973, 180956);
  add_cell_box(-26,-25,  8,  9, 161973, 180956);
  add_cell_box(-26,-25, 10, 11, 161973, 180956);
  add_cell_box(-26,-25, 12, 13, 161973, 180956);
  add_cell_box(-26,-25, 14, 15, 161973, 180956);
  add_cell_box(-25,-24,  5,  6, 161973, 180956);
  add_cell_box(-24,-23,  0,  1, 161973, 180956);
  add_cell_box(-24,-23,  2,  3, 161973, 180956);
  add_cell_box(-24,-23,  4,  5, 161973, 180956);
  add_cell_box(-24,-23,  6,  7, 161973, 180956);
  add_cell_box(-24,-23,  8,  9, 161973, 180956);
  add_cell_box(-24,-23, 10, 11, 161973, 180956);
  add_cell_box(-24,-23, 12, 13, 161973, 180956);
  add_cell_box(-24,-23, 14, 15, 161973, 180956);
  add_cell_box(-23,-22,  1,  2, 161973, 180956);
  add_cell_box(-23,-22,  3,  4, 161973, 180956);
  add_cell_box(-23,-22,  5,  6, 161973, 180956);
  add_cell_box(-22,-21,  0,  1, 161973, 180956);
  add_cell_box(-22,-21,  2,  3, 161973, 180956);
  add_cell_box(-22,-21,  4,  5, 161973, 180956);
  add_cell_box(-22,-21,  6,  7, 161973, 180956);
  add_cell_box(-22,-21,  8,  9, 161973, 180956);
  add_cell_box(-22,-21, 10, 11, 161973, 180956);
  add_cell_box(-22,-21, 12, 13, 161973, 180956);
  add_cell_box(-22,-21, 14, 15, 161973, 180956);
  add_cell_box(-21,-20,  3,  4, 161973, 180956);
  add_cell_box(-21,-20,  5,  6, 161973, 180956);
  add_cell_box(-21,-20,  7,  8, 161973, 180956);
  add_cell_box(-21,-20,  9, 10, 161973, 180956);
  add_cell_box(-20,-19,  0,  1, 161973, 180956);
  add_cell_box(-20,-19,  2,  3, 161973, 180956);
  add_cell_box(-20,-19,  4,  5, 161973, 180956);
  add_cell_box(-20,-19,  6,  7, 161973, 180956);
  add_cell_box(-20,-19,  8,  9, 161973, 180956);
  add_cell_box(-20,-19, 10, 11, 161973, 180956);
  add_cell_box(-20,-19, 12, 13, 161973, 180956);
  add_cell_box(-20,-19, 14, 15, 161973, 180956);
  add_cell_box(-19,-18,  1,  2, 161973, 180956);
  add_cell_box(-19,-18,  5,  6, 161973, 180956);
  add_cell_box(-19,-18,  9, 10, 161973, 180956);
  add_cell_box(-19,-18, 11, 12, 161973, 180956);
  add_cell_box(-19,-18, 15, 16, 161973, 180956);
  add_cell_box(-18,-17,  0,  1, 161973, 180956);
  add_cell_box(-18,-17,  4,  5, 161973, 180956);
  add_cell_box(-18,-17, 14, 15, 161973, 180956);
  add_cell_box(-17,-16,  1,  2, 161973, 180956);
  add_cell_box(-17,-16,  5,  6, 161973, 180956);
  add_cell_box(-17,-16, 15, 16, 161973, 180956);

  // 2nd cb
  add_cell_box(-26,-25, 40, 41, 161973, 180956);
  add_cell_box(-26,-25, 42, 43, 161973, 180956);
  add_cell_box(-25,-24, 41, 42, 161973, 180956);
  add_cell_box(-24,-23, 40, 41, 161973, 180956);
  add_cell_box(-24,-23, 42, 43, 161973, 180956);
  add_cell_box(-23,-22, 40, 42, 161973, 180956);
  add_cell_box(-22,-21, 40, 41, 161973, 180956);
  add_cell_box(-21,-20, 40, 42, 161973, 180956);
  add_cell_box(-20,-19, 40, 41, 161973, 180956);
  add_cell_box(-20,-19, 42, 43, 161973, 180956);

  // 3rd cb
  add_cell_box(-28,-27, 46, 47, 161973, 180956);
  add_cell_box(-27,-26, 46, 48, 161973, 180956);
  add_cell_box(-25,-24, 47, 48, 161973, 180956);
  add_cell_box(-24,-23, 46, 47, 161973, 180956);
  add_cell_box(-23,-22, 47, 48, 161973, 180956);
  add_cell_box(-22,-21, 46, 47, 161973, 180956);
  add_cell_box(-21,-20, 47, 48, 161973, 180956);

}

void CAL_REGIONS::add_large_cb_boxes()
{ deta = 0.01; dphi = 0.01; color = 2;
  // checkerboard
  add_cell_box(-32,-14,  0, 16, 161973, 180956);
  add_cell_box(-32,-19, 40, 43, 161973, 180956);
  add_cell_box(-32,-20, 46, 48, 161973, 180956);
}

// have low acceptance and/or emid efficiency, problem not tracked down
void CAL_REGIONS::add_all_unknown()
{ deta = 0.01; dphi = 0.01; color = 2;
  // unknown nEC
  add_cell_box(-30,-29, 44, 46, 174496, 180956);
  add_cell_box(-30,-29, 34, 38, 174496, 180956);
  add_cell_box(-29,-28, 36, 38, 174496, 180956); 
  add_cell_box(-26,-24, 62, 64, 170038, 178788);
  add_cell_box(-26,-25, 28, 30, 174496, 179761);
  add_cell_box(-26,-25, 34, 36, 174496, 180956);
  add_cell_box(-25,-24, 34, 36, 170038, 178788);
  add_cell_box(-25,-24, 60, 61, 174496, 180956);
  add_cell_box(-25,-24, 62, 64, 170038, 178788);
  add_cell_box(-25,-24, 62, 64, 170038, 178788);
  add_cell_box(-24,-23, 27, 29, 161973, 180956);
  add_cell_box(-24,-23, 34, 36, 161973, 180956);
  add_cell_box(-24,-23, 32, 40, 179762, 180956);
  add_cell_box(-23,-22, 62, 63, 161973, 168134);
  add_cell_box(-23,-22, 34, 36, 161973, 178788);
  add_cell_box(-23,-22, 28, 30, 170038, 178135);
  add_cell_box(-22,-20, 20, 22, 161973, 168134);
  add_cell_box(-22,-21, 36, 38, 174496, 175819);
  add_cell_box(-22,-21, 32, 36, 161973, 180956);
  add_cell_box(-21,-17, 48, 49, 161973, 174495);
  add_cell_box(-21,-20, 36, 38, 161973, 168134);
  add_cell_box(-20,-19, 36, 38, 161973, 168134);
  add_cell_box(-20,-19, 36, 38, 177008, 180956);
  add_cell_box(-18,-17, 42, 44, 161973, 168134);
  add_cell_box(-16,-14, 14, 16, 161973, 168134);
  add_cell_box(-16,-15, 40, 41, 161973, 179761);
  add_cell_box(-16,-14, 48, 50, 161973, 168134);
  
  // unknown nCC
  add_cell_box(-12,-11, 46, 49, 175820, 180956);
  add_cell_box(-12,-10, 16, 18, 161973, 168134);
  add_cell_box(-12,-10, 22, 24, 161973, 168134);
  add_cell_box(-12,-10, 44, 48, 161973, 168134);
  add_cell_box(-12,-10, 42, 44, 170038, 180956);
  add_cell_box(-12,-10, 54, 56, 170038, 180956);
  add_cell_box(-11,-10,  6,  7, 161973, 165775);
  add_cell_box(-11,-10,  6,  7, 174496, 180956);
  add_cell_box( -9, -8, 26, 27, 174496, 180956);
  add_cell_box( -9, -8, 26, 27, 161973, 165775);
  add_cell_box( -8, -6, 48, 50, 161973, 168134);
  add_cell_box( -8, -6, 12, 14, 174496, 180956);
  add_cell_box( -8, -7, 45, 46, 175820, 180956);
  add_cell_box( -6, -4, 62, 64, 161973, 168134);
  add_cell_box( -6, -4, 12, 14, 161973, 165775);
  add_cell_box( -5, -4, 24, 25, 161973, 180956);
  add_cell_box( -5, -4,  2,  3, 161973, 168134);
  add_cell_box( -4,  0, 16, 18, 161973, 168134);
  add_cell_box( -2,  0,  8, 10, 161973, 168134);
  add_cell_box( -2,  0, 28, 30, 161973, 168134);
  add_cell_box( -1,  0, 28, 29, 177008, 180956);
  add_cell_box( -1,  0,  0,  1, 178789, 180956);
  
  // unknown pCC
  add_cell_box(  0,  1, 37, 38, 170038, 180956);
  add_cell_box(  2,  4, 30, 32, 161973, 168134);
  add_cell_box(  2,  3, 59, 60, 161973, 180956);
  add_cell_box(  2,  3, 29, 30, 170038, 180956);
  add_cell_box(  2,  4, 48, 50, 175820, 180956);
  add_cell_box(  4,  5, 27, 28, 161973, 165775);
  add_cell_box(  4,  6, 48, 52, 161973, 168134);
  add_cell_box(  4,  6, 50, 52, 168135, 175819);
  add_cell_box(  4,  5, 27, 28, 176567, 180956);
  add_cell_box(  5,  6, 62, 63, 170038, 180956);
  add_cell_box(  6,  8, 32, 34, 161973, 168134);
  add_cell_box(  6,  8,  4,  6, 170038, 177007);
  add_cell_box(  7,  8,  2,  3, 161973, 180956);
  add_cell_box(  8, 12, 38, 40, 161973, 165775);
  add_cell_box(  8,  9, 51, 52, 161973, 180956);
  add_cell_box(  8,  9, 44, 46, 170038, 180956);
  add_cell_box(  9, 10, 44, 46, 161973, 180956);
  add_cell_box( 10, 12, 44, 46, 177008, 180956);
  add_cell_box( 10, 12, 18, 20, 161973, 168134);
  add_cell_box( 10, 12, 44, 48, 161973, 168134);
  add_cell_box( 10, 12, 40, 42, 178136, 180956);

  // unknown pEC
  add_cell_box( 14, 16, 54, 56, 161973, 180956);
  add_cell_box( 15, 16,  9, 10, 161973, 168134);
  add_cell_box( 16, 17,  8, 10, 161973, 165775);
  add_cell_box( 16, 18, 38, 40, 161973, 168134);
  add_cell_box( 16, 18, 60, 62, 161973, 168134);
  add_cell_box( 16, 17, 15, 16, 176567, 180956);
  add_cell_box( 16, 18, 40, 42, 170038, 180956);
  add_cell_box( 17, 20,  6, 10, 161973, 168134);
  add_cell_box( 18, 20,  5,  6, 161973, 180956);
  add_cell_box( 18, 19, 52, 54, 161973, 168134);
  add_cell_box( 19, 20, 52, 54, 161973, 180956);
  add_cell_box( 20, 22,  6,  8, 161973, 165775);
  add_cell_box( 21, 24, 60, 62, 161973, 165775);
  add_cell_box( 22, 24, 20, 22, 165776, 168134);
  add_cell_box( 22, 24, 16, 18, 170038, 174495);
  add_cell_box( 22, 24, 22, 24, 170038, 175819);
  add_cell_box( 22, 24, 32, 34, 170038, 178788);
  add_cell_box( 23, 24, 39, 40, 161973, 180956);
  add_cell_box( 24, 26,  2,  4, 174496, 178135);
  add_cell_box( 24, 28, 44, 46, 174496, 178135);
  add_cell_box( 24, 25, 61, 62, 174496, 180956);
  add_cell_box( 24, 25, 31, 32, 174496, 180956);
  add_cell_box( 24, 25, 17, 18, 174496, 180956);
  add_cell_box( 25, 26,  2,  4, 174496, 180956);
  add_cell_box( 26, 27, 13, 14, 174496, 180956);
  add_cell_box( 27, 28, 48, 49, 174496, 180956);
}

void CAL_REGIONS::add_hotcells()
{ deta = 0.01; dphi = 0.01; color = 2;
  add_cell_box(-11,-10, 47, 48, 175820, 180956);
  add_cell_box(  7,  9, 44, 45, 162006, 165775);
  add_cell_box( 10, 11, 41, 42, 168135, 174495); 
  add_cell_box( 10, 11, 41, 42, 177008, 178135); 
  add_cell_box( 17, 18, 54, 55, 175820, 179761); 
  add_cell_box( 23, 24, 33, 34, 162006, 165775); 
}

void CAL_REGIONS::add_module17()
{ deta = 0.01; dphi = 0.01; color = 2;
  // energy scale for module 17 CC is 8% lower than average
  add_cell_box( -13, 13, 32, 34, 161973, 180956);
}

void CAL_REGIONS::add_all_bad()
{ add_all_tower2();
  add_all_cable_swap();
  add_all_crate9();
  add_hotcells();
  if (ioption == 0) 
  { add_large_cb_boxes();
    add_all_unknown();
  }
  else if (ioption == 1) 
  { add_small_cb_boxes();
    add_all_unknown();
  }
  else if (ioption == 2) 
  { add_large_cb_boxes();
  }
  else if (ioption == 3) 
  { add_small_cb_boxes();
  }
  else if (ioption == 4)
  { add_large_cb_boxes();
    add_all_unknown();
    add_module17();
  }
}
  
////////////////////////////////////////////////////////////////////////////////
CAL_CELL_BOX::CAL_CELL_BOX(float eta1, float eta2, float phi1, float phi2, int Color,
                           int FirstRun, int LastRun)
{ if (eta1 > eta2) { eta_min = eta2; eta_max = eta1; }
  else { eta_min = eta1; eta_max = eta2; }
  if (phi1 > phi2) { phi_min = phi2; phi_max = phi1; }
  else { phi_min = phi1; phi_max = phi2; }
  firstrun = FirstRun; lastrun = LastRun;
  color = Color;
}

bool CAL_CELL_BOX::in_cell_box(float eta, float phi)
{ if (phi < phi_min) phi+= 2*3.141592654;
  if (phi > phi_max) phi-= 2*3.141592654;

  return ( (eta > eta_min) && (phi > phi_min) &&
           (eta < eta_max) && (phi < phi_max) );
  
}

bool CAL_CELL_BOX::in_cell_box(float eta, float phi, int run)
{ return in_cell_box(eta, phi) && 
         (run >= firstrun) && (run <= lastrun);
}

void CAL_CELL_BOX::draw()
{ TBox box;
  box.SetLineColor(color);
  box.SetLineWidth(2);
  box.SetFillStyle(0);
  box.DrawBox(eta_min, phi_min, eta_max, phi_max);
}

void CAL_CELL_BOX::draw_number()
{ TText text; char number[10];
  sprintf(number, "%i", color);
  text.SetTextSize(0.015);
  text.SetTextColor(color);
  text.DrawText( (eta_min + eta_max)/2 - 0.03,
                 (phi_min + phi_max)/2 - 0.04, number);
}
        
