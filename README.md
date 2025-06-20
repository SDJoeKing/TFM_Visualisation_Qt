# TFM_Visualisation_Qt
A simple QT C++ demo of TFM visualisation using Full Matrix Capturing datasets

## Introduction
This repository aims to validate the Total Focusing Method (TFM), an advanced visualisation method for generating high-resolution Ultrasonic Testing (UT) images in Non-destructive Testing (NDT). The calculation of TFM is intended for use within another GUI that handles real-time UT scans from a customised UT device. So the functions of this simple GUI might not be fully tested and optimised. 

The data used for TFM imaging is captured using Full Matrix Capturing (FMC) method. For instance, in a simple scenario where a UT linear array probe that has 16 tx/rx channels, FMC will employ the following acquisition sequence:
1. Chan.1 fires, Chan.2 - Chan.16 receive;
2. Chan,2 fires, Chan1 and Chan.3 - Chan.16 receive;
3. Repeat above until Chan.16 fires, and Chan.1 - Chan.15 receive;
4. FMC therefore renders a matrix data of $16\times16\times$ No.samples .
   
A good source to further information regarding TFM/FMC can be found [here](https://www.ndt.net/article/ecndt2023/presentation/ECNDT2023_PRESENTATION_390.pdf).

## Dependencies

 - The code was developed using Desktop Qt 6.8.0.
 - Develop OS: Ubuntu 22.04
 - Matrix/Array manipulation was achieved using [Eigen 3](https://eigen.tuxfamily.org/index.php?title=Main_Page), Version 3.4.0 (**NOT INCLUDED**).
 - The plotting was handled by [QCustomPlot](https://www.qcustomplot.com/documentation/index.html) library, Version 2.1.1. 
 - The FMC data used during development, validation and demonstration (**NOT INCLUDED**) is from researchers of University of Strathclyde. Special thanks:
    - Lack of fusion crack - Lardner, T. (Creator), Tant, K. M. M. (Contributor) (2015). FMC dataset. University of Strathclyde. FMC_2012_06_12_at_13_09(.mat), FMC_metadata1(.ods), readme_FMC_2012_06_12_at_13_09(.docx). 10.15129/a7da5071-0436-4913-8f0e-de78f5ebccd6  
    - Side drill hole data - Tant, K. M. M. (Creator) (10 Aug 2017). FMC dataset - 3mm side drilled hole 304ss MMA weld. University of Strathclyde. FMC_RR3_2_25MHz_3mmsdh(.mat), FMC_RR3_2_25MHz_3mmsdh_metadata(.xlsx). 10.15129/60b6a5b8-e78e-4742-8414-aaba9399a9c8
 - Both datasets mentioned above were pre-processed using Python to reformat to ***float32*** type.  
## Demonstration
 
 
   This is the GUI demo using dataset captured on part with side drilled holes. Details of this dataset can be found [here](https://pureportal.strath.ac.uk/en/datasets/fmc-dataset-3mm-side-drilled-hole-304ss-mma-weld). 
 
 
<img src="https://github.com/user-attachments/assets/27b4ebd0-568e-40b2-91c8-bd9253d78f96" alt="Side drilled holes TFM" width =600 height=400>. 
 
 
This is the GUI demo using dataset captured on part with lack of fusion flaw. Details of this dataset can be found [here](https://pureportal.strath.ac.uk/en/datasets/fmc-dataset).
 
<img src= https://github.com/user-attachments/assets/70651c13-4a80-4813-98d4-7bd4fe7d4c8c alt="Lack of Fusion fault TFM" width =600 height=400>

## Known issues
1. The inherent data formatting check has not been implemented. So at the moment, the correct TFM calculation relies on the correct user inputs for data channels and Ascan lengths. 
2. Not templated so it only works with float type data - should be an easy fix but it is not the main purpose of this repo.
3. Sometimes when click "Recalculate" the TFM array is not being replotted by QCustomPlot, even though array has been recalculated. 
4. There is no signal/slot to notify the GUI that the TFM calculation is done, so when dealing with very high resolution requirements, a large area of interest and many channels (e.g. 128 channels), the calculation might take time. Users might suspect the GUI is frozen and continuously click on "Recalculation", which could lead to an App crash.  

 
 

