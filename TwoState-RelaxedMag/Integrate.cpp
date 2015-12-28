//
//  Integrate.cpp
//  TwoState-RelaxedMag
//
//  Created by mekena McGrew on 12/22/15.
//  Copyright © 2015 Mekena Metcalf. All rights reserved.
//

#include <stdio.h>
#include "Integrate_Params.h"

double fup (double t, void * params)
{
    struct Integrate_params *p = (struct Integrate_params*) params;
    double w = p -> w;
    double Tf = p -> Tf;
    double tau = p -> tau;
    
    double f = (1./tau)*(exp(-(Tf-t)/tau))*exp(-sin(w*t))/(2*cosh(sin(w*t)));
    return f;
}

double fdn (double t, void * params)
{
    struct Integrate_params *p = (struct Integrate_params*) params;
    double w = p -> w;
    double Tf = p -> Tf;
    double tau = p -> tau;
    
    double f = (1./tau)*(exp(-(Tf-t)/tau))*exp(sin(w*t))/(2*cosh(sin(w*t)));
    return f;
}
