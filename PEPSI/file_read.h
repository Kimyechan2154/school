#ifndef FILE_READ//파일 구조와 역할 설명
#define FILE_READ

int ptFileRead(uint8_t** pt, FILE* ptFile);//평문 텍스트 파일 읽음
int traceFileRead(float** trace, FILE* traceFile);//암호문 텍스트 파일 읽음

#endif