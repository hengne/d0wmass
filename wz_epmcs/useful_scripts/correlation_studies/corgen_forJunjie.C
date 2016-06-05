// To be able to generate random numbers that are correlated, generated according to a gaussian distribution

#include <iostream>
#include<fstream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>

#include <TROOT.h>
#include <TFile.h>
#include <TRandom3.h>
#include <TH1.h>
#include <TH2.h>
#include <TCanvas.h>

using namespace std;

TRandom3 *myrandom;

// These functions are declared here, I have used 2 or 4 or 6 dim matrices in the past
// So please modify it according to your dimensions !
// The second index needs to be specified exactly (did not like to be varied)

void corset(double aaa[][2], int dim, double bbb[][2]);
void corgen(double bbb[][2], int dim, double[]);

void corset(double aaa[][4], int dim, double bbb[][4]);
void corgen(double bbb[][4], int dim, double[]);

void corset(double aaa[][6], int dim, double bbb[][6]);
void corgen(double bbb[][6], int dim, double[]);

int main(int argc, char** argv)
{

  if(argc<4) {
    cout <<" Please run this in the following way: " << endl
	 << "./corgen <dimension of covariance matrix> <fitted value obtd. for ScaleA> <fitted value obtd. for ScaleB> <fitted value obtd. for SamplA> <fitted value obtd. for alpha_mb> " << endl << endl;
    cout << "For e.g. ./corgen 0.9462 1.2904 1.1155 0.5654 " << endl;


    return 1;
  }

  const int dim = atoi(argv[1]);

  // Please define your variables here according to the value of your dimension.
  double fitted_scaleA = atof(argv[2]);
  double fitted_scaleB = atof(argv[3]);
  double fitted_samplA = atof(argv[4]);
  double fitted_alphamb = atof(argv[5]);
  double fitted_alpha = atof(argv[6]);
  double fitted_beta = atof(argv[7]);


  // Modify and print this out if you want to verify that the assigning was okay !
  //  cout << "alpha " << fitted_alpha << " beta " << fitted_beta << " scaleA " << fitted_scaleA << " scaleB " << fitted_scaleB << " samplA " << fitted_samplA << " alphamb " << fitted_alphamb << endl;


  // Histograms incase you wanted to see what the generated distribution of each variable looked like
  TH1D *hist1 = new TH1D("hist1", "histogram 1", 100, -2.0, 2.0);
  TH1D *hist2 = new TH1D("hist2", "histogram 2", 100, -2.0, 2.5);
  TH1D *hist3 = new TH1D("hist3", "histogram 3", 100, -2.0, 2.0);
  TH1D *hist4 = new TH1D("hist4", "histogram 4", 100, -2.0, 2.0);
  TH2D *hist5 = new TH2D("hist5", "histogram 5", 100, -2.0, 2.0, 100, -2.0, 2.0);
  TH2D *hist6 = new TH2D("hist6", "histogram 6", 100, -2.0, 2.0, 100, -2.0, 2.0);


  // JO is entering a 6x6 covariance matrix for electron corr and recoil corr. 
  // As evident Electron and Recoil are NOT correlated here !
  
  double cov_matrix[dim][dim] = {{1.849e-05, -8.97376e-04, 0, 0, 0, 0},
				 {-8.97376e-04, 4.3815e-02, 0, 0, 0, 0},
				 {0, 0, 1.165e-04, -7.827e-04, 2.179e-04, -2.218e-05},
				 {0, 0, -7.827e-04, 3.033e-02, 8.841e-04, -5.239e-03},
				 {0, 0, 2.179e-04, 8.841e-04, 4.004e-03, -3.203e-03},
				 {0, 0, -2.218e-05, -5.239e-03, -3.203e-03, 5.537e-03}}; 
  

  ///// Defining a 4x4 "square-root matrix"

  //  double matrix_sqrt[dim][dim] = {{0., 0., 0., 0.}, {0., 0., 0., 0.}, {0., 0., 0., 0.}, {0., 0., 0., 0.}};
  // Defining a 2x2 "square-root matrix"
  //  double matrix_sqrt[dim][dim] = {{0., 0.}, {0., 0.}};

  // Defining a 6x6 "square-root matrix"
  double matrix_sqrt[dim][dim] = {{0., 0., 0., 0., 0., 0.}, 
				  {0., 0., 0., 0., 0., 0.},
				  {0., 0., 0., 0., 0., 0.},
				  {0., 0., 0., 0., 0., 0.},
				  {0., 0., 0., 0., 0., 0.},
				  {0., 0., 0., 0., 0., 0.}};


  ///// Defining an array for the required set of numbers

  //  double reqdvector[dim] = {0., 0., 0., 0.};
  //  double reqdvector[dim] = {0., 0.};
  double reqdvector[dim] = {0., 0., 0., 0., 0., 0.};


  // Call CORSET and CORGEN - 
  // I called corgen many times in order to verify that the numbers are being generated properly
  corset(cov_matrix, dim, matrix_sqrt);

  myrandom = new TRandom3(513382473);
  fstream outfile("corrparameters_toys.txt", ios::out);

  // Change 300 to the number of times you want to call it
  for(int num=0; num<300; ++num) {
    corgen(matrix_sqrt, dim, reqdvector);

    // For debugging purposes
    /*
    for (int i=0; i<dim; i++) {
      cout << "reqdvector " << reqdvector[i] << endl;
      hist->Fill(reqdvector[i]);
    }
    */

    ///// Fill in the histograms with each call to corgen
    
    hist1->Fill(reqdvector[0] + fitted_scaleA);
    hist2->Fill(reqdvector[1] + fitted_scaleB);
    hist3->Fill(reqdvector[2] + fitted_samplA);
    hist4->Fill(reqdvector[3] + fitted_alphamb);
    hist5->Fill(reqdvector[0] + fitted_scaleA, reqdvector[1] + fitted_scaleB);
    hist6->Fill(reqdvector[2] + fitted_samplA, reqdvector[3] + fitted_alphamb);

    // Write out the generated values of the variables to the file
    outfile << (reqdvector[0]+fitted_alpha)<<" "<< (reqdvector[1]+fitted_beta) <<" "<< (reqdvector[2]+fitted_scaleA) <<" "<< (reqdvector[3]+fitted_scaleB) <<" "<< (reqdvector[4]+fitted_samplA) <<" "<< (reqdvector[5]+fitted_alphamb) << endl;

  }

  outfile.close();

  TFile *tf = new TFile("histo.root", "RECREATE");
  hist1->Write();
  hist2->Write();
  hist3->Write();
  hist4->Write();
  hist5->Write();
  hist6->Write();
  tf->Close();

  // For debugging purposes
  /*
  for (int j=0; j<dim; ++j) {
    for (int k=0; k<dim; ++k) {
      cout << "sqrt matrix " << matrix_sqrt[j][k] << endl;
    }
  }

// For debugging purposes
  for (int i=0; i<dim; i++) {
    cout << "vector "<< reqdvector[i] << endl;
  }
  */

  return 0;

}


