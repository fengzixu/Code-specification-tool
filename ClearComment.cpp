#include<iostream>
#include<string>
#include<cstdlib>
#include<fstream>
#include <atlbase.h>
#include <atlstr.h>
#include <stack>
using namespace std;





int main(){


	fstream inputfile, writefile,result_file;
	inputfile.open("F:\\\\code\\\\checkfile\\\\file.cpp");
	writefile.open("F:\\\\\code\\\\\checkfile\\\\output.txt");



	string line = "";

	while(getline(inputfile,line)){

		//���ƥ�䵽�˵���ע�͵Ļ�
		if(line.find("//") != string::npos){

			writefile << "\n";
		}
		else
			writefile << line << "\n";

	}
	inputfile.close();
	writefile.close();
	
	inputfile.open("F:\\\\code\\\\checkfile\\\\file.cpp");
	writefile.open("F:\\\\\code\\\\\checkfile\\\\output.txt");
	result_file.open("F:\\\\\code\\\\\checkfile\\\\result_output.txt");

	line = "";
    bool flag = false;
	//�������ע�ͣ���ȡ���ļ�β
	while(!getline(writefile,line).eof()){

		if (line.find("/*") != string::npos)
		{
			 result_file << "\n";
			 flag = true;
		     continue;
		}

		if(line.find("*/") != string::npos){

			  result_file << "\n";
			  flag = false;
			  continue;
		}
		if(flag)
		   result_file << "\n";
		else
		   result_file << line << "\n";
	}

	inputfile.close();
	writefile.close();
	result_file.close();



	return 0;
}