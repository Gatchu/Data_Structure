/*
 * postfix.c
 *
 *  2020 Data Structures, Homework #5
 *  Department of Computer Science at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STACK_SIZE 10
#define MAX_EXPRESSION_SIZE 20

/* stack 내에서 우선순위, lparan = 0 가장 낮음 */
typedef enum{
	lparen = 0,  /* ( 왼쪽 괄호 */
	rparen = 9,  /* ) 오른쪽 괄호*/
	times = 7,   /* * 곱셈 */
	divide = 6,  /* / 나눗셈 */
	plus = 5,    /* + 덧셈 */
	minus = 4,   /* - 뺄셈 */
	operand = 1 /* 피연산자 */
} precedence;


char infixExp[MAX_EXPRESSION_SIZE];   	/* infix expression을 저장하는 배열 */
char postfixExp[MAX_EXPRESSION_SIZE];	/* postfix로 변경된 문자열을 저장하는 배열 */
char postfixStack[MAX_STACK_SIZE];	/* postfix로 변환을 위해 필요한 스택 */
int evalStack[MAX_STACK_SIZE];		/* 계산을 위해 필요한 스택 */

int postfixStackTop = -1;  /* postfixStack용 top */
int evalStackTop = -1;	   /* evalStack용 top */

int evalResult = 0;	   /* 계산 결과를 저장 */

void postfixPush(char x)
{
    postfixStack[++postfixStackTop] = x;
}

// 후위 표기 변환을 위해 필요한 스택에 데이터를 입력하는 함수입니다.
// 스택에서 Top은 가장 마지막에 추가된 데이터를 가리키기 때문에 데이터가 하나 저장될 때마다 한 번씩 커집니다.
// 매개변수로 입력받은 데이터를 스택의 가장 마지막에 추가시키는 역할을 합니다.
// 또, Top을 초기화할 때 -1로 초기화했으므로 전위 증감 연산자를 통해 Top의 값을 먼저 증가시키고, 그 위치에 데이터를 넣어 Top이 마지막 데이터를 가리키게 합니다.

char postfixPop()
{
    char x;
    if(postfixStackTop == -1)
        return '\0';
    else {
    	x = postfixStack[postfixStackTop--];
    }
    return x;
}

// 후위 표기 변환을 위해 필요한 스택에서 데이터를 꺼내는 함수입니다.
// 스택에서 Top은 가장 마지막에 추가된 데이터를 가리키고, 스택은 Last In First Out구조이기 때문에 Top이 가리키는 데이터를 꺼내면 됩니다.
// Top이 -1이 아니라면 Top이 가리키는 데이터를 꺼냅니다. 이때 Top이 -1이 된 것은 스택이 비었다는 것을 의미합니다.
// 이때, 후위 증감 연산자를 통해 Top이 가리키는 데이터를 먼저 꺼내고, 빈 공간이 된 이후에 Top이 다시 앞으로 이동해 마지막 데이터를 가리키게 합니다.
// 이후 가져온 데이터를 반환합니다.


void evalPush(int x)
{
    evalStack[++evalStackTop] = x;
}

// 후위 표기식의 계산을 위해 필요한 스택에서 데이터를 가져오는 함수입니다.
// postfixPust와 마찬가지로 전위 증감 연산자를 통해 Top의 값을 먼저 증가시킨 뒤에 매개변수로 받은 데이터를 Top이 가리키는 곳에 입력합니다.

int evalPop()
{
    if(evalStackTop == -1)
        return -1;
    else
        return evalStack[evalStackTop--];
}

// 후위 표기식의 계산을 위해 필요한 스택에서 데이터를 꺼내는 함수입니다.
// Top이 -1이 아니라면(스택이 비지 않았다면) 스택에서 데이터를 꺼냅니다.
// postfixPop와 마찬가지로 후위 증감 연산자를 통해 데이터를 먼저 꺼낸 뒤 Top를 감소시킵니다.



/**
 * infix expression을 입력받는다.
 * infixExp에는 입력된 값을 저장한다.
 */
void getInfix()
{
    printf("Type the expression >>> ");
    scanf("%s",infixExp);
}

// 후위 표기식으로 변경할 식을 받아오는 함수입니다.
// 문자열을 받아오는 %s를 통해 infixExp에 식을 문자로 저장합니다.

precedence getToken(char symbol)
{
	switch(symbol) {
	case '(' : return lparen;
	case ')' : return rparen;
	case '+' : return plus;
	case '-' : return minus;
	case '/' : return divide;
	case '*' : return times;
	default : return operand;
	}

}

