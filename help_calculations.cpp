#include "help_calculations.h"

double GetRadians(double degrees)
{
    return degrees * M_PI / 180;
}

double CalculateDistance(TPoint start, TPoint finish)
{
    static const double EARTH_RADIUD = 6371000;

    double difLattitude = abs(finish.Lattitude  - start.Lattitude);
    double difLongitude = abs(finish.Longitude  - start.Longitude);

    return EARTH_RADIUD * 2 * asin(sqrt(sin(difLattitude / 2) * sin(difLattitude / 2) +
                                        sin(difLongitude / 2) * sin(difLongitude / 2) *
                                        cos(start.Lattitude) * cos(finish.Lattitude)));
}