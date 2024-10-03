#include "opencv2/opencv.hpp" // OpenCV 라이브러리 포함
#include <iostream> // 표준 입출력 스트림 헤더 파일 포함

using namespace cv; // OpenCV 네임스페이스 사용
using namespace std; // 표준 네임스페이스 사용

const String faceCascadePath = "C:/opencv/sources/data/haarcascades/haarcascade_frontalface_default.xml"; // 얼굴 인식 XML 파일 경로
CascadeClassifier faceCascade; // 얼굴 인식을 위한 분류기 객체 생성

Mat frame; // 카메라에서 캡쳐한 프레임을 저장할 변수
int optionNum = 0; // 사용자가 선택한 옵션 번호를 저장할 변수

// 마우스 이벤트 처리 함수
void onMouse(int event, int x, int y, int flags, void* userdata) {
    if (event == EVENT_LBUTTONDOWN) { // 마우스 왼쪽 버튼이 눌렸을 때
        if (x >= 0 && x < 213 && y >= 0 && y < 70) optionNum = 1; // 첫 번째 영역 선택
        else if (x >= 213 && x < 426 && y >= 0 && y < 70) optionNum = 2; // 두 번째 영역 선택
        else if (x >= 426 && x < 640 && y >= 0 && y < 70) optionNum = 3; // 세 번째 영역 선택
        else optionNum = 0; // 그 외 영역
    }
}

// 모자이크 효과를 적용하는 함수
void mosaic(Rect roi) {
    int mosaicSize = 25; // 모자이크 크기
    for (int i = roi.y; i < roi.y + roi.height; i += mosaicSize) {
        for (int j = roi.x; j < roi.x + roi.width; j += mosaicSize) {
            Rect rect = Rect(j, i, mosaicSize, mosaicSize) & Rect(0, 0, frame.cols, frame.rows);
            Scalar color = mean(frame(rect)); // 해당 영역의 평균 색상 계산
            rectangle(frame, rect, color, FILLED); // 계산된 색상으로 사각형 채우기
        }
    }
}

// 메인 함수
int main() {
    VideoCapture cap(0); // 기본 카메라 사용

    if (!cap.isOpened()) { // 카메라가 열리지 않았을 때 에러 메시지 출력
        cerr << "Camera open failed!" << endl;
        return -1;
    }

    if (!faceCascade.load(faceCascadePath)) { // 얼굴 인식 XML 파일 로드 실패 시 에러 메시지 출력
        cerr << "XML load failed!" << endl;
        return -1;
    }

    namedWindow("frame"); // 윈도우 생성
    setMouseCallback("frame", onMouse); // 마우스 콜백 함수 설정

    Scalar white = Scalar(255, 255, 255); // 텍스트 색상 (하양)
    Scalar gray = Scalar(80, 80, 80); // 사각형 테두리 색상 (회색)
    Scalar clicked = Scalar(0, 0, 0); // 사용되지 않음

    Rect option1 = Rect(Point(0, 0), Size(213, 70)); // 첫 번째 옵션 영역
    Rect option2 = Rect(Point(213, 0), Size(213, 70)); // 두 번째 옵션 영역
    Rect option3 = Rect(Point(426, 0), Size(213, 70)); // 세 번째 옵션 영역

    while (true) { // 무한 루프
        cap >> frame; // 카메라 프레임 캡처
        if (frame.empty()) break; // 프레임이 비어있다면 종료

        flip(frame, frame, 1); // 프레임 좌우 반전

        // 옵션 텍스트와 사각형 테두리 그리기
        putText(frame, "Option 1", Point(30, 40), FONT_HERSHEY_SIMPLEX, 0.5, white, 1, LINE_AA);
        putText(frame, "Option 2", Point(270, 40), FONT_HERSHEY_SIMPLEX, 0.5, white, 1, LINE_AA);
        putText(frame, "Option 3", Point(498, 40), FONT_HERSHEY_SIMPLEX, 0.5, white, 1, LINE_AA);

        rectangle(frame, option1, gray, 1, LINE_AA);
        rectangle(frame, option2, gray, 1, LINE_AA);
        rectangle(frame, option3, gray, 1, LINE_AA);

        vector<Rect> faces; // 검출된 얼굴 저장용 벡터
        faceCascade.detectMultiScale(frame, faces); // 얼굴 검출

        for (const Rect& face : faces) { // 각 얼굴에 대해
            switch (optionNum) { // 선택된 옵션에 따라 다른 효과 적용
            case 1:
                rectangle(frame, face, Scalar(0, 0, 255), 2); // 얼굴 주위에 빨간 사각형 그리기
                break;
            case 2:
                GaussianBlur(frame(face), frame(face), Size(25, 25), 0); // 얼굴 부위에 가우시안 블러 적용
                break;
            case 3:
                mosaic(face); // 얼굴 부위에 모자이크 적용
                break;
            }
        }

        imshow("frame", frame); // 윈도우에 프레임 보여주기

        if (waitKey(30) == 27) { // ESC 키가 눌리면 종료
            break;
        }
    }

    cap.release(); // 자원 해제
    destroyAllWindows(); // 모든 윈도우 닫기
    return 0;
}
