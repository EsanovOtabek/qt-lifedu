#include<iostream>
#include <fstream>
using namespace std;
int main(){
	int t=1449,n,ind;
	string a;
	char c;
	ofstream file;
	file.open("sql.txt");
	while(t--){
		getline(cin,a);
		a=a.c_str();
		for(int i=0;i<a.size();i++){
			if(a[i]=='.'){
				ind=i;
			}
		}
		for(int i=ind+1;i<a.size();i++){
			file<<a[i];
		}
		file<<'\n';
	}
	file.close();
	return 0;
}