#include "opencv2/opencv.hpp" // OpenCV ���̺귯�� ����
#include <iostream> // ǥ�� ����� ��Ʈ�� ��� ���� ����

using namespace cv; // OpenCV ���ӽ����̽� ���
using namespace std; // ǥ�� ���ӽ����̽� ���

const String faceCascadePath = "C:/opencv/sources/data/haarcascades/haarcascade_frontalface_default.xml"; // �� �ν� XML ���� ���
CascadeClassifier faceCascade; // �� �ν��� ���� �з��� ��ü ����

Mat frame; // ī�޶󿡼� ĸ���� �������� ������ ����
int optionNum = 0; // ����ڰ� ������ �ɼ� ��ȣ�� ������ ����

// ���콺 �̺�Ʈ ó�� �Լ�
void onMouse(int event, int x, int y, int flags, void* userdata) {
    if (event == EVENT_LBUTTONDOWN) { // ���콺 ���� ��ư�� ������ ��
        if (x >= 0 && x < 213 && y >= 0 && y < 70) optionNum = 1; // ù ��° ���� ����
        else if (x >= 213 && x < 426 && y >= 0 && y < 70) optionNum = 2; // �� ��° ���� ����
        else if (x >= 426 && x < 640 && y >= 0 && y < 70) optionNum = 3; // �� ��° ���� ����
        else optionNum = 0; // �� �� ����
    }
}

// ������ũ ȿ���� �����ϴ� �Լ�
void mosaic(Rect roi) {
    int mosaicSize = 25; // ������ũ ũ��
    for (int i = roi.y; i < roi.y + roi.height; i += mosaicSize) {
        for (int j = roi.x; j < roi.x + roi.width; j += mosaicSize) {
            Rect rect = Rect(j, i, mosaicSize, mosaicSize) & Rect(0, 0, frame.cols, frame.rows);
            Scalar color = mean(frame(rect)); // �ش� ������ ��� ���� ���
            rectangle(frame, rect, color, FILLED); // ���� �������� �簢�� ä���
        }
    }
}

// ���� �Լ�
int main() {
    VideoCapture cap(0); // �⺻ ī�޶� ���

    if (!cap.isOpened()) { // ī�޶� ������ �ʾ��� �� ���� �޽��� ���
        cerr << "Camera open failed!" << endl;
        return -1;
    }

    if (!faceCascade.load(faceCascadePath)) { // �� �ν� XML ���� �ε� ���� �� ���� �޽��� ���
        cerr << "XML load failed!" << endl;
        return -1;
    }

    namedWindow("frame"); // ������ ����
    setMouseCallback("frame", onMouse); // ���콺 �ݹ� �Լ� ����

    Scalar white = Scalar(255, 255, 255); // �ؽ�Ʈ ���� (�Ͼ�)
    Scalar gray = Scalar(80, 80, 80); // �簢�� �׵θ� ���� (ȸ��)
    Scalar clicked = Scalar(0, 0, 0); // ������ ����

    Rect option1 = Rect(Point(0, 0), Size(213, 70)); // ù ��° �ɼ� ����
    Rect option2 = Rect(Point(213, 0), Size(213, 70)); // �� ��° �ɼ� ����
    Rect option3 = Rect(Point(426, 0), Size(213, 70)); // �� ��° �ɼ� ����

    while (true) { // ���� ����
        cap >> frame; // ī�޶� ������ ĸó
        if (frame.empty()) break; // �������� ����ִٸ� ����

        flip(frame, frame, 1); // ������ �¿� ����

        // �ɼ� �ؽ�Ʈ�� �簢�� �׵θ� �׸���
        putText(frame, "Option 1", Point(30, 40), FONT_HERSHEY_SIMPLEX, 0.5, white, 1, LINE_AA);
        putText(frame, "Option 2", Point(270, 40), FONT_HERSHEY_SIMPLEX, 0.5, white, 1, LINE_AA);
        putText(frame, "Option 3", Point(498, 40), FONT_HERSHEY_SIMPLEX, 0.5, white, 1, LINE_AA);

        rectangle(frame, option1, gray, 1, LINE_AA);
        rectangle(frame, option2, gray, 1, LINE_AA);
        rectangle(frame, option3, gray, 1, LINE_AA);

        vector<Rect> faces; // ����� �� ����� ����
        faceCascade.detectMultiScale(frame, faces); // �� ����

        for (const Rect& face : faces) { // �� �󱼿� ����
            switch (optionNum) { // ���õ� �ɼǿ� ���� �ٸ� ȿ�� ����
            case 1:
                rectangle(frame, face, Scalar(0, 0, 255), 2); // �� ������ ���� �簢�� �׸���
                break;
            case 2:
                GaussianBlur(frame(face), frame(face), Size(25, 25), 0); // �� ������ ����þ� �� ����
                break;
            case 3:
                mosaic(face); // �� ������ ������ũ ����
                break;
            }
        }

        imshow("frame", frame); // �����쿡 ������ �����ֱ�

        if (waitKey(30) == 27) { // ESC Ű�� ������ ����
            break;
        }
    }

    cap.release(); // �ڿ� ����
    destroyAllWindows(); // ��� ������ �ݱ�
    return 0;
}