// For 4 dimensions ******************
// CORSET sets up the generation by computing matrix "bbb[]" which is the square root of 
// covariance-matrix (aaa[])

void corset(double aaa[][4], int dim, double bbb[][4])
{
  
  for(int j=0; j<dim; ++j) {
    double CK = 0.;
    
    for(int k=0; k<j; ++k) {
      //      cout << "bbb & j and k " << j <<" "<< k <<" "<< bbb[j][k] << endl;

      CK = CK + bbb[j][k]*bbb[j][k];
      //      cout << "CK " << CK << endl;
    }

    // FOR THE DIAGONAL ELEMENTS OF SQRT_MATRIX
    bbb[j][j] = sqrt(abs(aaa[j][j] - CK));
    //    cout << "bbb_jj " << j <<" "<< bbb[j][j] << endl;
    
    for(int i=j+1; i<dim; ++i) {
      CK = 0.0;
     
      for(int k=0; k<j; ++k) {
	CK = CK + bbb[i][k]*bbb[j][k];
	//	cout << "product "  << i <<" "<< j <<" "<< k <<" "<< bbb[i][k] <<" "<< bbb[j][k] << endl;
	//	cout << "CK new " << CK << endl;
      }

      // FOR OFF_DIAGONAL ELEMENTS OF SQRT_MATRIX
      bbb[i][j] = (aaa[i][j] - CK)/bbb[j][j];
            cout << "bbb & i and j " << i << " "<< j <<" "<< aaa[i][j] <<" "<< bbb[i][j] << endl;
    }

  }

}


// CORGEN actually generates a set of random numbers (of dimension dim) distributed according to  
// a gaussian with covariance matrix aaa[] and mean values zero

void corgen(double bbb[][4], int dim, double xx[])
{

  //  srand( time( 0 ) );
  //  TRandom *random = new TRandom(719287);

  double numarray[dim];
  double number;
  for(int inum=0; inum<dim; inum++) {
    number = myrandom->Gaus(0.0, 1.0);
    numarray[inum] = number;
    //    cout << "numarray " << "dim " << inum <<" "<< numarray[inum] << endl;

  }

  for(int i=0; i<dim; ++i) {
    xx[i] = 0.0;
    for(int j=0; j<(i+1); ++j) {
      xx[i] = xx[i] + bbb[i][j]*numarray[j];
      //      cout << "product within " << i <<" "<< j <<" "<< bbb[i][j] <<" "<< numarray[j] <<" "<< xx[i] << endl;
    }

  }


}


// For 6 dimensions ***************
// CORSET sets up the generation by computing matrix "bbb[]" which is the square root of 
// covariance-matrix (aaa[])

