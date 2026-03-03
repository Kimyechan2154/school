# DSA(차분 전력 분석)

수집된 파형의 평균의 차를 이요해 비밀 정보 분석 - 옳은 키 예측시 두 집단 간의 실제 소비전력 차이가 뚜렷하게 나타난다

- 가정: 공격자는 평문을 알고 있고 다량의 전력 파형 수집 가능

- 1단계 – 중간값 선택(Sbox output)
- 2단계 – 전력소비 측정
- 3단계 – 예상되는 중간값 계산
- 4단계 – 중간값과 전력소비 값의 관계 선택
- 5단계 – 예상되는 전력 값과 측정된 전력소비 비교

평문과 전력 파형을 알고 있을 때 중간값을 선택한 후 전력 파형 값을 측정한후 분류에 따라 나눈 후 A, B 두가지의 파형의 평균을 구하고 둘을 뺐을때 평균이 비슷하다면 틀린키고 차이가 크면 진짜 키다

# AES Differential Power Analysis (DPA)

C언어를 이용한 AES-128 차분 전력 분석(DPA) 공격 구현 프로젝트입니다.
`powerConsumption.trace` 바이너리 파일을 분석하여 암호 장비의 비밀키(Secret Key)를 찾아내는 것을 목표로 합니다.

## 📁 프로젝트 구조
- **main.c**: 전력 파형 데이터를 읽고 DPA 공격을 수행하는 메인 소스 코드
- **powerConsumption.trace**: 분석 대상 전력 파형 데이터 (별도 구비 필요)

## 🚀 개발 환경
- **Language**: C
- **IDE**: Visual Studio
- **Target**: AES-128

## 📝 구현 기능 (To-Do)
- [x] Trace 파일 헤더 파싱 (Header Parsing)
- [x] 전력 데이터 메모리 로드
- [ ] AES S-Box 구현
- [ ] DPA 공격 알고리즘 구현 (Key Guessing)
- [ ] Peak 탐지 및 비밀키 도출

## 🔧 실행 방법
1. Visual Studio에서 프로젝트 생성 후 `main.c` 추가
2. 프로젝트 폴더에 `powerConsumption.trace` 파일 위치
3. 빌드 및 실행 (Ctrl + F5)

## 📊 Trace 파일 구조
| Offset | Field | Size |
|---|---|---|
| 0~19 | Name | 20 bytes |
| 20~23 | Num Traces | 4 bytes (int) |
| 24~27 | Num Points | 4 bytes (int) |
| 28~31 | End Tag | 4 bytes |
| 32~ | Power Data | Float array |
