/* ���ڿ��� ���(�����͸� ���)�մϴ�. */
#include <stdio.h>

int main (void)
{
	char *pt = "12345";
	printf("������ pt�� \"%s\"��(��) ����ŵ�ϴ�.\n", pt);
	
	return 0;
}

/* [ �����Ϳ� ���ڿ� ]
	���� C ��� ���α׷������� �迭�� �ƴ϶� �����ͷ� ���ڿ��� ��Ÿ���ϴ�.
	�ǽ� 8-4�� ���鼭 ���캸�ڽ��ϴ�.
	������ ������ pt�� �ʱ�ȭ ��ҷ� ���ڿ� ���ͷ� "12345"�� �ݴϴ�.
	���ڿ� ���ͷ��� ���Ͽ� ��� ���� �� ���ڿ� ���ͷ��� ù ��° ���ڿ� ���� 
	�������̹Ƿ� pt�� "12345"�� ����ִ� �޸� ������ ù ��° ���� '1'�� ����Ű�� �ʱ�ȭ�˴ϴ�.
	
	02�忡�� ������ p�� ����Ű�� �迭�� ��ҷκ��� i��ŭ �ڿ� �ִ� ��Ҵ� ÷�� ������([])�� ����� �� p[i]�� ���� ������� ������ �� �ִٰ� �߽��ϴ�.
	�׷��Ƿ� ���ڿ� ���ͷ� "12345"�� ���� '1', '2', '3', '4', '5'�� ������� pt[0], pt[1], pt[2], pt[3], pt[4]�� ���� pt �迭ó�� ����� �� �ֽ��ϴ�.
	�迭�� ���� ���ڿ��� �����Ϳ� ���� ���ڿ��� ���� �޸��� ������ ũ�⸦ ���ϸ� ������ �����ϴ�.
	
	char st[] = "12345"; 	//�迭�� ���� ���ڿ��� ũ��� 6����Ʈ
	char *pt = "12345"; 	//�����Ϳ� ���� ���ڿ��� ũ���sizeof(char *) + 6����Ʈ
	
	�迭�� ������ ���ڿ��� 6����Ʈ�� �޸� ������ �����ϴ�.
	������ �����ͷ� ǥ���� ���ڿ��� ���ڿ� ���ͷ��� �����ϱ� ���� ���� �ܿ��� pt�� ���� �޸� ������ �� �ʿ��մϴ�.
	��, pt�� ���� ������ sizeof(char *) ����Ʈ�� �� ���ڿ� ���ͷ��� ���� ������ sizeof("12345")����Ʈ��ŭ �޸� ������ �ʿ��մϴ�.
	�ٽ� ���� �����ͷ� ǥ���� ���ڿ��� �迭�� ������ ���ڿ����� �� ���� �޸� ������ �����մϴ�.
	
	�ǽ� 8-5�� ���ڿ� ���ͷ��� ����Ű�� �� �������� ���� ���� ��ȯ�ϴ� ���α׷��Դϴ�.	
*/