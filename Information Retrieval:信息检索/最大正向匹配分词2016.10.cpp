//hashDictionary.h
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>

using namespace std;
//����ʵ乹���ϣ�ʵ� 
class hashDictionary
{
public:
    hashDictionary(); 
    ~hashDictionary();
    int searchWord(string w); //��map�ʵ��в��Ҵ�
    
private:
    string rowWord; //��ȡ�ʵ��ÿһ��
    string word; //����ÿ����
    map <string, int> hashword; 
    map <string, int >::iterator worditer; 
    typedef pair<string, int> spair;
};

hashDictionary::hashDictionary()
{
    ifstream dict("c:\\chendic.txt"); //����ʵ伯 
    if (!dict.is_open()) 
    {
        cerr << "file is not found " << endl;
        exit(-1);
    }
    while (getline(dict, rowWord)) // ����ʵ�ÿһ�еĴ���ӵ�map�ʵ���
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

# define MaxWordLength 14 // �������ʳ� 
# define Separator "  /  " // �ʷָ���� 

hashDictionary WordDic; //��ʼ��һ���ʵ�

//���ַ������������ƥ�䷨����
string maxMatch(string s1)
{
    string s2 = ""; //��ŷִʽ��
    while(!s1.empty())
    {
        int len =(int) s1.length(); //ȡ���봮���ȣ�������봮���ȴ������ʳ�,��ֻ�����ʳ���Χ�ڽ��д��� 
        if (len > MaxWordLength) 
        {
            len = MaxWordLength; 
        }
        
        string w = s1.substr(0, len); //�����봮��ߵ������ʳ����ȴ�ȡ����Ϊ��ѡ�ʣ���map�ʵ��в�����Ӧ�Ĵ� 
        int n = WordDic.searchWord(w); 
        
        while(len > 2 && n == 0) // ���δ�ҵ��ʣ���Ӻ�ѡ���ұ߼���һ�����֣���ʣ�µĲ�����Ϊ��ѡ�ʲ��������� 
        {
            len -= 2; 
            w = w.substr(0, len); 
            n = WordDic.searchWord(w);
        }
        
        s2 += w + Separator; //��ƥ��õ��Ĵ���ͬ�ʽ��Ǽӵ������ĩβ����s1-w����ʼ 
		s1 = s1.substr(w.length(), s1.length()); 
		
    }
    return s2;
}

//�������ַ��Ĵ���
string maxMatchMM (string s1)
{
    string s2 = ""; //��s2��ŷִʽ��
    int i;
    int dd;
    while(!s1.empty() )
    {
        unsigned char ch = (unsigned char)s1[0];
        if (ch < 128) 
        {
            i = 1;
            dd = (int)s1.length();
            while (i < dd && ((unsigned char)s1[i] < 128) && (s1[i] != 10) && (s1[i] != 13)) // s1[i]�����ǻ��з���س���
            { 
			  i++;
			}
              if ((ch != 32) && (ch != 10) && (ch != 13)) // ������ǿո���л�س���
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
            if (ch < 176) // ���ı��ȷǺ����ַ�
            {
                i = 0; dd = (int)s1.length();
                while(i < dd && ((unsigned char)s1[i] < 176) && ((unsigned char)s1[i] >= 161)&& (!((unsigned char)s1[i] == 161 && ((unsigned char)s1[i+1] >= 162 && (unsigned char)s1[i+1] <= 168))) && (!((unsigned char)s1[i] == 161 && ((unsigned char)s1[i+1] >= 171 && (unsigned char)s1[i+1] <= 191))) && (!(((unsigned char)s1[i] == 163 && ((unsigned char)s1[i+1] == 172 || (unsigned char)s1[i+1] == 161)) || (unsigned char)s1[i+1] == 168 || (unsigned char)s1[i+1] == 169 || (unsigned char)s1[i+1] == 186 || (unsigned char)s1[i+1] == 187 || (unsigned char)s1[i+1] == 191)))
                {
                    i = i + 2; // �ٶ�û�а������
                }
                    if (i == 0) { i = i + 2; }
                if (!(ch == 161 && (unsigned char)s1[1] == 161)) // ���������Ŀո�
                { s2+=s1.substr(0, i) + Separator; // �����ķǺ���˫�ֽ��ַ������������
                } s1 = s1.substr(i, dd); continue; } } // ���´����ִ�
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
string rowWord; //���ڱ�������Ͽ��ж����ÿһ��
string line; //�������ÿһ�еĽ��
        
        ifstream file("c:\\100.txt"); // �������ļ�
        if (!file.is_open())
        {
            cerr << "file is not found" << endl; 
            exit(-1); 
        } 
        
        ofstream outfile("testResult.txt"); //����ִ��ļ� 
        if (!outfile.is_open()) 
        { 
            cerr << "failed to ofstream"<< endl; 
            exit(-1); 
        } 
        
        while (getline(file, rowWord))    //�������Ͽ��е�ÿһ�в����������ƥ�䷨���� 
        { 
            line = rowWord; 
            line = maxMatchMM(line); // ���÷ִʺ������зִʴ��� 
            outfile << line << endl; // ���ִʽ��д��Ŀ���ļ� 
        } 
        cout<<"Done!"<<endl;
        return 0; 
}