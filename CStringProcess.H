#include <stdio.h>
#include <string>
#include <vector>

using namespace std;


/*
	����	��	CStringProcess
	����	��	�ַ�������
	����	��	���
	�޸�	��	{2013.5.20} ��һ�δ���

*/
class CStringProcess
{
public:
	static vector<string> split(const string& src, string delimit, string null_subst="");//���ַ������зָ�

};

	/*
	����	��	split
	����	��	�ַ����ָ�
	����	��	{const string& src} ����Ĵ��������ַ���;
			{string delimit} �ָ���,�����ǵ����ַ���Ҳ�����Ƕ���ַ���ɵ��ַ���;
			{string null_subst=""} �ָ�����Ŀ��ַ��������õı�ʾ��ʽ��Ĭ�ϲ��ÿ��ַ�����ʾ;
	����	��	{vector<string>} �ָ����˳�������ַ���������;
	
	����	��	���
	�޸�	��	{2013.5.20 ��һ�δ���};

	*/
vector<string> CStringProcess::split(const string& src, string delimit, string null_subst)
{
	vector<string> v;//��ŷָ��Ľ��
	
	if(src.empty() || delimit.empty())//����ַ������߷ָ���Ϊ�գ��򷵻ؿ��ַ���������
	{
		return v;
	}

	
	int delimit_len = delimit.size();//�ָ�������
	long index = -1,//��ǰ�ָ�����λ�� 
		 last_search_position = 0;//�ϴ�����λ��

	while((index = src.find( delimit, last_search_position )) != string::npos)
	{
		if( index == last_search_position )
		{
			v.push_back(null_subst);
		}else
		{
			string substring = src.substr(last_search_position, index - last_search_position);
			v.push_back(substring);			
		}

		last_search_position = index + delimit_len;

	}

	string last_substring = src.substr(last_search_position);//���һ���ָ��������е��ַ���
	v.push_back( last_substring.empty() ? null_subst : last_substring);//��Ϊ�գ���ʹ��null_subst����

	return v;	
}
