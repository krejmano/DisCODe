/*
 * GobanMarkers.hpp
 * created on 21.01.11
 * author: kaji
 */

#ifndef GOBANMARKERS_HPP_
#define GOBANMARKERS_HPP_

#include <cv.h>

#include "Object3D.hpp"

namespace Types {

namespace Objects3D {

class GobanMarkers :public Object3D
{

public:
	GobanMarkers(cv::Size size) :
		size(size)
				{
				}


	GobanMarkers(const GobanMarkers& obj) :
		Object3D(obj),
		size(obj.size)
				{
				}


	virtual ~GobanMarkers()
				{
				}

	virtual GobanMarkers* clone()
		{
			return new GobanMarkers(*this);
		}

	virtual void draw(cv::Mat& image, CvScalar color, int offsetX = 0, int offsetY = 0)
		{
			cv::Mat keypoints(imagePoints);
			cv::drawChessboardCorners(image, size, keypoints, true);

		}

private:
	const cv::Size size;


};

} // namespace Objects3D

} // namespace Types


#endif /* GOBANMARKERS_HPP_ */
