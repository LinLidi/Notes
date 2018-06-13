//hashDictionary.h
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>

using namespace std;
//读入词典构造哈希词典 
class hashDictionary
{
public:
    hashDictionary(); 
    ~hashDictionary();
    int searchWord(string w); //在map词典中查找词
    
private:
    string rowWord; //读取词典的每一行
    string word; //保存每个词
    map <string, int> hashword; 
    map <string, int >::iterator worditer; 
    typedef pair<string, int> spair;
};

hashDictionary::hashDictionary()
{
    ifstream dict("c:\\chendic.txt"); //读入词典集 
    if (!dict.is_open()) 
    {
        cerr << "file is not found " << endl;
        exit(-1);
    }
    while (getline(dict, rowWord)) // 读入词典每一行的词添加到map词典中
    {
        istringstream istr(rowWord);
        istr >> word; 
        hashword.insert(spair(word, 1)); 
    }
}

hashDictionary::~hashDictionary()
{
}

int hashDictionary::searchWord(string w)
{
    if (hashword.find(w) != hashword.end())
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

//main.cpp
//#include "Dictionary.h"

# define MaxWordLength 14 // 定义最大词长 
# define Separator "  /  " // 词分隔标记 

hashDictionary WordDic; //初始化一个词典

//对字符串用最大正向匹配法处理
string maxMatch(string s1)
{
    string s2 = ""; //存放分词结果
    while(!s1.empty())
    {
        int len =(int) s1.length(); //取输入串长度，如果输入串长度大于最大词长,则只在最大词长范围内进行处理 
        if (len > MaxWordLength) 
        {
            len = MaxWordLength; 
        }
        
        string w = s1.substr(0, len); //将输入串左边等于最大词长长度串取出作为候选词，在map词典中查找相应的词 
        int n = WordDic.searchWord(w); 
        
        while(len > 2 && n == 0) // 如果未找到词，则从候选词右边减掉一个汉字，将剩下的部分作为候选词并继续查找 
        {
            len -= 2; 
            w = w.substr(0, len); 
            n = WordDic.searchWord(w);
        }
        
        s2 += w + Separator; //将匹配得到的词连同词界标记加到输出串末尾，从s1-w处开始 
		s1 = s1.substr(w.length(), s1.length()); 
		
    }
    return s2;
}

//对特殊字符的处理
string maxMatchMM (string s1)
{
    string s2 = ""; //用s2存放分词结果
    int i;
    int dd;
    while(!s1.empty() )
    {
        unsigned char ch = (unsigned char)s1[0];
        if (ch < 128) 
        {
            i = 1;
            dd = (int)s1.length();
            while (i < dd && ((unsigned char)s1[i] < 128) && (s1[i] != 10) && (s1[i] != 13)) // s1[i]不能是换行符或回车符
            { 
			  i++;
			}
              if ((ch != 32) && (ch != 10) && (ch != 13)) // 如果不是空格或换行或回车符
            {
			  s2 += s1.substr(0,i) + Separator;
            }
            else
            { 
              if(ch == 10 || ch == 13 || ch == 32) 
                {
                    s2 += s1.substr(0, i);
                }
            }
            s1 = s1.substr(i,dd); 
			continue;
        } 
		else
        {
            if (ch < 176) // 中文标点等非汉字字符
            {
                i = 0; dd = (int)s1.length();
                while(i < dd && ((unsigned char)s1[i] < 176) && ((unsigned char)s1[i] >= 161)&& (!((unsigned char)s1[i] == 161 && ((unsigned char)s1[i+1] >= 162 && (unsigned char)s1[i+1] <= 168))) && (!((unsigned char)s1[i] == 161 && ((unsigned char)s1[i+1] >= 171 && (unsigned char)s1[i+1] <= 191))) && (!(((unsigned char)s1[i] == 163 && ((unsigned char)s1[i+1] == 172 || (unsigned char)s1[i+1] == 161)) || (unsigned char)s1[i+1] == 168 || (unsigned char)s1[i+1] == 169 || (unsigned char)s1[i+1] == 186 || (unsigned char)s1[i+1] == 187 || (unsigned char)s1[i+1] == 191)))
                {
                    i = i + 2; // 假定没有半个汉字
                }
                    if (i == 0) { i = i + 2; }
                if (!(ch == 161 && (unsigned char)s1[1] == 161)) // 不处理中文空格
                { s2+=s1.substr(0, i) + Separator; // 其他的非汉字双字节字符可能连续输出
                } s1 = s1.substr(i, dd); continue; } } // 以下处理汉字串
        i = 2; dd = (int)s1.length(); while(i < dd && (unsigned char)s1[i] >= 176)
                {
                    i += 2;
                }
                s2 += maxMatch(s1.substr(0, i));
                s1 = s1.substr(i,dd);
            }
        
        return s2;
    }

int main(int argc, char *argv[])
{
string rowWord; //用于保存从语料库中读入的每一行
string line; //用于输出每一行的结果
        
        ifstream file("c:\\100.txt"); // 打开输入文件
        if (!file.is_open())
        {
            cerr << "file is not found" << endl; 
            exit(-1); 
        } 
        
        ofstream outfile("testResult.txt"); //输出分词文件 
        if (!outfile.is_open()) 
        { 
            cerr << "failed to ofstream"<< endl; 
            exit(-1); 
        } 
        
        while (getline(file, rowWord))    //读入语料库中的每一行并用最大正向匹配法处理 
        { 
            line = rowWord; 
            line = maxMatchMM(line); // 调用分词函数进行分词处理 
            outfile << line << endl; // 将分词结果写入目标文件 
        } 
        cout<<"Done!"<<endl;
        return 0; 
}