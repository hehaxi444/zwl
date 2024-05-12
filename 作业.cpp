#include<iostream>
#include <iomanip>
using namespace std;
struct SJF
{
	int N;
	double Htime;//提交
	double Rtime;//执行
	double Stime;//开始
	double Ctime;//完成
	double Ztime;//周转
	double DZtime;//带权周转
};
#define t 4//作业个数
double sumZtime;
double sumDZtime;
struct SJF F[t], temp;
void Fin() {//输入
	for (int i = 0; i < t; i++) {
		cout << "请输入提交时间: ";
		cin >> F[i].Htime;
		cout << "请输入执行时间: ";
		cin >> F[i].Rtime;
	}
	cout << endl;
}
void Px() {  //提交时间升序排序
 
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
void Px1(int a, int b) {  //执行时间升序排序
	if (a == b)  return;
	int c = 0;
	for (int i = a; i < b; i++, c++) {  //序号a-->b的冒泡排序
		for (int j = a; j < b - c; j++) {
			if (F[j + 1].Rtime < F[j].Rtime) {
				temp = F[j + 1];
				F[j + 1] = F[j];
				F[j] = temp;
 
			}
		}
	}
}
void Get0(int i) {  //求完成时间、周转时间、带权周转时间
	F[i].Ctime = F[i].Stime + F[i].Rtime;
	F[i].Ztime = F[i].Ctime - F[i].Htime;
	F[i].DZtime = F[i].Ztime / F[i].Rtime;
}
void Get1() {  //先求出第一个作业的所有时间
	F[0].Stime = F[0].Htime;
	Get0(0);
}
void Get2(int a, int j) {  //开始时间=上一个作业的完成时间
	for (; a < j; a++) {
		F[a].Stime = F[a - 1].Ctime;
		Get0(a);
	}
}
void Get3(int i) {//开始时间=本作业的提交时间
	F[i].Stime = F[i].Htime;
	Get0(i);
}
void Get() {
	int i = 1;  //从第二个作业开始（第一个作业的下标为0）
	int j;
	while (F[i].Htime <= F[0].Ctime) {  //直到找到提交时间大于第一个作业的完成时间
		i++;
	}//跳出循环的i作业提交时间大于第一个作业的完成时间
	if (i != 1) { Px1(1, i - 1); Get2(1, i); }  //排序执行时间后以此求剩余时间      (i=2则代表只有i=1的提交时间>第一个作业的完成时间)
	while (i < t) {
		j = i;//j用于记录i值
		//-----------------------------------------------//与上面相同的过程，只是比较的对象不同
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
	cout << setiosflags(ios::fixed) << setprecision(2);//保留2位小数
	cout << "SJF调度算法：" << endl;
	cout << "作业\t     提交时间\t     执行时间\t     开始时间\t     完成时间\t     周转时间\t     带权周转时间\t     " << endl;
	for (int i = 0; i < t; i++) {
		F[i].N = i + 1;
		cout << F[i].N << "\t\t" << F[i].Htime << "\t\t" << F[i].Rtime << "\t\t" <<
			F[i].Stime << "\t\t" << F[i].Ctime << "\t\t" << F[i].Ztime << "\t\t" << F[i].DZtime << "\n";
	}
	for (int j = 0; j < t; j++) {
		sumZtime += F[j].Ztime;
		sumDZtime += F[j].DZtime;
	}
	cout << setiosflags(ios::fixed) << setprecision(3);//保留3位小数
	cout << "平均周转时间： ";
	cout << sumZtime / t << endl;
	cout << "平均带权周转时间： ";
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
