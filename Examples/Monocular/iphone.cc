/**
* This file is part of ORB-SLAM3
*
* Copyright (C) 2017-2021 Carlos Campos, Richard Elvira, Juan J. Gómez Rodríguez, José M.M. Montiel and Juan D. Tardós, University of Zaragoza.
* Copyright (C) 2014-2016 Raúl Mur-Artal, José M.M. Montiel and Juan D. Tardós, University of Zaragoza.
*
* ORB-SLAM3 is free software: you can redistribute it and/or modify it under the terms of the GNU General Public
* License as published by the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* ORB-SLAM3 is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
* the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License along with ORB-SLAM3.
* If not, see <http://www.gnu.org/licenses/>.
*/

#include <signal.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <chrono>
#include <ctime>
#include <sstream>

#include <condition_variable>

#include <opencv2/core/core.hpp>

#include <librealsense2/rs.hpp>
#include "librealsense2/rsutil.h"

#include <System.h>

using namespace std;

int main(int argc, char **argv)
{
string vocabPath = "ORBvoc.txt";
string settingsPath = "iphone.yaml";
if (argc == 1)
{

}
else if (argc == 2)
{
	vocabPath = argv[1];
}
else if (argc == 3)
{
	vocabPath = argv[1];
	settingsPath = argv[2];
}
else
{
    cerr << endl << "Usage: mono_webcam.exe path_to_vocabulary path_to_settings" << endl;
    return 1;
}

// Create SLAM system. It initializes all system threads and gets ready to process frames.
ORB_SLAM3::System SLAM(vocabPath, settingsPath,ORB_SLAM3::System::MONOCULAR,true);

cout << endl << "-------" << endl;
cout << "Start processing sequence ..." << endl;

cv::VideoCapture cap(0);


// From http://stackoverflow.com/questions/19555121/how-to-get-current-timestamp-in-milliseconds-since-1970-just-the-way-java-gets
int64_t now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();


// Main loop
cv::Mat im;
cv::Mat Tcw;
while (true)
{
	cap.read(im);

	if (im.empty())
		continue;

	int64_t curNow = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

	// Pass the image to the SLAM system
	Tcw = SLAM.TrackMonocular(im, curNow / 1000.0,'Sophus::SE3f');

	/* This can write each image with its position to a file if you want
	if (!Tcw.empty())
	{
		cv::Mat Rwc = Tcw.rowRange(0, 3).colRange(0, 3).t();
		cv::Mat twc = -Rwc*Tcw.rowRange(0, 3).col(3);
		std::ostringstream stream;
		//stream << "imgs/" << Rwc.at<float>(0, 0) << " " << Rwc.at<float>(0, 1) << " " << Rwc.at<float>(0, 2) << " " << twc.at<float>(0) << " " <<
		//	Rwc.at<float>(1, 0) << " " << Rwc.at<float>(1, 1) << " " << Rwc.at<float>(1, 2) << " " << twc.at<float>(1) << " " <<
			//Rwc.at<float>(2, 0) << " " << Rwc.at<float>(2, 1) << " " << Rwc.at<float>(2, 2) << " " << twc.at<float>(2) << ".jpg";
		stream << "imgs/" << curNow << ".jpg";
		string fileName = stream.str();
		cv::imwrite(fileName, im);
	}
	*/

	// This will make a third window with the color images, you need to click on this then press any key to quit
	cv::imshow("Image", im);


	if (cv::waitKey(1) >= 0)
		break;
}

// Stop all threads
SLAM.Shutdown();
cap.release();

// Save camera trajectory
SLAM.SaveKeyFrameTrajectoryTUM("KeyFrameTrajectory.txt");

return 0;
}