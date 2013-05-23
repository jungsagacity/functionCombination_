#include <stdio.h>
#include <string>
#include <vector>

using namespace std;


/*
	类名	：	CStringProcess
	功能	：	字符串处理
	作者	：	吴军
	修改	：	{2013.5.20} 第一次创建

*/
class CStringProcess
{
public:
	static vector<string> split(const string& src, string delimit, string null_subst="");//对字符串进行分割

};

	/*
	方法	：	split
	功能	：	字符串分割
	参数	：	{const string& src} 输入的待处理的字符串;
			{string delimit} 分隔符,可以是单个字符，也可以是多个字符组成的字符串;
			{string null_subst=""} 分割出来的空字符串所采用的表示方式，默认采用空字符串表示;
	返回	：	{vector<string>} 分割后按照顺序存放在字符串向量中;
	
	作者	：	吴军
	修改	：	{2013.5.20 第一次创建};

	*/
vector<string> CStringProcess::split(const string& src, string delimit, string null_subst)
{
	vector<string> v;//存放分割后的结果
	
	if(src.empty() || delimit.empty())//如果字符串或者分隔符为空，则返回空字符串向量组
	{
		return v;
	}

	
	int delimit_len = delimit.size();//分隔符长度
	long index = -1,//当前分隔符的位置 
		 last_search_position = 0;//上次搜索位置

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

	string last_substring = src.substr(last_search_position);//最后一个分隔符后所有的字符串
	v.push_back( last_substring.empty() ? null_subst : last_substring);//若为空，则使用null_subst代替

	return v;	
}

