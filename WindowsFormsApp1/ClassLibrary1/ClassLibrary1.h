#pragma once

#include <msclr/gcroot.h>
#include <opencv2/opencv.hpp>

#ifdef _DEBUG
//Debugモードの場合
#pragma comment(lib,"C:\\opencv\\build\\x86\\vc14\\lib\\opencv_core2413d.lib")
#pragma comment(lib,"C:\\opencv\\build\\x86\\vc14\\lib\\opencv_highgui2413d.lib")
#pragma comment(lib,"C:\\opencv\\build\\x86\\vc14\\lib\\opencv_imgproc2413d.lib")
#pragma comment(lib,"C:\\opencv\\build\\x86\\vc14\\lib\\opencv_calib3d2413d.lib")
#pragma comment(lib,"C:\\opencv\\build\\x86\\vc14\\lib\\opencv_features2d2413d.lib")
#pragma comment(lib,"C:\\opencv\\build\\x86\\vc14\\lib\\opencv_gpu2413d.lib")
#pragma comment(lib,"C:\\opencv\\build\\x86\\vc14\\lib\\opencv_objdetect2413d.lib")
#else
//Releaseモードの場合
#pragma comment(lib,"C:\\opencv\\build\\x86\\vc14\\lib\\opencv_core2413.lib")
#pragma comment(lib,"C:\\opencv\\build\\x86\\vc14\\lib\\opencv_highgui2413.lib")
#pragma comment(lib,"C:\\opencv\\build\\x86\\vc14\\lib\\opencv_imgproc2413.lib")
#pragma comment(lib,"C:\\opencv\\build\\x86\\vc14\\lib\\opencv_calib3d2413.lib")
#pragma comment(lib,"C:\\opencv\\build\\x86\\vc14\\lib\\opencv_features2d2413.lib")
#pragma comment(lib,"C:\\opencv\\build\\x86\\vc14\\lib\\opencv_gpu2413.lib")
#pragma comment(lib,"C:\\opencv\\build\\x86\\vc14\\lib\\opencv_objdetect2413.lib")
#endif

using namespace cv;
using namespace System;

namespace ClassLibrary1 {
	public class TestClass
	{
	public:
		msclr::gcroot<Drawing::Bitmap^> bmp;

		void SetBitmap(Mat image)
		{
			IplImage iplImage = image;
			bmp = gcnew Drawing::Bitmap(iplImage.width, iplImage.height, Drawing::Imaging::PixelFormat::Format24bppRgb);

			Drawing::Imaging::BitmapData^ bd =
				bmp->LockBits(
					Drawing::Rectangle(0, 0, iplImage.width, iplImage.height),
					Drawing::Imaging::ImageLockMode::WriteOnly,
					Drawing::Imaging::PixelFormat::Format24bppRgb);

			for (int i = 0; i < iplImage.height; i++) {
				uchar *p = (uchar *)bd->Scan0.ToPointer() + i * bd->Stride;
				memcpy(p, iplImage.imageData + iplImage.widthStep * i, iplImage.widthStep);
			}

			bmp->UnlockBits(bd);
		}

		Drawing::Bitmap^ TestMethod()
		{
			auto image = cv::imread("Penguins.jpg");
			SetBitmap(image);
			return bmp;
		}
	};

	public ref class Class1
	{
	private:
		TestClass * clsTest; // ネイティブクラスへのポインタ

	public:
		// TODO: このクラスのメソッドをここに追加します。
		// コンストラクタ
		Class1() {
			clsTest = new TestClass(); // ネイティブオブジェクト生成
		}

		// デストラクタ
		~Class1() {
			delete clsTest; // ファイナライザを呼ぶ
		}

		// ラッパ
		Drawing::Bitmap^ TestMethod()
		{
			return clsTest->TestMethod();
		}
	};

}
