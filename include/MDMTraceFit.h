#ifndef MDMTRACRFIT_H
#define MDMTRACRFIT_H

#include "MDMTrace.h"
#include <vector>
#include <map>

class MDMTraceFit
{
public:
    MDMTraceFit(double mdmAng, double mdmDipoleProbe, double mdmMultipoleProbe, double scaMass, double scaCharge);
    double operator()(const double* para) const;
    void SetData(std::vector<double> data);
    void SetPPAClength(double length);

private:
    std::vector<double> fData;
    MDMTrace* fMDMTrace;
    double fPPAClength;
};


#endif //MDMTRACRFIT_H