void corset(double aaa[][6], int dim, double bbb[][6])
{
  
  for(int j=0; j<dim; ++j) {
    double CK = 0.;
    
    for(int k=0; k<j; ++k) {
      //      cout << "bbb & j and k " << j <<" "<< k <<" "<< bbb[j][k] << endl;

      CK = CK + bbb[j][k]*bbb[j][k];
      //      cout << "CK " << CK << endl;
    }

    // FOR THE DIAGONAL ELEMENTS OF SQRT_MATRIX
    bbb[j][j] = sqrt(abs(aaa[j][j] - CK));
    //    cout << "bbb_jj " << j <<" "<< bbb[j][j] << endl;
    
    for(int i=j+1; i<dim; ++i) {
      CK = 0.0;
     
      for(int k=0; k<j; ++k) {
	CK = CK + bbb[i][k]*bbb[j][k];
	//	cout << "product "  << i <<" "<< j <<" "<< k <<" "<< bbb[i][k] <<" "<< bbb[j][k] << endl;
	//	cout << "CK new " << CK << endl;
      }

      // FOR OFF_DIAGONAL ELEMENTS OF SQRT_MATRIX
      bbb[i][j] = (aaa[i][j] - CK)/bbb[j][j];
      //      cout << "bbb & i and j " << i << " "<< j <<" "<< aaa[i][j] <<" "<< bbb[i][j] << endl;
    }

  }

}


// CORGEN actually generates a set of random numbers (of dimension dim) distributed according to
// a gaussian with covariance matrix aaa[] and mean values zero

void corgen(double bbb[][6], int dim, double xx[])
{

  //  srand( time( 0 ) );
  //  TRandom *random = new TRandom(719287);

  double numarray[dim];
  double number;
  for(int inum=0; inum<dim; inum++) {
    number = myrandom->Gaus(0.0, 1.0);
    numarray[inum] = number;
    //    cout << "numarray " << "dim " << inum <<" "<< numarray[inum] << endl;

  }

  for(int i=0; i<dim; ++i) {
    xx[i] = 0.0;
    for(int j=0; j<(i+1); ++j) {
      xx[i] = xx[i] + bbb[i][j]*numarray[j];
      //      cout << "product within " << i <<" "<< j <<" "<< bbb[i][j] <<" "<< numarray[j] <<" "<< xx[i] << endl;
    }

  }


}

// For 2 dimensions *******************
// CORSET sets up the generation by computing matrix "bbb[]" which is the square root of 
// covariance-matrix (aaa[])

void corset(double aaa[][2], int dim, double bbb[][2])
{
  
  for(int j=0; j<dim; ++j) {
    double CK = 0.;
    
    for(int k=0; k<j; ++k) {
      //      cout << "bbb & j and k " << j <<" "<< k <<" "<< bbb[j][k] << endl;

      CK = CK + bbb[j][k]*bbb[j][k];
      //      cout << "CK " << CK << endl;
    }

    // FOR THE DIAGONAL ELEMENTS OF SQRT_MATRIX
    bbb[j][j] = sqrt(abs(aaa[j][j] - CK));
    //    cout << "bbb_jj " << j <<" "<< bbb[j][j] << endl;
    
    for(int i=j+1; i<dim; ++i) {
      CK = 0.0;
     
      for(int k=0; k<j; ++k) {
	CK = CK + bbb[i][k]*bbb[j][k];
	//	cout << "product "  << i <<" "<< j <<" "<< k <<" "<< bbb[i][k] <<" "<< bbb[j][k] << endl;
	//	cout << "CK new " << CK << endl;
      }

      // FOR OFF_DIAGONAL ELEMENTS OF SQRT_MATRIX
      bbb[i][j] = (aaa[i][j] - CK)/bbb[j][j];
            cout << "bbb & i and j " << i << " "<< j <<" "<< aaa[i][j] <<" "<< bbb[i][j] << endl;
    }

  }

}


// CORGEN actually generates a set of random numbers (of dimension dim) distributed according to
// a gaussian with covariance matrix aaa[] and mean values zero

void corgen(double bbb[][2], int dim, double xx[])
{

  //  srand( time( 0 ) );
  //  TRandom *random = new TRandom(719287);

  double numarray[dim];
  double number;
  for(int inum=0; inum<dim; inum++) {
    number = myrandom->Gaus(0.0, 1.0);
    numarray[inum] = number;
    //    cout << "numarray " << "dim " << inum <<" "<< numarray[inum] << endl;

  }

  for(int i=0; i<dim; ++i) {
    xx[i] = 0.0;
    for(int j=0; j<(i+1); ++j) {
      xx[i] = xx[i] + bbb[i][j]*numarray[j];
      //      cout << "product within " << i <<" "<< j <<" "<< bbb[i][j] <<" "<< numarray[j] <<" "<< xx[i] << endl;
    }

  }

}






