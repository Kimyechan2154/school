#실습 23
age = 20
score = 85

print(age > 19 and score > 80) # True
print(age < 19 or score < 80) # False
print(not(age == 20)) # False

#실습 24

test1 = input("문자열 입력: ")
target1 = input("찾고 싶은 문자: ")
loc1 = test1.find(target1)  #없는 문자를 찾을때 -1값이 나오기 위해 find 함수 이용
print("입력하신 '{}'에서 첫번째 '{}'는 {}번째 위치에 있습니다" .format(test1, target1, loc1))

#실습 25

target1 = input("문자열 입력: ")
target2 = input("문자열 입력: ")

if target1.lower() == target2.lower(): #대, 소문자 구분 없애기
    print("두 문자열은 같습니다.")
else:
    print("두 문자열은 다릅니다.")

#실습 26

email = input("email 입력: ")
id = email.split("@") #@기준으로 나누기
domain = email.split(".") #.기준으로 나누기
print("입력하신 이메일의 아이는 {}, 도메인은 '{}', 최상위 도메인은 '{}'입니다.".format(id[0], id[1], domain[-1]))

#실습 27

password = input("password 입력: ")
result = password.isdigit()

if len(password) < 8:
    print("사용 불가능한 비밀번호입니다.")
elif password.isdigit():
    print("사용 불가능한 비밀번호입니다.")
elif password.isalpha():
    print("사용 불가능한 비밀번호입니다.")
else:
    print("사용 가능한 비밀번호입니다.")
