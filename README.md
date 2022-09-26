# std_cpp
아두이노 설계
필요 기능: 블루투스(hm 10), 서보 모터, 그릇 위치 저장(전역 변수), 배열 ing(서보 보터-재료 연결)

1. 핸드폰 - 아두이노 연결: 블루투스 통신 - 입력이 있을 때까지 대기, 입력이 많은 경우 차례대로 수행
2. 블루투스로 수신한 신호를 통해 서보 모터 제어: (벨트부분 작동 -> 정지 -> 재료 부분 작동) 반복
3. 순서: 앱(메뉴 입력) -> 블루투스 송신 -> 블루투스 수신(아두이노) -> 메뉴에 따라 다른 순서 동작
    메뉴 ex) 라면: 벨트 작동 -> 벨트 정지(스프 부분 도착) -> 스프 서보 모터 동작(재료 투하) -> 벨트 이동 -> 벨트 정지(후레이크 부분 도착) -> 후레이크 서보 모터 동작(재료 투하) -> 벨트 이동 -> 벨트 정지(인덕션 도착) -> ... -> 인덕션 서보 모터 동작및 정지(불 on) -> 인덕션 서보 모터 동작및 정지(불 off) -> 조리 완료 
    조리 완료 메세지 블루투스 송신 -> 앱 블루투스 수신
4. 필요 함수? - 재료 부분 서보 모터 번호 설정: 메뉴에 따라 번호 순서로 재료 투하
            - 서보 모터 작동 함수 convyor(현재, 목표): (현재 위치 - 목표 재료 번호)*동작 시간
            - 재료 투하 함수 cook(메뉴): 배열 사용 
                for(int i = 0; i < sizeof(ing); i++){
                convyor(현재 위치, 목표 위치)
                // 재료 투하 코드 입력
                }
                convyor(현재 위치, 인덕션 위치)
메뉴 저장 배열 요소 구성: ([메뉴이름], [재료(순서)], [재료(그람수)])

22/09/23 - 회의 결과, 기존 목표에 한계가 존재하므로 목표 수정이 필요하다는 의견이 나옴.
    한계: '자동 조리기'의 재료를 담을 통이 무한정 늘어날 수 없다는 물리적 한계(통이 늘어날 경우, 크기도 커짐)
    대안: '자동 조리기'의 기능을 라면 조리로 한정 + a* 알고리즘을 통한 음식 배달 최적 경로 생성 기능 추가
    추가 의견: 라면 용기 셋팅기능 필요, 물 공급용 펌프 필요, 인덕션 제어 기능 필요

22/09/24 - 현황: 서보 모터 작동 확인, 외부 전력 필요성 확인, 메뉴에 따른 서보 모터 동작 알고리즘 초안 완성

22/09/24 - 추가 기능 및 모듈
    필요 기능: 용기 자동 세팅, 펌프를 통한 물 공급, 인덕션 제어, 블루투스 제어 코드와 결합 필요
    추가 부품 및 모듈: 6v 건전지 홀더(AA 1.5v 4개) 3개, 펌프, 릴레이 모듈(인덕션 제어), 추가 서보 모터 

22/09/26 - 회의: 기존 기술과의 차별점 필요

