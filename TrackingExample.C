#include <iostream>
#include <vector>
#include "MDMTrace.h"
#include "MDMTraceFit.h"
#include <Math/Minimizer.h>
#include <Math/Factory.h>
#include <Math/Functor.h>

int main(int argc, char **argv)
{

    // initialize MDMTraceFit
    double mdmAngle = 35.3; // [deg]
    double mdmDipoleProbe = 2365;
    double mdmMultipoleProbe = 444;
    double scatteredMass = 12.;
    double scatteredCharge = 5.;
    MDMTraceFit *fcn = new MDMTraceFit(mdmAngle, mdmDipoleProbe, mdmMultipoleProbe, scatteredMass, scatteredCharge);
    fcn->SetPPAClength(42); // distance between 2 PPACs [cm]

    // set data for each event. [cm]
    double X1 = 1;
    double Y1 = 1;
    double X2 = 1;
    double Y2 = 1;
    std::vector<double> data = {X1, Y1, X2, Y2};
    fcn->SetData(data);

    // set minimizer and algorithm
    std::string minName = "Minuit2";
    std::string algoName = "Simplex";
    ROOT::Math::Minimizer *min = ROOT::Math::Factory::CreateMinimizer(minName, algoName);
    // set maximun function calls and tolerance
    min->SetMaxFunctionCalls(1000);
    min->SetTolerance(0.001);

    // set print info. 0 prints nothing, 1 prints something useful for debug
    min->SetPrintLevel(1);

    // convert MDMTraceFit to a ROOT functor with 3 parameters
    // set initial minimization parameters value
    // has to be in order: 0-scatterEnergy [MeV], 1-scatterAngleX [deg], 2-scatterAngleY [deg]
    ROOT::Math::Functor f(*fcn, 3);
    min->SetFunction(f);
    min->SetVariable(0, "scatterEnergy", 15.0, 0.1);
    min->SetVariable(1, "scatterAngleX", 35.3, 0.1);
    min->SetVariable(2, "scatterAngleY", 0.0, 0.1);
    // set minimization range, usually no need
    // SetLimitedVariable(index, name, initial value, step, lower limit, upper limit)
    // min->SetLimitedVariable(1,"scatterAngleX",35.3, 0.1, 33.3, 37.3);
    min->Minimize();

    // get minimization result
    const double *xs = min->X();
    // check if chi-square > 1
    if (min->MinValue() > 1)
        return kFALSE;
    Double_t scatteringEnergy = xs[0];
    Double_t scatteringAngleX = xs[1];
    Double_t scatteringAngleY = xs[2];

    std::cout << "Fitted scatteringEnergy: " << scatteringEnergy << " [MeV]" << std::endl;
    std::cout << "Fitted scatteringAngleX: " << scatteringAngleX << " [deg]" << std::endl;
    std::cout << "Fitted scatteringAngleY: " << scatteringAngleY << " [deg]" << std::endl;

    delete min;

    return 0;
}