// 연산자를 받아와 문자화하는 함수입니다.

precedence getPriority(char x)
{
	return getToken(x);
}

// 문자화된 데이터를 받아 enum으로 반환하는 함수입니다.
// 예시로, '('를 문자로 받으면 lparen으로 문자화하고, 우선순위 0을 가집니다.
// 이것으로 연산자 간의 우선순위 비교가 가능합니다.

/**
 * 문자 하나를 전달받아, postfixExp에 추가
 */
void charCat(char* c)
{
	if (postfixExp == '\0')
		strncpy(postfixExp, c, 1);
	else
		strncat(postfixExp, c, 1);
}

/**
 * infixExp의 문자를 하나씩 읽어가면서 stack을 이용하여 postfix로 변경한다.
 * 변경된 postfix는 postFixExp에 저장된다.
 */
void toPostfix()
{
	/* infixExp의 문자 하나씩을 읽기위한 포인터 */
	char *exp = infixExp;
	char x; /* 문자 하나를 임시로 저장하기 위한 변수 */

	/* exp를 증가시켜가면서, 문자를 읽고 postfix로 변경 */
	while(*exp != '\0')
	{
		for(int i = 0; i < MAX_EXPRESSION_SIZE-1; i++){
			char *check = infixExp;
			if(infixExp[i+1] == '\0') break;
			if((infixExp[i] >= 48 && infixExp[i] <= 57) && (infixExp[i+1] >= 48 && infixExp[i+1] <= 57)){
				printf("[ERROR]Please input (0~9).\n");
				*infixExp = '\0';
				*(exp+1) = '\0';
				break;
			}else if((infixExp[i] >= 40 && infixExp[i] <= 43) || infixExp[i] == 45 || (infixExp[i] >= 47 && infixExp[i] <= 57)) check++;
			else{
				printf("[ERROR]Please input ""(,),+,-,*,/"".\n");
				*infixExp = '\0';
				*(exp+1) = '\0';
				break;
			}
		}

		// infixExp에 저장된 식을 먼저 전처리하는 부분입니다.
		// infixExp의 문자를 하나씩 읽으면서 infixExp가 끝났다면 다음으로 넘어가도록 합니다.
		// 불러온 문자와 다음 문자가 연속으로 아스키 코드로 숫자에 해당한다면, 10의 자리 숫자를 입력한 것이기 때문에 0~9를 입력하도록 에러 메세지를 출력합니다.
		// 또, infixExp와 *(exp+1)을 0으로 만들어 반복문을 종료, infixExp로 받은 식을 NULL로 만듭니다.
		// 불러온 문자가 아스키 코드로 숫자 하나에 대응하거나 허용된 연산자 - (,),+,-,*,/라면 다음 문자를 읽도록 합니다.
		// 이때, 숫자나 허용된 연산자가 아니라면 허용된 연산자를 입력하라는 에러 메세지를 출력하고, 10의 자리 숫자를 입력받았을 때와 마찬가지로 반복문을 종료, 식을 NULL로 만듭니다.

		precedence token1;
		token1 = getPriority(*exp);
		x = postfixPop();
		if(x != '\0') postfixPush(x);

		// x에 스택의 값을 하나 불러온 다음, 스택이 비어있지 않다면 다시 스택에 그 값을 돌려줍니다.
		// x는 임시로 스택의 값을 저장해 비교하기 위한 변수이기 때문입니다.

		if(token1 == operand) charCat(exp++);		// 불러온 문자가 숫자라면 바로 후위 표기식에 적고 다음으로 넘깁니다.
		else if(token1 == rparen){
			while(getPriority(postfixStack[postfixStackTop]) != lparen){
				x = postfixPop();
				charCat(&x);
			}
			postfixPop();
			exp++;
		}

		// 불러온 문자가 오른쪽 괄호 )라면, 스택에 저장된 연산자 왼쪽 괄호 (가 나올 때까지 연산자들을 후위 표기식에 적습니다.
		// 이후 스택에서 한 번 더 데이터를 빼내어 왼쪽 괄호 (를 버리고, 그대로 다음 문자를 읽어 오른쪽 괄호 )도 버립니다.

		else if (x == '\0') postfixPush(*exp++);			// 스택이 비었다면, 연산자를 바로 스택에 추가합니다.
		else if (token1 == lparen) postfixPush(*exp++);		// 왼쪽 괄호 (가 나왔다면, 스택에 추가합니다. 왼쪽 괄호의 우선순위는 스택 밖에서는 가장 높기 때문입니다.
		else {
			while(postfixStackTop > -1 && token1 <= getPriority(x)){
				x = postfixPop();					// 불러온 연산자의 우선순위가 스택에서 가져온 연산자의 우선순위보다 낮다면 스택에서 가져온 연산자를 꺼내 후위 표기식에 추가하고 불러온 연산자를 스택에 넣습니다. 이후 다음 문자를 불러옵니다.
				charCat(&x);
		}											// 불러온 연산자의 우선순위가 스택에서 가져온 연산자의 우선순위보다 높다면 스택에서 가져온 연산자를 스택에 그대로 두고, 불러온 연산자를 스택에 저장하고 다음 문자를 불러옵니다.
				postfixPush(*exp++);
		}
	}
	while(x != '\0'){
		x = postfixPop();
		charCat(&x);
	}
	// 일련의 과정이 끝난 뒤에 스택에 남아있는 연산자들을 모두 후위 표기식에 추가합니다.
}

	/* 필요한 로직 완성 */
