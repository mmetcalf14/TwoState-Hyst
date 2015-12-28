//
//  main.cpp
//  TwoState-RelaxedMag
//
//  Created by mekena McGrew on 12/18/15.
//  Copyright © 2015 Mekena Metcalf. All rights reserved.
//

#include <iostream>

#include <fstream>
#include <gsl/gsl_integration.h>
#include "Integrate_Params.h"

void DistributionFunc(double * P, double * P2, int T, double it);
//double IntegrateBode(double * F, double T, int it, double dt, double t_r);
double HystArea(double * M, double dt, double T);

using namespace std;
int main(int argc, const char * argv[])
{
    //list of variables
    
    
    
    double t;//dtime
    double dt = .01;//t incriments
    double T_f = 1; //final time
    int T_tot = T_f/dt;
    int T_int = T_tot/4;
    cout << "Tint: " << T_int << endl;
    
    double pi = 3.141592653;
    double w = 2*pi;
    
    double tau = .1;//relaxation time
    
    
    
//    double * Prob_up = new double[T_tot];
//    double * Prob_dn = new double[T_tot];
    
    double * PR_up = new double[T_tot];
    double * PR_dn = new double[T_tot];
    
    double * M = new double[T_tot]; //Magnetization
    //double * B = new double[T_tot];
    
    ofstream fout;
    fout.open("TwoMagState_tau100_Tf100_122815_(TEST).dat");
    fout.precision(8);
    fout.setf(ios::fixed);
    fout.setf(ios::showpoint);
    
    T_f = 0;
    //DistributionFunc(Prob_up, Prob_dn, T_tot, dt);


    
    for(int i =0; i <= T_tot; i++)//dissipated fermi function
    {
        T_f = i*dt;
        struct Integrate_params params = {T_f, tau, w};
        double result_up, error_up;
        double result_dn, error_dn;
//        size_t neval_up;
//        size_t neval_dn;
        
        gsl_integration_workspace * work = gsl_integration_workspace_alloc (1000);
        gsl_function Fup;
        gsl_function Fdn;
        Fup.function = &fup;
        Fdn.function = &fdn;
        Fup.params = &params;
        Fdn.params = &params;
        
        gsl_integration_qag(&Fup, 0, T_f, 0, 1e-7, 1000, 5, work, &result_up, &error_up);//use qag
        gsl_integration_qag(&Fdn, 0, T_f, 0, 1e-7, 1000, 5, work, &result_dn, &error_dn);

//        if(i == (T_tot))
//        {
//            cout << PR_up[0] << " " << PR_dn[0] << endl;
//        }

        PR_up[i] = 0.5*exp(-(T_f/tau)) + result_up;

        PR_dn[i] = 0.5*exp(-(T_f/tau)) + result_dn;//on last iteration
        //the first  element are changed to incorrect values
        //after this line. Last element is changed to different value after ending loop
        //All numbers of output below are correct compared to Mathematica value
        
        
        gsl_integration_workspace_free (work);
        cout << PR_up[i] << " " << PR_dn[i] << endl;


    }
    
    //cout << PR_up[0] << " " << PR_dn[0] << endl;
    
    for(int m = 0; m <= T_tot; m++)
    {
       //cout << PR_up[m] << " " << PR_dn[m] << endl;
        M[m] = PR_up[m]-PR_dn[m];
    }
    
    
    
    for( int i = 0; i <= T_tot; i++)
    {
        t = i*dt;
        fout << sin(w*t) << " " << M[i] << endl;
       // cout << t <<" " << sin(2*pi*t) << " " << M[i] << endl;
    }
    
    fout.close();
    
    //cout << "Here is the area: " << HystArea(M, dt, T_tot) << endl;
    

    delete [] PR_up;
    delete [] PR_dn;
    delete [] M;

    
    return 0;
    
    
}




//void DistributionFunc(double * P, double * P2, int T, double it)
//{
//    double t = 0.;
//    double w = 2*3.14;
//    
//    for(int i = 0; i < T; i++)
//    {
//        
//        P[i] = exp(-sin(w*t))/(2*cosh(sin(w*t)));
//        P2[i] = exp(sin(w*t))/(2*cosh(sin(w*t)));
//        
//        t+=it;
//    }
//}

//
//double HystArea(double * M, double dt, double T)
//{
//    double area = 0;
//    double area1 = 0;
//    double area2 = 0;
//    
//    int Ts = T/8;
//    int Tf = (T/8)+(1/(4*dt));
//    
//    int Period = 1/(4*dt);
//    
//    cout << "Ts: " << Ts << " Tf: " << Tf << endl;
//    for(int i = Ts; i <= Tf; i++)
//    {
//        double t = 4*i*dt;
//      cout << "t: " << t << endl;
//        if( i < Ts/2)
//        {
//            area1 += 4*dt*M[i];
//        }
//        else
//        {
//          area2 += 4*dt*M[i];
//        }
//        
//    }
//    area = area1 - area2;
//    
////    for(int i = ((T/2)-1); i < (5*T)/2; i++)
////    {
////        double t = 4*i*dt;
////        cout << "t: " << t << endl;
////        if(i <= (3*T)/2)
////        {
////             area1 += 4*dt*M[i];
////            
////        }
////        else
////        {
////            area2 += 4*dt*M[i];
////            
////        }
////    }
////    
////    area = area1 - area2;
//    
//    return area;
//}










