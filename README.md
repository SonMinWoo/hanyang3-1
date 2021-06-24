# hanyang3-1
3학년 1학기에 수행한 전공과목 프로젝트들입니다.
실습은 기재해놓은 각 연구실에서 기본 코드를 제공했으며 프로젝트는 직접 수행하였습니다.

## 멀티미디어
멀티미디어 정보처리 과목에서는 영상처리 관련한 내용을 다루었습니다.
영상의 산술연산, 잡음제거, 선명화 등을 low-level processing
영상 연결과 같은 고전적 영상인식 관련 내용을 intermediate-level processing
인공지능/딥러닝 기반 영상인식 알고리즘(CNN, U-net, VGG16, ResNet, Lenet)을 high-level processing
위의 세가지 부분으로 나누어 공부했습니다.
실습은 한양대학교 Computer Vision & Pattern Recognition Lab에서 진행했습니다.

### 실습
1. 이미지 읽기 
2. 이미지 산술 연산
3. 히스토그램 기반 처리(Contrast-stretching / Histogram equalization) 및 이진화
4. Convolution 기반 이미지 잡음제거, 이미지 Segmentaion
5. 이미지 내 특징점검출
6. 특징점 검출 기반 이미지 파노라마 제작 (중간고사 대체과제 프로젝트를 겸함)
7. 인공지능-선형회귀 실습
8. 딥러닝 기반 이미지 Segmentaion (U-Net) 
9. LeNet 기반 이미지 Classification
10. ResNet 기반 이미지 Classification

### 프로젝트
1. 자체 제작 이미지를 통한 특징점 검출
2. 여러 이미지를 이용한 파노라마 제작
3. VGG16모델 구현 

## 네트워크
네트워크 과목에서는 지정한 html 파일을 client가 접속하면 되돌려주는 프로그램을 작성하는 서버 프로그램 제작 프로젝트를 수행했습니다.

## 운영체제
운영체제 과목에서는 Operating system concepts 10th를 기준으로 진도를 나가며 책의 내용을 실습으로 다루었습니다.
실습은 한양대학교 정보보호연구실에서 진행했습니다.

### 실습
1. 커널에 시스템 콜 추가
2. 멀티프로세싱 & 파이프
3. 모듈 프로그래밍
4. ps 명령어 직접 구현
5. 시스템 콜 추적 코드 직접 제작
6. 프로세스 동기화(Peterson Solution, Mutex)
7. 프로세스 동기화(Semaphore, Producer-Consumer Problem)
8. Reader-Writer Problem 읽는자 선호-first variation(mutex 사용 / Conditional Variables 사용)
9. Deadlock(Dining philosophers problem) and solution
10. Deadlock(Cigarette Smokers Problem)
11. Paging(FIFO, LRU, Optimal)

### 프로젝트
1. Mini shell 구현 (Multiprocessing)
2. Sudoku 멀티스레드 처리 (multithreading)
3. Producer-Consumer Problem 2nd variation&3rd variation (쓰는자 선호/공정한 알고리즘) 구현
4. Threadpool 구현
