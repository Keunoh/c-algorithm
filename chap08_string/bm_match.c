/* Boyer-Moore법으로 문자열을 검색하는 프로그램 */
#include <stdio.h>
#include <string.h>
#include <limits.h>

/*--- Boyer-Moore법으로 문자열을 검색하는 함수 ---*/
int bm_match (const char txt[], const char pat[]) 
{
	int pt;						/* txt 커서 */
	int pp;						/* pat 커서 */
	int txt_len = strlen(txt);	/* txt 문자 개수 */
	int pat_len = strlen(pat);	/* pat 문자 개수 */
	int skip[UCHAR_MAX + 1];	/* 건너뛰기 표 */
	
	for (pt = 0; pt <= UCHAR_MAX; pt++)		/* 건너뛰기 표 만들기 */
		skip[pt] = pat_len;
	for (pt = 0; pt < pat_len - 1; pt++)	/* pt == pat_len - 1*/
		skip[pat[pt]] = pat_len - pt - 1;	
		
	while(pt < txt_len) {
		pp = pat_len - 1;		/* pat의 마지막 문자부터 검사 */
		while (txt[pt] == pat[pp]) { 
			if (pp == 0)
				return pt;
			pp--;
			pt--;
		}
		pt += (skip[txt[pt]] > pat_len - pp) ? skip[txt[pt]] : pat_len - pp;
	}
	return -1;
}

int main (void)
{
	int idx;
	char s1[256];
	char s2[256];
	puts("Boyer-Moore");
	printf("text : "); scanf("%s", s1);
	printf("pattern : "); scanf("%s", s2);
	
	idx = bm_match(s1, s2);
	if (idx == -1)
		puts("There is no pattern in text");
	else 
		printf("The String is matched from index %d\n", idx + 1);
		
	return 0;
 } 
 
