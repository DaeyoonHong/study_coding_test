# Study Programmers Cursor

이 폴더는 Cursor AI를 통해 생성된 프로그래머스 문제 해결 코드들을 포함합니다.

## 파일 목록

### 1. 02_biggest_num_efficient.c
**문제**: 가장 큰 수 만들기  
**방법**: 문자열 연결 비교 기반 정렬  
**핵심 로직**: 
- 두 문자열을 연결했을 때 어떤 것이 더 큰지 비교
- `"6" + "10" = "610"` vs `"10" + "6" = "106"` 비교
- 시간 복잡도: O(n log n)

### 2. 03_biggest_num_first_digit.c  
**문제**: 가장 큰 수 만들기  
**방법**: 첫 번째 자릿수 기반 정렬  
**핵심 로직**:
- 첫 번째 자릿수를 기준으로 내림차순 정렬
- 같은 자릿수끼리는 전체 숫자 비교
- 시간 복잡도: O(n log n)

## 컴파일 및 실행

```bash
# 문자열 연결 비교 방법
gcc -o biggest_num_efficient 02_biggest_num_efficient.c
./biggest_num_efficient

# 첫 번째 자릿수 기반 방법  
gcc -o biggest_num_first_digit 03_biggest_num_first_digit.c
./biggest_num_first_digit
```

## 입력 예시
```c
int numbers[] = {6, 10, 2};
```

## 출력 예시
```
가장 큰 수: 6210
```

## 알고리즘 비교

| 방법 | 시간복잡도 | 정확성 | 구현 난이도 |
|------|------------|--------|-------------|
| 모든 순열 생성 | O(n!) | 완벽 | 높음 |
| 문자열 연결 비교 | O(n log n) | 완벽 | 중간 |
| 첫 번째 자릿수 | O(n log n) | 대부분 정확 | 낮음 |

**권장**: 문자열 연결 비교 방법 (02_biggest_num_efficient.c) 