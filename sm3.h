#include <iostream>
#include <string>
#include <cmath>
using namespace std;
//�������Ƴ��Ȳ���Ϊ4�ı���
string BZ(string s)
{
	int l = s.size();
	while (l % 4 != 0) {//��Ϊÿ��λ�����������ܹ���Ϊһ��ʮ�������������Խ�������������ת��Ϊ4�ı���
		s = "0" + s;//���λ��0ֱ������Ϊ4�ı�������
	}
	return s;
}
//������ת��Ϊʮ�����ƺ���ʵ��
string BTH(string s) {
	s = BZ(s);//�������Ƴ��Ȳ���Ϊ4�ı���
	string h = "";//�����洢������ɵ�ʮ��������
	int D = 0;//�����洢ÿ����λ����������ʮ����ֵ
	int l = s.size();
	for (int i = 0; i < l; i += 4) {
		D = (s[i] - '0') * 8 + (s[i + 1] - '0') * 4 + (s[i + 2] - '0') * 2 + (s[i + 3] - '0') * 1;//4λ����������ʮ����
		if (D < 10) {
			h += to_string(D);
		}
		else {
			h += 'A' + (D - 10);
		}
	}
	return h;
}

//ʮ������ת��Ϊ�����ƺ���ʵ��
string HTB(string s) {
	int l = s.size();
	string b = "";
	string table[16] = { "0000","0001","0010","0011","0100","0101","0110","0111","1000","1001","1010","1011","1100","1101","1110","1111" };
	for (int i = 0; i < l; i++) {
		if (s[i] >= 'A' && s[i] <= 'F') {
			b += table[s[i] - 'A' + 10];
		}
		else {
			b += table[s[i] - '0'];
		}
	}
	return b;
}

//������ת��Ϊʮ���Ƶĺ���ʵ��
int BTD(string s) {
	int d = 0;
	for (int i = 0; i < s.size(); i++) {
		d += (s[i] - '0') * pow(2, s.size() - i - 1);
	}
	return d;
}

//ʮ����ת��Ϊ�����Ƶĺ���ʵ��
string DTB(int s) {
	string b = "";
	while (s >= 1) {
		b = to_string(s % 2) + b;
		s = s / 2;
	}
	return b;
}

//ʮ������ת��Ϊʮ���Ƶĺ���ʵ��
int HTD(string s) {
	int d = 0;
	for (int i = 0; i < s.size(); i++) {
		if (s[i] >= 'A' && s[i] <= 'F') {
			d += (s[i] - 'A' + 10) * pow(16, s.size() - i - 1);
		}
		else {
			d += (s[i] - '0') * pow(16, s.size() - i - 1);
		}
	}
	return d;
}

//ʮ����ת��Ϊʮ�����Ƶĺ���ʵ��
string DTH(int s) {
	string h = "";
	int t = 0;
	while (s >= 1) {
		t = s % 16;
		if (t < 10 && t >= 0) {
			h = to_string(t) + h;
		}
		else {
			h += ('A' + (t - 10));
		}
		s = s / 16;
	}
	return h;
}
string LeftShift(string str, int len) {//ʵ��ѭ������lenλ����
	string res = HTB(str);
	res = res.substr(len) + res.substr(0, len);
	return BTH(res);
}

string XOR(string str1, string str2) {//ʵ��������
	string res1 = HTB(str1);
	string res2 = HTB(str2);
	string res = "";
	for (int i = 0; i < res1.size(); i++) {
		if (res1[i] == res2[i]) {
			res += "0";
		}
		else {
			res += "1";
		}
	}
	return BTH(res);
}

string AND(string str1, string str2) {//ʵ�������
	string res1 = HTB(str1);
	string res2 = HTB(str2);
	string res = "";
	for (int i = 0; i < res1.size(); i++) {
		if (res1[i] == '1' && res2[i] == '1') {
			res += "1";
		}
		else {
			res += "0";
		}
	}
	return BTH(res);
}

string OR(string str1, string str2) {//ʵ�ֻ����
	string res1 = HTB(str1);
	string res2 = HTB(str2);
	string res = "";
	for (int i = 0; i < res1.size(); i++) {
		if (res1[i] == '0' && res2[i] == '0') {
			res += "0";
		}
		else {
			res += "1";
		}
	}
	return BTH(res);
}

string NOT(string str) {//ʵ�ַǲ���
	string res1 = HTB(str);
	string res = "";
	for (int i = 0; i < res1.size(); i++) {
		if (res1[i] == '0') {
			res += "1";
		}
		else {
			res += "0";
		}
	}
	return BTH(res);
}

char binXor(char str1, char str2) {//ʵ�ֵ����ص�������
	return str1 == str2 ? '0' : '1';
}

char binAnd(char str1, char str2) {//ʵ�ֵ����ص������
	return (str1 == '1' && str2 == '1') ? '1' : '0';
}
