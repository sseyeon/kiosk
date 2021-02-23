#include<stdio.h>
#include<stdlib.h>


typedef struct Menu {
 char name[20];
 int price;
}Menu;

// 노드 정의
typedef struct basket {
 int num;
 struct basket * next;   //다음 노드를 가리키는 포인터
}basket;

basket * start = NULL; // 시작 노드를 가리키는 포인터

void showMenu(Menu * m) {

 printf("\n%20s\t\t%20s\t\t%20s\n", "<한식>", "<양식>", "<중식>");

 int n = 1;
 for (int i = 0; i < 3; i++) {
  for (int j = 0; j < 3; j++) {
   printf("%15s(00%d) / %6d원\t", m[n - 1].name, n, m[n - 1].price);
   n++;
  }printf("\n");
 }printf("\n");

}

void insert_end_Basket(basket * end, basket * new_node) {
 end->next = new_node;
}
void insert_Basket(int menu_num) {

 basket * cur = NULL; // 현재 노드를 가리키는 포인터
 basket * new_node = NULL;   // 새로 생성된 노드를 가리키는 포인터

 if (start == NULL) {   // 제일 처음 생성하는 노드
  new_node = (basket*)malloc(sizeof(basket));   //노드생성
  new_node->next = NULL;   // 포인터 초기화
  new_node->num = (menu_num)-1;   // 첫 노드에는 메인 음식 번호를 넣음
  start = new_node;   //시작지점으로 설정
 }
 else {
  new_node = (basket*)malloc(sizeof(basket));   //노드생성
  new_node->next = NULL;   // 포인터 초기화
  new_node->num = (menu_num)-1;   // 두번째부터는 세부사항

  // cur가 마지막 노드를 가리키게 함
  for (cur = start; cur->next != NULL; cur = cur->next);
  insert_end_Basket(cur, new_node);   // 다음 노드로 link
 }
}


void menuDetail() {
 while (1) {
  int sel;   // 선택 입력
  printf("\n1. 음료추가 (1000원)\n");
  printf("2. 사이즈 업 (500원)\n");
  printf("3. 소스 추가 (700원)\n");
  printf("0. 종료\n");
  printf("세부사항을 선택해 주세요 >> ");
  scanf_s("%d", &sel);
  if (sel == 0)
   break;
  insert_Basket(sel);

 }
}

void showOrder(Menu * m, Menu * dm) {
 printf("\n\t< 주문 장바구니 > \n");
 basket * cur = NULL;
 if (start == NULL)
  printf("     주문 내역이 없습니다!\n\n");
 else {
  for (cur = start; cur != NULL; cur = cur->next) {
   if (cur == start) {
    printf("%14s / %6d원 \n", m[cur->num].name, m[cur->num].price);
   }
   else {
    printf("%14s / %6d원 \n", dm[cur->num].name, dm[cur->num].price);
   }
  }
 }printf("\n");
}

void Payment(Menu *m, Menu * dm, int T_O) {
 basket * cur = NULL;
 int totalpay = 0;
 for (cur = start; cur != NULL; cur = cur->next) {
  if (cur == start) {
   totalpay += m[cur->num].price;
  }
  else {
   totalpay += dm[cur->num].price;
  }
 }
 if (T_O == 2) {
  int tmp = totalpay;
  totalpay *= 0.9;
  printf("\n테이크아웃 할인 적용 : %d 원 -> %d 원\n", tmp, totalpay);
 }
 printf("\n최종 결제 금액 : %d원\n\n", totalpay);
}

void freeBasket(basket ** start) {
 while (*start != NULL) {
  basket *tmp = *start;
  (*start) = (*start)->next;
  free(tmp);

 }
 printf("결제 완료 ! \n");
 printf("<< 이용해주셔서 감사합니다. >> \n");
}

void main() {

 int T_O;
 Menu m[9] = { { "순두부찌개", 7000 }, { "로제 파스타", 6500 }, { "짜장면", 5000 }, { "전주비빔밥", 8000 }, { "돈까스", 7500 }, { "탕수육", 12000 }, { "양념게장 정식", 8500 } , { "소고기 필라프", 7000 }, { "마파두부밥", 8000 } };
 Menu detailMenu[3] = { {"음료 추가", 1000}, {"사이즈 업", 500}, {"소스 추가", 700} };
 basket*first = 0;

 printf("\n\t1.매장에서 식사\t\t2.테이크아웃\n >> ");
 scanf_s("%d", &T_O);
 system("pause");
 system("cls");

 while (1) {
  int menu, menu_num;
  printf("\n");
  printf("1. 메뉴선택\n");
  printf("2. 주문사항 확인\n");
  printf("3. 결제\n");
  printf("0. 종료\n\n");
  printf("번호 입력 >> ");
  scanf_s("%d", &menu);
  system("cls");
  switch (menu) {
  case 1:
   showMenu(m);
   // [순두부, 7000]
   printf("메뉴번호를 입력하세요 : ");
   scanf_s("%d", &menu_num);
   // 변수 int로 저장
   insert_Basket(menu_num);
   system("pause"); system("cls");
   menuDetail();   //여기에 while문 쓰기  
   break;
  case 2:
   showOrder(m, detailMenu);
   break;
  case 3:
   Payment(m, detailMenu, T_O);
   freeBasket(&start);
   break;
  case 0:
   exit(1);
  default:
   printf("번호를 잘못 입력하셨습니다. 다시 입력해주세요.\n");
   break;
  }system("pause");
  system("cls");
 }
}
