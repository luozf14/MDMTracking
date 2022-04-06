#include "MDMTraceFit.h"
#include "MDMTrace.h"
#include <math.h>
#include <stdio.h>
#include <vector>

MDMTraceFit::MDMTraceFit(double mdmAng, double mdmDipoleProbe, double mdmMultipoleProbe, double scaMass, double scaCharge){
    fMDMTrace = new MDMTrace();
    fMDMTrace->SetMDMAngle(mdmAng);
    fMDMTrace->SetMDMProbe(mdmDipoleProbe, mdmMultipoleProbe);
    fMDMTrace->SetScatteredCharge(scaCharge);
    fMDMTrace->SetScatteredMass(scaMass);
}

double MDMTraceFit::operator()(const double* p) const {

    double afterTarget = p[0];
    double scatteredAngleX = p[1];
    double scatteredAngleY = p[2];

    fMDMTrace->SetScatteredEnergy(afterTarget);
    fMDMTrace->SetScatteredAngle(scatteredAngleX, scatteredAngleY);

    fMDMTrace->SendRay();

    double positionX,positionY,angleX,angleY;
    fMDMTrace->GetPositionAngleFirstWire(positionX,positionY,angleX,angleY);

    double x1 = positionX;
    double x2 = x1 + std::tan(angleX/180.*3.14159)*fPPAClength;
    double y1 = positionY;
    double y2 = y1 + std::tan(angleY/180.*3.14159)*fPPAClength;

    double chi2 = std::pow(x1-fData[0], 2) + std::pow(x2-fData[2], 2) + std::pow(y2-fData[3], 2) + std::pow(y1-fData[1], 2) ;
    return chi2;
}


void MDMTraceFit::SetData(std::vector<double> data)
{
    fData = data;
}

void MDMTraceFit::SetPPAClength(double length)
{
    fPPAClength = length;
}