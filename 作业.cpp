#include<iostream>
#include <iomanip>
using namespace std;
struct SJF
{
	int N;
	double Htime;//�ύ
	double Rtime;//ִ��
	double Stime;//��ʼ
	double Ctime;//���
	double Ztime;//��ת
	double DZtime;//��Ȩ��ת
};
#define t 4//��ҵ����
double sumZtime;
double sumDZtime;
struct SJF F[t], temp;
void Fin() {//����
	for (int i = 0; i < t; i++) {
		cout << "�������ύʱ��: ";
		cin >> F[i].Htime;
		cout << "������ִ��ʱ��: ";
		cin >> F[i].Rtime;
	}
	cout << endl;
}
void Px() {  //�ύʱ����������
 
	for (int i = 0; i < t - 1; i++) {
		for (int j = 0; j < t - i - 1; j++) {
			if (F[j + 1].Htime < F[j].Htime) {
				temp = F[j + 1];
				F[j + 1] = F[j];
				F[j] = temp;
			}
		}
	}
}
void Px1(int a, int b) {  //ִ��ʱ����������
	if (a == b)  return;
	int c = 0;
	for (int i = a; i < b; i++, c++) {  //���a-->b��ð������
		for (int j = a; j < b - c; j++) {
			if (F[j + 1].Rtime < F[j].Rtime) {
				temp = F[j + 1];
				F[j + 1] = F[j];
				F[j] = temp;
 
			}
		}
	}
}
void Get0(int i) {  //�����ʱ�䡢��תʱ�䡢��Ȩ��תʱ��
	F[i].Ctime = F[i].Stime + F[i].Rtime;
	F[i].Ztime = F[i].Ctime - F[i].Htime;
	F[i].DZtime = F[i].Ztime / F[i].Rtime;
}
void Get1() {  //�������һ����ҵ������ʱ��
	F[0].Stime = F[0].Htime;
	Get0(0);
}
void Get2(int a, int j) {  //��ʼʱ��=��һ����ҵ�����ʱ��
	for (; a < j; a++) {
		F[a].Stime = F[a - 1].Ctime;
		Get0(a);
	}
}
void Get3(int i) {//��ʼʱ��=����ҵ���ύʱ��
	F[i].Stime = F[i].Htime;
	Get0(i);
}
void Get() {
	int i = 1;  //�ӵڶ�����ҵ��ʼ����һ����ҵ���±�Ϊ0��
	int j;
	while (F[i].Htime <= F[0].Ctime) {  //ֱ���ҵ��ύʱ����ڵ�һ����ҵ�����ʱ��
		i++;
	}//����ѭ����i��ҵ�ύʱ����ڵ�һ����ҵ�����ʱ��
	if (i != 1) { Px1(1, i - 1); Get2(1, i); }  //����ִ��ʱ����Դ���ʣ��ʱ��      (i=2�����ֻ��i=1���ύʱ��>��һ����ҵ�����ʱ��)
	while (i < t) {
		j = i;//j���ڼ�¼iֵ
		//-----------------------------------------------//��������ͬ�Ĺ��̣�ֻ�ǱȽϵĶ���ͬ
		while (F[i].Htime <= F[j - 1].Ctime && i < t) {
			i++;
		}
		if (i != j) { Px1(j, i - 1); Get2(j, i); }
		//-----------------------------------------------//
		if (F[i].Htime > F[i - 1].Ctime) {
			Get3(i); i++;
		}
	}
}
void print() {
	cout << setiosflags(ios::fixed) << setprecision(2);//����2λС��
	cout << "SJF�����㷨��" << endl;
	cout << "��ҵ\t     �ύʱ��\t     ִ��ʱ��\t     ��ʼʱ��\t     ���ʱ��\t     ��תʱ��\t     ��Ȩ��תʱ��\t     " << endl;
	for (int i = 0; i < t; i++) {
		F[i].N = i + 1;
		cout << F[i].N << "\t\t" << F[i].Htime << "\t\t" << F[i].Rtime << "\t\t" <<
			F[i].Stime << "\t\t" << F[i].Ctime << "\t\t" << F[i].Ztime << "\t\t" << F[i].DZtime << "\n";
	}
	for (int j = 0; j < t; j++) {
		sumZtime += F[j].Ztime;
		sumDZtime += F[j].DZtime;
	}
	cout << setiosflags(ios::fixed) << setprecision(3);//����3λС��
	cout << "ƽ����תʱ�䣺 ";
	cout << sumZtime / t << endl;
	cout << "ƽ����Ȩ��תʱ�䣺 ";
	cout << sumDZtime / t << endl;
}
int main() {
	Fin();
	Px();
	Get1();
	Get();
	Px();
	print();
}
