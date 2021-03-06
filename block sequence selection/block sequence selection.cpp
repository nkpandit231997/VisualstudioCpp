// block sequence selection.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <vector>
#include "Block.h"
#include <sstream>
#include <string>

using namespace std;
using namespace cv;

int total_blocks = 12;

int total_color = 6;
char seq[6][10] = {"Blue","Yellow","DarkBlue","Red","Orange","Green"};

int total_seq_str = 3;
char seq_str[3][10] = { "Blue","Yellow","DarkBlue" };

int seq_mat[3][8][8][2] = { {
	{ { 0,0 },{ 0,0 },{ 0,0 },{ 0,0 },{ 0,0 },{ 0,0 },{ 0,0 },{ 0,0 } },
	{ { 0,0 },{ 0,0 },{ 0,0 },{ 0,0 },{ 0,0 },{ 0,0 },{ 0,0 },{ 0,0 } },
	{ { 10,2 },{ 10,2 },{ 11,1 },{ 11,1 },{ 11,1 },{ 11,1 },{ 12,2 },{ 12,2 } },
	{ { 10,2 },{ 10,2 },{ 8,6 },{ 8,6 },{ 9,4 },{ 9,4 },{ 12,2 },{ 12,2 } },
	{ { 1,1 },{ 7,6 },{ 7,6 },{ 8,6 },{ 8,6 },{ 9,4 },{ 9,4 },{ 6,5 } },
	{ { 1,1 },{ 2,3 },{ 7,6 },{ 7,6 },{ 5,5 },{ 6,5 },{ 6,5 },{ 6,5 } },
	{ { 1,1 },{ 2,3 },{ 3,4 },{ 3,4 },{ 5,5 },{ 5,5 },{ 5,5 },{ 4,3 } },
	{ { 1,1 },{ 2,3 },{ 2,3 },{ 3,4 },{ 3,4 },{ 4,3 },{ 4,3 },{ 4,3 } } },
	{
	{ { 0,0 },{ 0,0 },{ 0,0 },{ 0,0 },{ 0,0 },{ 0,0 },{ 0,0 },{ 0,0 } },
	{ { 0,0 },{ 0,0 },{ 0,0 },{ 0,0 },{ 0,0 },{ 0,0 },{ 0,0 },{ 0,0 } },
	{ { 10,4 },{ 10,4 },{ 12,1 },{ 12,1 },{ 12,1 },{ 12,1 },{ 11,6 },{ 11,6 } },
	{ { 5,5 },{ 10,4 },{ 10,4 },{ 9,2 },{ 9,2 },{ 11,6 },{ 11,6 },{ 7,3 } },
	{ { 5,5 },{ 6,4 },{ 6,4 },{ 9,2 },{ 9,2 },{ 8,6 },{ 8,6 },{ 7,3 } },
	{ { 5,5 },{ 5,5 },{ 6,4 },{ 6,4 },{ 8,6 },{ 8,6 },{ 7,3 },{ 7,3 } },
	{ { 1,2 },{ 1,2 },{ 2,5 },{ 4,1 },{ 4,1 },{ 4,1 },{ 4,1 },{ 3,3 } },
	{ { 1,2 },{ 1,2 },{ 2,5 },{ 2,5 },{ 2,5 },{ 3,3 },{ 3,3 },{ 3,3 } } },
	{
	{ { 0,0 },{ 0,0 },{ 0,0 },{ 0,0 },{ 0,0 },{ 0,0 },{ 0,0 },{ 0,0 } },
	{ { 0,0 },{ 0,0 },{ 0,0 },{ 0,0 },{ 0,0 },{ 0,0 },{ 0,0 },{ 0,0 } },
	{ { 9,5 },{ 12,1 },{ 12,1 },{ 12,1 },{ 12,1 },{ 11,3 },{ 10,2 },{ 10,2 } },
	{ { 9,5 },{ 9,5 },{ 9,5 },{ 11,3 },{ 11,3 },{ 11,3 },{ 10,2 },{ 10,2 } },
	{ { 5,4 },{ 5,4 },{ 8,1 },{ 8,1 },{ 8,1 },{ 8,1 },{ 6,6 },{ 6,6 } },
	{ { 1,3 },{ 5,4 },{ 5,4 },{ 7,2 },{ 7,2 },{ 6,6},{ 6,6 },{ 3,5 } },
	{ { 1,3 },{ 2,4 },{ 2,4 },{ 7,2 },{ 7,2 },{ 4,6 },{ 4,6 },{ 3,5 } },
	{ { 1,3 },{ 1,3 },{ 2,4 },{ 2,4 },{ 4,6 },{ 4,6 },{ 3,5 },{ 3,5 } } } };

//**********************************************************************************
//      OPENCV     //

Mat img;
Mat hsv;
Block block[6];

int MIN_OBJECT_AREA = 15 * 15;
int MAX_OBJECT_AREA = 304800;

