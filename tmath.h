#ifndef TMATH_H
#define TMATH_H

#include <QList>
#include <vector>
#include <QString>
#include <QtMath>
#include <cmath>
#include <eigen3/Eigen/Dense> // Requiring system level Eigen installation i.e. sudo apt install libeigen3-dev  
using namespace Eigen;
namespace MATH{

bool populateMAT(std::vector<ArrayXXf> &dataArr, QString path);

void generateLookTable(std::vector<ArrayXXf> &arr,
                       float speed, float pitch,
                       float offsetX, float offsetY, float resolution);
void TFM(std::vector<ArrayXXf> &src,
         ArrayXXf &dest,
         std::vector<ArrayXXf> &lookUpTable, float fs);

}

#endif // TMATH_H


