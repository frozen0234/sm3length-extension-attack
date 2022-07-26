#include "sm3.h"
#include <iostream>
#include <string>
#include <cmath>
using namespace std;
string IV = "7380166F4914B2B9172442D7DA8A0600A96F30BC163138AAE38DEE4DB0FB0E4E";
string padding(string s) {//�����ݽ������ 
	string res = "";
	for (int i = 0; i < s.size(); i++) {//���Ƚ�����ֵת��Ϊ16�����ַ���
		res += DTH((int)s[i]);
	}
	cout << "�����ַ�����ASCII���ʾΪ��" << endl;
	for (int i = 0; i < res.size(); i++) {
		cout << res[i];
		if ((i + 1) % 8 == 0) {
			cout << "  ";
		}
		if ((i + 1) % 64 == 0 || (i + 1) == res.size()) {
			cout << endl;
		}
	}
	cout << endl;
	int res_length = res.size() * 4;//��¼�ĳ���Ϊ2�����µĳ���
	res += "8";//�ڻ�õ����ݺ�����1����16�������൱�������8
	while (res.size() % 128 != 112) {
		res += "0";//��0���������
	}
	string res_len = DTH(res_length);//���ڼ�¼���ݳ��ȵ��ַ���
	while (res_len.size() != 16) {
		res_len = "0" + res_len;
	}
	res += res_len;
	return res;
}
string ModAdd(string str1, string str2) {//mod 2^32����ĺ���ʵ��
	string res1 = HTB(str1);
	string res2 = HTB(str2);
	char temp = '0';
	string res = "";
	for (int i = res1.size() - 1; i >= 0; i--) {
		res = binXor(binXor(res1[i], res2[i]), temp) + res;
		if (binAnd(res1[i], res2[i]) == '1') {
			temp = '1';
		}
		else {
			if (binXor(res1[i], res2[i]) == '1') {
				temp = binAnd('1', temp);
			}
			else {
				temp = '0';
			}
		}
	}
	return BTH(res);
}

string P1(string str) {//ʵ���û�����P1��X��
	return XOR(XOR(str, LeftShift(str, 15)), LeftShift(str, 23));
}

string P0(string str) {//ʵ���û�����P0��X��
	return XOR(XOR(str, LeftShift(str, 9)), LeftShift(str, 17));
}

string T(int j) {//����Tj����ֵ�ĺ���ʵ��
	if (0 <= j && j <= 15) {
		return "79CC4519";
	}
	else {
		return "7A879D8A";
	}
}

string FF(string X, string Y, string Z, int j) {//ʵ�ֲ�������FF����
	if (0 <= j && j <= 15) {
		return XOR(XOR(X, Y), Z);
	}
	else {
		return OR(OR(AND(X, Y), AND(X, Z)), AND(Y, Z));
	}
}

string GG(string X, string Y, string Z, int j) {//ʵ�ֲ�������GG����
	if (0 <= j && j <= 15) {
		return XOR(XOR(X, Y), Z);
	}
	else {
		return OR(AND(X, Y), AND(NOT(X), Z));
	}
}
string extension(string str) {//��Ϣ��չ����
	string res = str;//�ַ������ʹ洢ǰ68λ�洢��չ��Wֵ
	for (int i = 16; i < 68; i++) {//���ݹ�ʽ���ɵ�17λ����68λ��Wֵ
		res += XOR(XOR(P1(XOR(XOR(res.substr((i - 16) * 8, 8), res.substr((i - 9) * 8, 8)), LeftShift(res.substr((i - 3) * 8, 8), 15))), LeftShift(res.substr((i - 13) * 8, 8), 7)), res.substr((i - 6) * 8, 8));
	}
	for (int i = 0; i < 64; i++) {//���ݹ�ʽ����64λW'ֵ
		res += XOR(res.substr(i * 8, 8), res.substr((i + 4) * 8, 8));
	}
	return res;
}

string compress(string str1, string str2) {//��Ϣѹ������
	string IV = str2;
	string A = IV.substr(0, 8), B = IV.substr(8, 8), C = IV.substr(16, 8), D = IV.substr(24, 8), E = IV.substr(32, 8), F = IV.substr(40, 8), G = IV.substr(48, 8), H = IV.substr(56, 8);
	string SS1 = "", SS2 = "", TT1 = "", TT2 = "";
	for (int j = 0; j < 64; j++) {
		SS1 = LeftShift(ModAdd(ModAdd(LeftShift(A, 12), E), LeftShift(T(j), (j % 32))), 7);
		SS2 = XOR(SS1, LeftShift(A, 12));
		TT1 = ModAdd(ModAdd(ModAdd(FF(A, B, C, j), D), SS2), str1.substr((j + 68) * 8, 8));
		TT2 = ModAdd(ModAdd(ModAdd(GG(E, F, G, j), H), SS1), str1.substr(j * 8, 8));
		D = C;
		C = LeftShift(B, 9);
		B = A;
		A = TT1;
		H = G;
		G = LeftShift(F, 19);
		F = E;
		E = P0(TT2);
	}
	string res = (A + B + C + D + E + F + G + H);
	cout << endl;
	return res;
}

string iteration(string str,string b) {//����ѹ������ʵ��
	int num = str.size() / 128;
	//string V = "7380166F4914B2B9172442D7DA8A0600A96F30BC163138AAE38DEE4DB0FB0E4E";
	string V = b;
	string B = "", extensionB = "", compressB = "";
	for (int i = 0; i < num; i++) {
		B = str.substr(i * 128, 128);
		extensionB = extension(B);
		compressB = compress(extensionB, V);
		V = XOR(V, compressB);
	}
	return V;
}
int main() {//������
	//string str0 = "abcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcd";
	string r1 = "114514";
	string r2 = "hutao";
	string m = padding(r1);
	string x1 = iteration(m,IV);
	string x2 = iteration(m + r2,IV);

	cout << "x2:" << endl;
	for (int i = 0; i < 8; i++)
		cout << x2.substr(i * 8, 8);

	string x3 = iteration(r2, x1);
	cout << "h3:" << endl;
	for (int i = 0; i < 8; i++)
		cout << x3.substr(i * 8, 8);
	cout << endl << endl;

	if (x2 == x3)
		cout << "�����ɹ�" << endl;
}

