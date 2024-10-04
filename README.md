프로젝트 - OpenCV Mosaic Project

1) 프로젝트 설명
- 이 프로젝트는 C++과 OpenCV를 사용하여 실시간 얼굴 인식 및 모자이크 효과를 적용하는 프로그램입니다. 
- 사용자가 웹캠을 통해 얼굴을 인식하고, 선택한 필터(빨간 사각형, 블러, 모자이크)를 얼굴 부위에 실시간으로 적용할 수 있습니다.

2) 프로젝트 파일 구성
- opencv.cpp : 얼굴 인식과 필터 적용 로직이 포함된 C++ 코드
- opencv_mosaicPPT.pdf : 프로젝트 발표 자료
- opencvproject.vcxproj, .filters, .user : Visual Studio 프로젝트 파일
- opencv_mosaic 보고서.pdf : 프로젝트 설명 및 결과 보고서
- 시연 영상.mp4 : 프로젝트 시연 영상

* 그외에 opencv 파일도 업로드 해야되나 파일의 용량 문제로 업로드 하지 못하였습니다.

3) 요구 사항 - 이 프로젝트를 실행하려면 아래의 프로그램과 라이브러리가 필요합니다
- Visual Studio 2022 또는 그 이상의 버전
- OpenCV 라이브러리 4.x 버전
- CMake (Visual Studio에서 OpenCV 빌드를 위해 필요할 수 있음)

4) OpenCV 설정 방법
- OpenCV 공식 사이트에서 OpenCV 4.x 버전을 다운로드합니다.
- 다운로드한 파일을 로컬 컴퓨터에 압축 해제합니다.
- Visual Studio에서 프로젝트 속성에서 VC++ 디렉터리 > 포함 디렉터리와 라이브러리 디렉터리에 OpenCV 경로를 추가합니다.
- 포함 디렉터리: C:/path_to_opencv/build/include
- 라이브러리 디렉터리: C:/path_to_opencv/build/x64/vc15/lib
- 프로젝트 속성에서 링커 > 입력에 아래와 같은 추가 종속 라이브러리를 추가합니다:
- opencv_world470.lib (버전에 맞게 파일 이름을 수정하세요)

* 제가 참고한 사이트 입니다.
- https://m.blog.naver.com/dorergiverny/223057719024 
- https://velog.io/@mouse0429/openCVVisual-Studio-OpenCV-%EC%84%A4%EC%B9%98

5) 실행 방법
- Visual Studio에서 프로젝트를 엽니다.
- OpenCV가 제대로 설정되었는지 확인합니다.
- 웹캠을 연결한 후, 프로그램을 실행합니다.
- 웹캠에서 얼굴을 인식하고, 마우스를 통해 선택한 필터(빨간 사각형, 블러, 모자이크)를 얼굴 부위에 적용할 수 있습니다.

6) 주의 사항
- OpenCV 라이브러리 파일은 용량이 커서 GitHub에 업로드되지 않았습니다. 따라서 위의 설정 방법에 따라 OpenCV를 수동으로 설정해야 합니다.
- 프로그램 실행 시 웹캠이 필요합니다. 웹캠이 연결되지 않으면 프로그램이 정상적으로 동작하지 않을 수 있습니다.

7) 프로젝트 시연
- 프로젝트의 시연 영상은 시연 영상.mp4 파일에서 확인할 수 있습니다.