/* [ Boyer-Moore 법 ]
	R. S. Boyer, J. S. Moore가 만든 Boyer-Moore법은 KMP법보다 효율이 더 좋습니다.
	이 알고리즘은 패턴의 마지막 문자부터 앞쪽으로 검사를 진행하면서 일치하지 않는 문자가 있으면 미리 준비한 표에 따라 패턴을 옮길 크기를 정합니다.
	
	텍스트 "ABDDCADZZASDADA"에서 패턴 "ABAC"를 검색하는 경우를 예로 들어 살펴보겠습니다.
	a처럼 텍스ㅡ와 패턴의 첫 번쨰 문자를 위, 아래로 겹치고 패턴의 마지막 문자 'C'를 검사합니다.
	텍스트의 'X'는 패턴에 없습니다.
	이 문자는 패턴에 아예 없는 문자이기 때문에 b ~ d처럼 패턴을 1 ~ 3 칸 옮겨도 문자열 "ABCX"와 패턴 안의 문자는 일치하지 않는다는 것을 알 수 있습니다.
	
	이와 같이 텍스트 안에서 패턴에 들어 있지 않은 문자를 찾으면 해당 위치까지의 문자는 건너뛸 수 있습니다.
	이 방법을 사용하면 b ~ d의 비교는 생략하고 패턴을 단숨에 4칸 뒤로 옮겨 그림 8-14의 상태가 됩니다.
	이 상태는 패턴의 마지막 문자 'C'와 텍스트의 'C'가 일치하기 때문에 패턴을 1칸 옮길 수 있습니다.
	그림 8-15를 보면서 계속 살펴보겠습니다.
	
	패턴의 문자 'A'는 텍스트의 'Z'와 다르기도 하지만 텍스트의 'Z'는 패턴에 없는 문자입니다.
	따라서 b, c처럼 패턴을 1 ~2칸 옮긴다 하더라도 패턴과 일치하지 않는 것을 알 수 있습니다.
	퍠턴을 한꺼번에 3칸 옮겨 그림 8-16의 상태로 만듭니다.
	
	이렇게 패턴의 길이를 n이라고 하면 현재 검사하고 있는 텍스트의 문자 위치로부터 `다음에 검사할 패턴의 마지막 문자위치`가 n만큼 떨어질 수 있도록 패턴을 옮기면 됩니다.
	예를 들어 그림 8-13에서는 패턴을 4칸 옮겼지만 이번에는 검사하고 있는 텍스트의 위치(6)로부터 4만큼 떨어진 위치(10)에서 검사를 시작하기 위해 패턴을 3칸 옮깁니다. 

	이렇게 옮긴 다음에 다시 검사를 시작해도 텍스트의 'A'와 패턴의 마지막 문자 'C'를 비교합니다.
	하지만 문자 'A'는 패턴의 1,3번째 인덱스에 들어 있습니다.
	이런 경우에는 b와 같이 패턴의 뒤쪽에 위치한 'A'가 텍스트와 위, 아래로 겹치도록 패턴을 1칸만 옮깁니다.
	d와 같은 방법으로 패턴의 첫 번째 문자인 'A'와 겹치도록 하기 위해 3칸을 옮기면 안 됩니다.
	패턴을 1칸만 옮겨민 다음의 그림 8-17과 같은 상태가 됩니다.
	이후 b의 상태에서 다시 패턴의 마지막 위치에서 순서대로 문자를 비교하면 모두 일치하기 떄문에 검색 성공입니다.
	
	그런데 Boyer-Moore 알고리즘도 각각의 문자를 만났을 때 패턴을 옮길 크기를 저장할 표(건너뛰기 표)를 미리 만들어야 합니다.
	패턴 문자열의 길이가 n일 때 옮길 크기는 아래와 같은 방법으로 결정합니다.
	
	패턴에 들어있지 않은 문자를 만난 경우
	1. 패턴을 옮길 크기는 n입니다. 그림 8-13을 다시 예르 들어 살펴보면 'X'는 패턴에 들어 있지 않으므로 4만큼 옮깁니다.
	
	패턴에 들어 있는 문자를 만난 경우
	1. 마지막에 나오는 위치의 인덱스가 k이면 패턴을 옮길 크기는 n - k - 1입니다.
	그림 8-16을 다시 예로 들면 'A'는 패턴의 두 곳에 들어 있지만 마지막 인덱스를 기준으로 하여 패턴을 1만큼(4-2-1) 옮깁니다.
	2. 같은 문자가 패턴 안에 중복해서 들어 있지 않다면 ("ABAC"의 'C'는 패턴 안에 1개만 들어 있습니다) 패턴을 옮길 크기는 n입니다. 
*/

/*
	strstr 함수
	C 언어는 문자열을 검색하는 표준 라이브러리 strstr 함수를 제공합니다.
	
	*****************************************************************************************************************
	* strstr 함수									   																*
	* 헤더	|	#include <string.h>					   																*
	* 형식 	|	char *strstr(const char *s1, const char *s2);		   												*
	* 해설	|	s1이 가리키는 문자열에서 s2가 가리키는 문자열과 일치하는(널 문자를 포함하지 않는) 문자열을 찾습니다.* 
	*		|	가장 앞쪽에 나오는 문자열을 찾습니다. 																*
	* 반환값|	찾아낸 문자열에 대한 포인터(첫 번째 문자에 대한 포인터)를 반환합니다.								*
	*		|	찾지 못하면 널 포인터를 반환합니다. 																*
	*		|	s2가 길이가 0인 문자열이면 s1을 반환합니다. 														*
	*****************************************************************************************************************

	strchr, strrchr 함수와 마찬가지로 찾은 위치의 인덱스가 아닌 그 문자에 대한 포인터를 반환한다는 점을 주의해야 합니다.
	예를 들어, 그림 8-11의 경우 텍스트의 앞쪽에서 3번째 문자인 'A'에 대한 포인터를 반환합니다.
	검색에 실패하면 널 포인터를 반환합니다. 
*/






























