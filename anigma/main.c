#include <stdio.h>
#include <memory.h>

// 각 로터의 배선 데이터 (0~25 범위의 정수 매핑)
// Index: 0(A) 1(B) 2(C) ... 25(Z)
int WIRING_1[] = { 4,10,12,5,11,6,3,16,21,25,13,19,14,22,24,7,20,18,0,9,1,2,23,8,15,17 }; // Rotor I
int WIRING_2[] = { 0,9,3,10,18,8,17,20,23,1,11,7,22,19,12,2,16,6,25,13,15,24,5,21,14,4 }; // Rotor II
int WIRING_3[] = { 1,3,5,7,9,11,13,2,15,3,19,18,20,23,21,14,12,10,8,6,4,0,17,22,24,25 };  // Rotor III
int REFLECT_B[] = { 24,17,20,7,16,18,11,3,15,23,13,6,14,10,12,8,4,1,5,25,2,22,21,9,0,19 };// Reflector B

// 로터 함수 (direction: 0은 순방향, 1은 역방향)
int rotor(int input, int wiring[], int direction) {
    if (direction == 0) {
        // 순방향: 인덱스 자체가 입력값이 됨 (a=0 -> wiring[0])
        return wiring[input];
    }
    else {
        // 역방향: 치환값(wiring[i])이 입력값과 일치하는 인덱스(i)를 찾아 반환
        for (int i = 0; i < 26; i++) {
            if (wiring[i] == input) return i;
        }
    }
    return -1; // 에러 케이스
}

int reflector(int input) {
    // 반사기도 동일하게 0~25 인덱스 직접 참조
    return REFLECT_B[input];
}

int plugboard(int* plug, int input)
{
    if (plug[input] == -1)
    {
        return input;
    }
    return plug[input];
}

int main() {
    char letter = 0;
    printf("알파벳 소문자 한 개를 입력하세요 (a-z): ");

    // 이전에 남아있을 수 있는 엔터 키(\n)를 무시하기 위해 공백 추가
    if (scanf(" %c", &letter) != 1) return 0;

    // a=0, b=1 ... z=25 처리
    int input = (int)letter - 97;

    if (input < 0 || input > 25) {
        printf("잘못된 입력입니다.\n");
        return 0;
    }

    int N = 0;
    int Plug[26] = { 0, };
    memset(Plug, -1, 26); //나중에 plugboard 입력이 들어왔을때 -1이면 그대로 다시 출력
    printf("[plugboard] 몇개?: ");
    scanf("%d", &N);
    char buffer[2] = { 0, };

    for (int i = 0; i < N; i++)
    {
        printf("[plugboard] ? <-> ?");
        scanf("%c %c", &buffer[0], &buffer[1]);
        Plug[buffer[0] - 97] = buffer[1] - 97;
        Plug[buffer[1] - 97] = buffer[0] - 97;
    }

    // --- 암호화 경로 (Signal Path) ---

    // 1. Forward Pass (우측 로터 -> 좌측 로터 순서)
    int pass1 = rotor(input, WIRING_3, 0); // Rotor III
    int pass2 = rotor(pass1, WIRING_2, 0); // Rotor II
    int pass3 = rotor(pass2, WIRING_1, 0); // Rotor I

    // 2. Reflection (유턴)
    int reflected = reflector(pass3);

    // 3. Backward Pass (좌측 로터 -> 우측 로터 순서)
    int pass4 = rotor(reflected, WIRING_1, 1); // Rotor I Inverse
    int pass5 = rotor(pass4, WIRING_2, 1);     // Rotor II Inverse
    int pass6 = rotor(pass5, WIRING_3, 1);     // Rotor III Inverse

    // 출력 처리: 숫자를 다시 문자로 변환 (+97)
    printf("입력: %c (정수: %d) -> 출력: %c (정수: %d)\n", letter, input, (char)(pass6 + 97), pass6);

    return 0;
}
