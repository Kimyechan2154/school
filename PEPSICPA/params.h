/*헤더 가드: 하나의 헤더 파일이 같은 소스 코드
파일 내에서 여러번 중복(재정의 에러)으로 포함되는 것을 막음
#ifndef가 여러번 나오면 조건이 거짓이 되어 내부코드가 무시됨
#ifndef: 메크로 지정 안되있다면 아래 코드 읽기 #endif: 조건문 종료 */

#ifndef PARAM // 파일 경로 및 데이터 설정값 모아둠
#define PARAM //매크로 정의

//#define TRACE_PATH "C:\\Users\\kimye\\OneDrive\\Desktop\\KMU\\PEPSI\\PEPSI_DPA과제\\DPA data\\CW_Lite_powerConsumption.trace"
//#define PT_PATH "C:\\Users\\kimye\\OneDrive\\Desktop\\KMU\\PEPSI\\PEPSI_DPA과제\\DPA data\\CW_Lite_plain.txt"

#define TRACE_PATH "C:\\Users\\kimye\\OneDrive\\Desktop\\KMU\\PEPSI\\PEPSI_trace\\simpleserial-aes-SPA\\260330_185244.trace"
#define PT_PATH "C:\\Users\\kimye\\OneDrive\\Desktop\\KMU\\PEPSI\\PEPSI_trace\\simpleserial-aes-SPA\\260330_185244_plain.txt"

#define NUM_TRACE 5000//총 파형수
#define NUM_POINT 3724 //하나의 파형이 갖는 데이터 포인트 수 

#endif