void setvalues()
{
	block[0].setname("Blue");
	block[0].setHSVmin(Scalar(92, 104, 95));
	block[0].setHSVmax(Scalar(106, 155, 130));
	block[0].setcolor(Scalar(255, 0, 0));
	//yello
	block[1].setname("Yellow");
	block[1].setHSVmin(Scalar(25, 190, 115));
	block[1].setHSVmax(Scalar(39, 242, 158));
	block[1].setcolor(Scalar(0, 255, 255));
	//darkblue
	block[2].setname("DarkBlue");
	block[2].setHSVmin(Scalar(98, 112, 52));
	block[2].setHSVmax(Scalar(128, 196, 83));
	block[2].setcolor(Scalar(139, 0, 0));
	//red
	block[3].setname("Red");
	block[3].setHSVmin(Scalar(0, 169, 90));
	block[3].setHSVmax(Scalar(9, 225, 125));
	block[3].setcolor(Scalar(0, 0, 255));
	//orange
	block[4].setname("Orange");
	block[4].setHSVmin(Scalar(7, 183, 121));
	block[4].setHSVmax(Scalar(18, 230, 140));
	block[4].setcolor(Scalar(0, 165, 255));
	//green
	block[5].setname("Green");
	block[5].setHSVmin(Scalar(37, 176, 102));
	block[5].setHSVmax(Scalar(54, 237, 136));
	block[5].setcolor(Scalar(0, 255, 0));
}
VideoCapture capture(-1);
Block found_block;
int track(int index)
{
	
	namedWindow("Controls");
	setvalues();
	cout << "search  " << block[index].getname()<<"\n";
	int i = 0;
	while (i++<10) {
		capture.read(img);
		//imshow("img", img);
		Rect cropped = Rect(160, 120, 320, 240);
		img = img(cropped);
		pyrUp(img, img, Size(img.cols * 2, img.rows * 2));
		waitKey(1);
	}
	cvtColor(img, img, COLOR_BGR2HSV);
	inRange(img, block[index].getHSVmin(), block[index].getHSVmax(), hsv);
	imshow("hsv", hsv);
	Mat erodeElement = getStructuringElement(MORPH_RECT, Size(3, 3));
	Mat dilateElement = getStructuringElement(MORPH_RECT, Size(8, 8));
	erode(hsv, hsv, erodeElement);
	erode(hsv, hsv, erodeElement);
	dilate(hsv, hsv, dilateElement);
	dilate(hsv, hsv, dilateElement);
	vector< vector<Point> > contours;
	vector<Vec4i> hierarchy;
	int x=0, y=0;
	double largest_countour = 0;
	findContours(hsv, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);
	if (hierarchy.size() > 0)
	{
		int numObjects = hierarchy.size();
		for (int i = 0; i >= 0; i = hierarchy[i][0])
		{
			Moments moment = moments((cv::Mat)contours[i]);
			double area = contourArea(contours[i]);
			if (area > largest_countour)
			{
				x = (moment.m10 / area);
				y = (moment.m01 / area);
			}
		}
		//cout << "\n"<< x<< "   " << y;
		circle(img, Point(x, y), 5, Scalar(255, 0, 0), 2);
		//imshow("img", img);
	}
	if (x == 0 || y == 0)
		return 1;
	else
		return 0;
}


//**********************************************************************************



int main()
{
	int x;
	char got[10];
	//while (1)track(0);
	//cout << "Enter the First Block : ";
	//cin >> got;
	int seq_index=-1;
	for (int i = 0; i < 6; i++)
	{
		//if (track(i) == 0)
		//{
		//	seq_index = i;
		//	break;
		//}
		if (track(i) == 0)
		{
			cout << "Found Color : " << seq[i] << "   " << track(i) << "\n";
			seq_index = i;
			break;
		}
		else
			cout << "Not Found   : " << seq[i] <<"   "<< track(i) << "\n";
	}
	
	//cin >> x;
	if (seq_index == -1)
	{
		cin >> x;
		return 0;
	}
	cout << "Found color : " << seq[seq_index];
	for (int i = 0; i < total_seq_str; i++)
	{
		if (strcmp(got, seq_str[i]) == 0)
		{
			seq_index = i;
		}
	}
	cout << "Found at Seq Index : " << seq_index;
	cout << "\n";
	
	int found;

	for (int i = 1; i < total_blocks; i++)
	{
		found = 0;
		for (int j = 0; j < 8 && found == 0; j++)
		{
			for (int k = 0; k < 8 && found == 0; k++)
			{
				if (seq_mat[seq_index][j][k][0] == i+1)
				{
					cout << i + 1 << " ";
					cout << seq[seq_mat[seq_index][j][k][1]-1];
					cout << "\n";
					found = 1;
					while (track(seq_mat[seq_index][j][k][1]-1) == 1);
				}

			}
		}
	}

	for (int j = 0; j < 8; j++)
	{
		for (int k = 0; k < 8; k++)
		{
			if (seq_mat[seq_index][j][k][0] == 0)
				printf(" ------ ");
			else
				printf(" %6s ", seq[seq_mat[seq_index][j][k][1]-1]);
		}cout << "\n";
	}

	
	cout << "\n";
	cin >> x;
    return 0;
}

