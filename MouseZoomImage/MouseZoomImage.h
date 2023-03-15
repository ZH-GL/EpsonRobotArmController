#pragma once

#include <QtWidgets/QMainWindow>
#include <opencv2/opencv.hpp>

#include "ui_MouseZoomImage.h"
#include "qevent.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MouseZoomImageClass; };
QT_END_NAMESPACE

class MouseZoomImage : public QMainWindow
{
    Q_OBJECT

public:
    MouseZoomImage(QWidget *parent = nullptr);
    ~MouseZoomImage();


protected:

	// 鼠标事件
	void wheelEvent(QWheelEvent * event);

private:
    Ui::MouseZoomImageClass *ui;

	int m_width;
	int m_height;
	/*double m_iscaled;*/
	QImage m_tempimage;
	cv::Mat m_Srcimage;
	cv::Mat m_image;
	bool m_bmove;
	QPoint m_translate;
	QPoint m_ImagePos;
	// 当前比例
	double m_currentScale;
	cv::Rect m_roi;

	// 设置缩放的最小值和最大值
	double scaleFactor;
	double minScale;
	double maxSCale;
};