void debug()
{
	printf("\n---DEBUG\n");
	printf("infixExp =  %s\n", infixExp);
	printf("postExp =  %s\n", postfixExp);
	printf("eval result = %d\n", evalResult);

	printf("postfixStack : ");
	for(int i = 0; i < MAX_STACK_SIZE; i++)
		printf("%c  ", postfixStack[i]);

	printf("\n");

}

// 사용자가 입력한 식, 후위 표기식으로 바뀐 식, 계산 결과, 스택에 쌓인 데이터를 모두 표시합니다.
// 이때, 스택에 쌓인 데이터가 완전 삭제된 것이 아니기 때문에 스택에 쌓인 데이터가 남아 있을 수 있습니다.

void reset()
{
	infixExp[0] = '\0';
	postfixExp[0] = '\0';

	for(int i = 0; i < MAX_STACK_SIZE; i++)
		postfixStack[i] = '\0';
         
	postfixStackTop = -1;
	evalStackTop = -1;
	evalResult = 0;
}

// 모든 조건을 초기로 되돌리는 함수입니다.

void evaluation()
{
	/* postfixExp, evalStack을 이용한 계산 */
    precedence token;
    char Symbol;
    int Op1, Op2;
    for(int i = 0; i < MAX_EXPRESSION_SIZE; i++){
        if(postfixExp[i] == '\0') break;					// 식의 끝에 도달했다면 반복문을 탈출합니다.
        token = getPriority(postfixExp[i]);					// 후위 표기식에서 가져온 데이터의 우선순위를 파악합니다.
        Symbol = postfixExp[i];								// 후위 표기식에서 가져온 데이터를 임시 저장합니다.
        if(token == operand) evalPush(Symbol-'0');			// 가져온 데이터가 숫자라면 스택에 문자가 아닌 숫자로 저장합니다. 이때, 스택에는 숫자만 저장됩니다.
        else{
            Op2 = evalPop();								// 스택에 저장된 숫자를 꺼내 임시저장합니다. 이때 스택은 Last In First Out이기 때문에, Op2가 스택에서 숫자를 먼저 꺼냅니다.
            Op1 = evalPop();								// Op2를 저장한 다음, 스택에서 다음 숫자를 꺼내 임시저장합니다.
            switch(token){
                case plus : evalPush(Op1+Op2);  break;		// 식에서 가져온 연산자와 스택에서 가져온 숫자를 통해 적절한 계산을 수행합니다.
                case minus : evalPush(Op1-Op2); break;
                case times : evalPush(Op1*Op2); break;
                case divide : evalPush(Op1/Op2);
            }
        }
    }
    evalResult = evalPop();									// 연산이 완료된 결과를 변수에 저장합니다.
}


int main()
{
	char command;

	do{
        printf("[-----Software, Student ID : 2017038040, Name : Han Gyu Jun-----]\n");
        // 성명과 학번이 출력되도록 소스를 수정했습니다. 한글은 컴파일시 깨져서 영문으로 작성했습니다.
		printf("----------------------------------------------------------------\n");
		printf("               Infix to Postfix, then Evaluation               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'i': case 'I':
			getInfix();
			break;
		case 'p': case 'P':
			toPostfix();
			break;
		case 'e': case 'E':
			evaluation();
			break;
		case 'd': case 'D':
			debug();
			break;
		case 'r': case 'R':
			reset();
			break;
		case 'q': case 'Q':
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 0;


}
