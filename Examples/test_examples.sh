#!/bin/bash
pathDatasetEuroc='/home/mingxi/ws/final_proj_5554' #Example, it is necesary to change it by the dataset path

#------------------------------------
# Monocular Examples
#echo "Launching KITTI00 with Monocular iPhone"
#./Monocular/mono_kitti ../Vocabulary/ORBvoc.txt ./Monocular/iPhone.yaml "$pathDatasetEuroc"/my_data/house1_30Hz

#echo "Launching 10Hz outdoor dataset with Monocular iPhone"
#./Monocular/mono_kitti ../Vocabulary/ORBvoc.txt ./Monocular/iPhone.yaml "$pathDatasetEuroc"/my_data/outdoor_10Hz

#echo "Launching 30Hz outdoor dataset with Monocular iPhone"
#./Monocular/mono_kitti ../Vocabulary/ORBvoc.txt ./Monocular/iPhone.yaml "$pathDatasetEuroc"/my_data/outdoor_30Hz

#echo "Launching 2Hz outdoor dataset with Monocular iPhone"
#./Monocular/mono_kitti ../Vocabulary/ORBvoc.txt ./Monocular/iPhone.yaml "$pathDatasetEuroc"/my_data/outdoor_2Hz

#echo "Launching malden dataset with Monocular iPhone"
#./Monocular/mono_kitti ../Vocabulary/ORBvoc.txt ./Monocular/iPhone_1080.yaml "$pathDatasetEuroc"/my_data/malden_10Hz

#echo "Launching house2 with Monocular iPhone"
#./Monocular/mono_kitti ../Vocabulary/ORBvoc.txt ./Monocular/iPhone.yaml "$pathDatasetEuroc"/my_data/house2_30Hz

#echo "Launching 30Hz indoor dataset with Monocular iPhone"
#./Monocular/mono_kitti ../Vocabulary/ORBvoc.txt ./Monocular/iPhone.yaml "$pathDatasetEuroc"/my_data/house3_30Hz

echo "Launching 60Hz indoor dataset with Monocular iPhone"
./Monocular/mono_kitti ../Vocabulary/ORBvoc.txt ./Monocular/iPhone.yaml "$pathDatasetEuroc"/my_data/house3_60Hz
#echo "Launching MH01 with Monocular sensor"
#./Monocular/mono_kitti ../Vocabulary/ORBvoc.txt ./Monocular/KITTI00-02.yaml "$pathDatasetEuroc"/dataset_kitti/KITTI_odometry_gray/00

