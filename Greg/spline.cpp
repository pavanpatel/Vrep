#include <iostream>
#include "spline.h"

using namespace std;

Spline::Spline()
{
    clear();
}

void Spline::clear()
{
    nbPoints = 0;
}

double Spline::getXMax()
{
    if (nbPoints == 0) {
        return 0.0;
    }

    return points[nbPoints-1][0];
}

void Spline::addPoint(double x, double y)
{
    if (nbPoints < SPLINE_MAX_POINTS) {
        points[nbPoints][0] = x;
        points[nbPoints][1] = y;

        if (nbPoints > 0) {
            ds[nbPoints-1] = points[nbPoints][1] - points[nbPoints-1][1];
            ds[nbPoints-1] /= points[nbPoints][0] - points[nbPoints-1][0];
        }

        nbPoints++;
    }
}

double Spline::get(double x)
{
    int i;
    
    for (i=0; i<nbPoints; i++) {
        if (points[i][0] >= x) {
            break;
        }
    }

    if (i == 0) {
        return points[0][1];
    }

    if (i == nbPoints) {
        return points[nbPoints-1][1];
    }

    return points[i-1][1]+ds[i-1]*(x-points[i-1][0]);
}

double Spline::getMod(double x)
{
    double maxX = getXMax();

    if (x < 0.0 || x > maxX) {
        x -= maxX*(int)(x/maxX);
    }
    
    return get(x);
}


void Spline::print()
{
    int i;

    cout << "Spline:" << endl;
    for (i=0; i < nbPoints; i++) {
        cout << points[i][0];
        if (i != nbPoints-1) {
            cout << ";";
        }
    }
    cout << endl;
    for (i=0; i < nbPoints; i++) {
        cout << points[i][1];
        if (i != nbPoints-1) {
            cout << ";";
        }
    }
    cout << endl;
}
