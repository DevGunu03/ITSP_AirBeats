#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>
using namespace std;
#include "irrlicht.h"
#include "quaternion.h"
#include "vector3d.h"
using namespace irr::core;

#define PI 3.141

int main()
{
  // gi - angular velocity along the ith axis
  // ti - translational acceleration along the ith axis
  double t, gx, gy, gz, tx, ty, tz;
  // store the previous measurements for kalman filtering
  double t_, gx_, gy_, gz_, tx_, ty_, tz_;

  // calibrate

  // tracking the orientation
  quaternion P;
  P = quaternion(1, 0, 0, 1);
  cout << P.W << " " << P.X << " " << P.Y << " " << P.Z << endl;

  quaternion M;
  quaternion N;
  // N is the inverse of M

  vector3d<irr::f32> V;

  fstream gyro;

  t = t_ = 0;
  int i = 0;
  double a, b;

  while(true)
  {
    // read the data
    gyro.open("readings.txt", ios::in);
    std::string tp;
    for(int j=0; j<=i; j++)
    {
      std::getline(gyro, tp);
    }
    cout << tp << endl;

    // converting the string numbers to doubles
    int start = 0;
    double readings[7];
    for(int k = start; k < tp.length(); k++)
    {
      int values = 0;
      // getting the integer part
      if(tp[k] == 32)
      {
          std::string num = tp.substr(start, k);
          a = stoi(num);
          for(int m = 0; m < num.length(); m++)
          {
            if(num[m] == 46)
            {
              std::string decimal = num.substr(m + 1, num.length() - 1);
              b = stoi(decimal);
              b /= pow(10, decimal.length());
            }
          }
          double val = a + b;
          readings[values] = val;
          values++;
          start = k + 2;
      }
    }

    t = readings[0];
    cout << t << endl;
    gx = readings[1];
    gy = readings[2];
    gz = readings[3];
    tx = readings[4];
    ty = readings[5];
    tz = readings[6];

    i++;
    gyro.close();

    // rotate position vector accordingly
    double dt = t - t_;
    cout << dt << " ";
    M = quaternion(gx*dt/2, gy*dt/2, gz*dt/2);
    N = M; N.makeInverse();
    cout << M.X << M.Y << M.Z << M.W << " " << N.X << N.Y << N.Z << N.W << " ";

    P = M*P*N;

    t_ = t;
    gx_ = gx;
    gy_ = gy;
    gz_ = gz;
    tx_ = tx;
    ty_ = ty;
    tz_ = tz;

    P.toEuler(V);
    cout << "/" << V.X << " " << V.Y << " " << V.Z << "/" << endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
}
