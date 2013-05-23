#include <string>
#include <vector>

using namespace std;

/*
struct  cp
{
  string an,//申请号
  string ad,//申请日
  string pn	,//公开/公告号
  string apd,//公开日
  string spn,//公告号
  string spd,//优先申请日
  string dpn,//分案原申请号
  string gpn,//授权公告号
  string gpd,//授权公告日
  string qd,//授权日
  string di,//颁证日
  string ic1,//主分类号
  string ic2,//副分类号
  string wg,//外观分类号
  string ct,//范畴分类号
  string inn,//发明（设计）人
  string pa,//申请（专利权）人
  string aa,//通讯地址
  string ti,//发明名称
  string ab,//文摘
  string ac,//权利要求
  string pr,//优先权项
  string sdn,//审定公告号
  string epd,//审定公告日
  string ian,//国际申请
  string ipn,//国际公布
  string den,//进入国家日期
  string co,//国别省市代码
  string agt,//代理人
  string agc,//代理机构
  string su,//说明书光盘卷
  string du,//说明书页数
  string pd,//公开/公告日
  string icc,//引得码
  string icc2,//不连用引得码
  string ic3,//附加分类
  string ls,//法律状态
  string le,//法律变更事项
  string dlp,//最终结案结果
  string dh,//代理机构地址
}chinesePatent;
*/


/*
	类名	：	CPatentStruct
	功能	：	存放专利数据字段结构信息
	作者	：	吴军
	修改	：	{2013.5.20 第一次创建}

*/

class CPatentStruct
{
public:

	vector<string> patentStruct;

	CPatentStruct(char c)
	{
		switch(c)
		{
			case 'C':
				CPatentStruct::patentStruct.push_back("an");//1 申请号
				CPatentStruct::patentStruct.push_back("ad");//2 申请日
				CPatentStruct::patentStruct.push_back("pn");//3 公开/公告号
				CPatentStruct::patentStruct.push_back("apd");//4 公开日
				CPatentStruct::patentStruct.push_back("spn");//5 公告号
				CPatentStruct::patentStruct.push_back("spd");//6 优先申请日
				CPatentStruct::patentStruct.push_back("dpn");//7 分案原申请号
				CPatentStruct::patentStruct.push_back("gpn");//8 授权公告号
				CPatentStruct::patentStruct.push_back("gpd");//9 授权公告日
				CPatentStruct::patentStruct.push_back("qd");//10授权日
				CPatentStruct::patentStruct.push_back("di");//11 颁证日
				CPatentStruct::patentStruct.push_back("ic1");//12 主分类号
				CPatentStruct::patentStruct.push_back("ic2");//13副分类号
				CPatentStruct::patentStruct.push_back("wg");//14 外观分类号
				CPatentStruct::patentStruct.push_back("ct");//15 范畴分类号
				CPatentStruct::patentStruct.push_back("inn");//16 发明（设计）人
				CPatentStruct::patentStruct.push_back("pa");//17 申请（专利权）人
				CPatentStruct::patentStruct.push_back("aa");//18 通讯地址
				CPatentStruct::patentStruct.push_back("ti");//19 发明名称
				CPatentStruct::patentStruct.push_back("ab");//20 文摘
				CPatentStruct::patentStruct.push_back("ac");//21 权利要求
				CPatentStruct::patentStruct.push_back("pr");//22 优先权项
				CPatentStruct::patentStruct.push_back("sdn");//23 审定公告号
				CPatentStruct::patentStruct.push_back("epd");//24 审定公告日
				CPatentStruct::patentStruct.push_back("ian");//25 国际申请
				CPatentStruct::patentStruct.push_back("ipn");//26 国际公布
				CPatentStruct::patentStruct.push_back("den");//27 进入国家日期
				CPatentStruct::patentStruct.push_back("co");//28 国别省市代码
				CPatentStruct::patentStruct.push_back("agt");//29 代理人
				CPatentStruct::patentStruct.push_back("agc");//30 代理机构
				CPatentStruct::patentStruct.push_back("su");//31 说明书光盘卷
				CPatentStruct::patentStruct.push_back("du");//32 说明书页数
				CPatentStruct::patentStruct.push_back("pd");//33 公开/公告日
				CPatentStruct::patentStruct.push_back("icc");//34 引得码
				CPatentStruct::patentStruct.push_back("icc2");//35 不连用引得码
				CPatentStruct::patentStruct.push_back("ic3");//36 附加分类
				CPatentStruct::patentStruct.push_back("ls");//37 法律状态
				CPatentStruct::patentStruct.push_back("le");//38 法律变更事项
				CPatentStruct::patentStruct.push_back("dlp");//39 最终结案结果
				CPatentStruct::patentStruct.push_back("dh");//40 代理机构地址

				break;

			default://欧美专利采样一样的格式保存
				CPatentStruct::patentStruct.push_back("an");//申请号
				CPatentStruct::patentStruct.push_back("ad");//申请日
				CPatentStruct::patentStruct.push_back("pn");//专利号
				CPatentStruct::patentStruct.push_back("pd");//公布日
				CPatentStruct::patentStruct.push_back("inn");//发明人
				CPatentStruct::patentStruct.push_back("pa");//专利权人
				CPatentStruct::patentStruct.push_back("ic1");//国际主分类
				CPatentStruct::patentStruct.push_back("ic2");//国际副分类
				CPatentStruct::patentStruct.push_back("ti");//发明名称
				CPatentStruct::patentStruct.push_back("ab");//文摘
				CPatentStruct::patentStruct.push_back("ac");//权利要求
				CPatentStruct::patentStruct.push_back("pr");//优先权项
				CPatentStruct::patentStruct.push_back("rd");//优先权日
				CPatentStruct::patentStruct.push_back("fa");//同族专利项
				CPatentStruct::patentStruct.push_back("co");//国省代码
				CPatentStruct::patentStruct.push_back("ds");//指定国
				CPatentStruct::patentStruct.push_back("pcp");//PCT公开
				CPatentStruct::patentStruct.push_back("pcn");//PCT申请
				CPatentStruct::patentStruct.push_back("pcm");//PCT信息
				CPatentStruct::patentStruct.push_back("rno");//再版原专利
				CPatentStruct::patentStruct.push_back("dis");//分案申请
				CPatentStruct::patentStruct.push_back("frf");//国外参考文献
				CPatentStruct::patentStruct.push_back("urf");//美国参考文献
				CPatentStruct::patentStruct.push_back("orp");//非专利参考文献
				CPatentStruct::patentStruct.push_back("red");//相关信息
				CPatentStruct::patentStruct.push_back("icc");//引得码
				CPatentStruct::patentStruct.push_back("ec1");//欧洲主分类
				CPatentStruct::patentStruct.push_back("ec2");//欧洲副分类
				CPatentStruct::patentStruct.push_back("usc1");//美国主分类
				CPatentStruct::patentStruct.push_back("usc2");//美国副分类
				CPatentStruct::patentStruct.push_back("fi1");//日本主分类
				CPatentStruct::patentStruct.push_back("fi2");//日本副分类
				CPatentStruct::patentStruct.push_back("wg");//外观分类
				CPatentStruct::patentStruct.push_back("exp");//审查员
				CPatentStruct::patentStruct.push_back("agt");//代理人
				CPatentStruct::patentStruct.push_back("su");//光盘卷号
				CPatentStruct::patentStruct.push_back("ic3");//附加分类
				CPatentStruct::patentStruct.push_back("won");//WO申请号
				CPatentStruct::patentStruct.push_back("icc2");//不连用引得码
				CPatentStruct::patentStruct.push_back("dh");//主题导航

				break;
		}
	}

};
