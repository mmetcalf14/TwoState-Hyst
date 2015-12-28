//
//  Integrate_Params.h
//  TwoState-RelaxedMag
//
//  Created by mekena McGrew on 12/22/15.
//  Copyright © 2015 Mekena Metcalf. All rights reserved.
//

#include <cmath>
#ifndef Integrate_Params_h
#define Integrate_Params_h

struct Integrate_params
{
    
    double Tf, tau, w;//Initial conditions to solve function
};

double fup (double t, void * params);
double fdn (double t, void * params);

#endif /* Integrate_Params_h */
