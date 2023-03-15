#include "MouseZoomImage.h"
#include <opencv2/core/utils/logger.hpp>
#include <opencv2/opencv.hpp>
#include<QDebug>
#include "qglobal.h"
#include "core/cvdef.h"

using namespace cv;

QImage Mat2QImage(cv::Mat const& src);

MouseZoomImage::MouseZoomImage(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MouseZoomImageClass()), m_bmove(false)
{
	ui->setupUi(this);
	m_currentScale = 1;

	m_image = cv::imread("./image/test.jpg", IMREAD_COLOR); // Read the file
	
	// ��¼
	m_roi = cv::Rect(0,0,m_image.cols, m_image.rows);
	m_width = m_image.cols;
	m_height = m_image.rows;
	if (m_width > 1920)
	{
		m_width = 1920;
	}
	if (m_height > 1080)
	{
		m_height = 1080;
	}
	cv::resize(m_image, m_image, Size( m_width, m_height), 0, 0, cv::INTER_AREA);
	m_tempimage = Mat2QImage(m_image);
	ui->label->setPixmap(QPixmap::fromImage(m_tempimage));
	ui->label->setAlignment(Qt::AlignCenter);

	m_ImagePos = QPoint(0,0);
	ui->label->resize(m_width, m_height);
	this->setFixedSize(m_width, m_height);
	cv::utils::logging::setLogLevel(utils::logging::LOG_LEVEL_SILENT);//���������־
	scaleFactor = 1.1; // ��������
	minScale = 1 / pow(1.1, 10);
	maxSCale = 1 * pow(1.1, 50);
}

MouseZoomImage::~MouseZoomImage()
{
    delete ui;
}


void MouseZoomImage::wheelEvent(QWheelEvent * event)
{
	// ��ȡ��굱ǰλ��
	QPointF mousePos = event->posF();
	
	// �������ű���
	double delta = event->delta() / 120.0;
	double scale = pow(scaleFactor, delta); // �������ű���
	m_currentScale *= scale;
	
	// ��Χ���
	if (m_currentScale < minScale)
	{
		m_currentScale = minScale;
	}
	if (m_currentScale > maxSCale)
	{
		m_currentScale = maxSCale;
	}

	Mat resized_up;
	if (m_currentScale <= 1)
	{
		cv::resize(m_image, resized_up, Size(m_width * m_currentScale, m_height * m_currentScale), 0, 0, cv::INTER_AREA);
		m_ImagePos = QPoint(0, 0);
	}
	else
	{
		//  ����ȡ�Ŀ��
		int iWidth = m_width / m_currentScale;
		int iHeight = m_height / m_currentScale;

		// �������λ�õ�ԭͼλ��
		qDebug() << mousePos;
		mousePos = (m_ImagePos * m_currentScale + mousePos * scale) / m_currentScale;
		qDebug() << mousePos;

		// �Ŵ�����λ�� ��ȥ��ǰ���λ�� 
		int x = mousePos.x() - event->pos().x() / (m_currentScale);
		int y = mousePos.y() - event->pos().y() / (m_currentScale);
		
		// rect��Χ��Ч���
		if (x < 0)
		{
			x = 0;
		}
		if (y < 0)
		{
			y = 0;
		}
		if (x + iWidth > m_width)
		{
			x = m_width - iWidth;
		}
		if (y + iHeight > m_height)
		{
			y = m_height - iHeight;
		}
		m_ImagePos = QPoint(x, y);
		resized_up = m_image(cv::Rect(x , y , iWidth, iHeight));
		cv::resize(resized_up, resized_up, Size(m_width, m_height), 0, 0, cv::INTER_CUBIC);
	}

	// ��OpenCV��Mat����ת����QImage����
	QImage image = Mat2QImage(resized_up);

	// ת��ΪQImage
	m_tempimage = QPixmap::fromImage(image).toImage(); 
	ui->label->setPixmap(QPixmap::fromImage(m_tempimage));
	return QWidget::wheelEvent(event);
}

QImage Mat2QImage(cv::Mat const& src)
{
	QImage dest(src.cols, src.rows, QImage::Format_ARGB32);

	const float scale = 255.0;

	if (src.depth() == CV_8U) {
		if (src.channels() == 1) {
			for (int i = 0; i < src.rows; ++i) {
				for (int j = 0; j < src.cols; ++j) {
					int level = src.at<quint8>(i, j);
					dest.setPixel(j, i, qRgb(level, level, level));
				}
			}
		}
		else if (src.channels() == 3) {
			for (int i = 0; i < src.rows; ++i) {
				for (int j = 0; j < src.cols; ++j) {
					cv::Vec3b bgr = src.at<cv::Vec3b>(i, j);
					dest.setPixel(j, i, qRgb(bgr[2], bgr[1], bgr[0]));
				}
			}
		}
	}
	else if (src.depth() == CV_32F) {
		if (src.channels() == 1) {
			for (int i = 0; i < src.rows; ++i) {
				for (int j = 0; j < src.cols; ++j) {
					int level = scale * src.at<float>(i, j);
					dest.setPixel(j, i, qRgb(level, level, level));
				}
			}
		}
		else if (src.channels() == 3) {
			for (int i = 0; i < src.rows; ++i) {
				for (int j = 0; j < src.cols; ++j) {
					cv::Vec3f bgr = scale * src.at<cv::Vec3f>(i, j);
					dest.setPixel(j, i, qRgb(bgr[2], bgr[1], bgr[0]));
				}
			}
		}
	}

	return dest;
}


/*
// �������ź��ͼƬ�Ĵ�С
		// �Ŵ��ı���ȡ�Ĳ�����ԭͼ��ȳ����൱����ԭͼ��ȡ���Ŵ�ǰ�����ű����ĳ���
		int width = m_width / m_currentScale;	// ����ȡ�Ŀ�(��ԭͼ����)
		int height = m_height / m_currentScale;	// ����ȡ�ĸ�(��ԭͼ����)/

		int dx = m_width * (m_currentScale - 1) / 2; // �Ŵ���ƫ����X
		int dy = m_height * (m_currentScale - 1) / 2; // �Ŵ���ƫ����Y

		int x = mousePos.x() - width / 2 - dx;
		int y = mousePos.y() - height / 2 - dy;
		qDebug() << QRect(x, y, width, height);
		// �жϽ�ȡλ�õķ�Χ
		if (x < 0)
		{
			x = 0;
		}
		if (y < 0)
		{
			y = 0;
		}
		if (x + width > m_width)
		{
			x = m_width - width;
		}
		if (y + height > m_width)
		{
			y = m_height - height;
		}

		resized_up = m_image(cv::Rect(x, y, width, height));
		cv::resize(resized_up, resized_up, Size(m_width, m_height),0,0,cv::INTER_CUBIC);
*/