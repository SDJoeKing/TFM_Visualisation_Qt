#include "tmath.h"
#include <QFile>
#include <csignal>
#include <qdebug.h>

namespace MATH{

void generateLookTable(std::vector<ArrayXXf> &arr, float speed, float pitch,
                       float offsetX, float offsetY, float resolution)
{
    int channel = arr.size();
    int height = arr[0].rows();
    int length = arr[1].cols();



    ArrayXXf xAxis(height, length);
    ArrayXXf yAxis(height, length);

    for(int r=0; r < height; r++)
    {
        xAxis.row(r) = Eigen::ArrayXf::LinSpaced(length, 0, (length-1)*resolution).transpose() + offsetX ;
    }


    for(int col=0; col < length; col++)
    {
        yAxis.col(col) = Eigen::ArrayXf::LinSpaced(height, 0, (height-1)*resolution) + offsetY ;
    }

    ArrayXf probe = ArrayXf::LinSpaced(channel, 0, pitch*(channel-1));
    for(int chan = 0; chan < channel; chan++)
    {
        // qDebug() << probe(chan);
        arr[chan] = ((xAxis - probe(chan)).square() + yAxis.square()).sqrt();
        arr[chan] /= (speed * 1000);
    }

}


void TFM(std::vector<ArrayXXf> &src, ArrayXXf &dest, std::vector<ArrayXXf> &lookUpTable, float fs)
{
    // src -> (128, 128, 10e3)
    // dest ->(height, length)
    // LUT  ->(128, height, length)

    int channel = lookUpTable.size();
    int samples = src[0].cols();

    for(int tx =0; tx < channel; tx++)
    {
        for(int rx = 0; rx < channel; rx++)
        {
            ArrayXXf tofl = (lookUpTable[tx] + lookUpTable[rx]) * fs;
            tofl = (tofl >= samples).select(0, tofl);
            ArrayXXf out = tofl.unaryExpr([&src, &tx, &rx](float  x){return float(src[tx](rx, int(x)));});
            dest += out;
        }
    }

    dest /= dest.maxCoeff();
}

bool populateMAT(std::vector<ArrayXXf> &dataArr, QString path)
{

    QFile file(path);
    int tx = dataArr.size();
    int rx = dataArr[0].rows();
    int sample = dataArr[1].cols();
    qDebug() << tx << rx << sample;
    if(file.open(QIODevice::ReadOnly))
    {

        int l = 0;
        int w = 0;
        int d = 0;
        int counter = 0;

        QByteArray input = file.readAll();

        float * arr = reinterpret_cast<float *>(input.data());

        for (int s = 0; s< sample*tx*rx; s++)
        {
            // auto arr = file.read(8).data();
            counter++;
            // int *data = reinterpret_cast<int *>(arr);

            dataArr[d](w, l) = arr[s];

            l++;

            if(l == sample)
            {
                l = 0;
                w++;
                if(w == rx)
                {
                    w = 0;
                    d++;
                }
            }
        }

        qDebug() << "D is :" << d;

        if(d!=tx)
        {

            qDebug() << "Read: " << counter;
            throw std::runtime_error("Incorrect data format, tx channel missing");
        }

        file.close();
        return 1;
    }
    return 0;
}

}
