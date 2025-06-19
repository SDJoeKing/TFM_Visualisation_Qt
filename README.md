# TFM_Visualisation_Qt
A simple QT C++ demo of TFM visualisation using Full Matrix Capturing datasets

## Introduction
This repository aims to validate the Total Focusing Method (TFM), an advanced visualisation method for generating high-resolution Ultrasonic Testing (UT) images in Non-destructive Testing (NDT). The data used for TFM imaging is captured using Full Matrix Capturing (FMC) method. For instance, in a simple scenario where a UT linear array probe that has 16 tx/rx channels, FMC will employ the following acquisition sequence:
1. Chan.1 fires, Chan.2 - Chan.16 receive;
2. Chan,2 fires, Chan1 and Chan.3 - Chan.16 receive;
3. Repeat above until Chan.16 fires, and Chan.1 - Chan.15 receive;
4. FMC therefore renders a matrix data of $16\times16\times$No.samples .
   
A good source to further information regarding TFM/FMC can be found [here](https://www.ndt.net/article/ecndt2023/presentation/ECNDT2023_PRESENTATION_390.pdf).
