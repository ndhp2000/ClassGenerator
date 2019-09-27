#include <iostream>
#include <string>
#include <vector>
const int MAXN = 1000;
using namespace std;
string s,classname;
char inputFile[1000], hFile[1000], cppFile[1000];
int n;
vector <string> a[MAXN];
int main(int argc,char * argv[]) {
	if (argc != 3)
	{
		return 0;
	}

	strcpy(inputFile,argv[1]);
	strcpy(hFile, argv[2]);
	strcat(hFile, ".h");
	strcpy(cppFile,argv[2]);
	strcat(cppFile, ".cpp");

	FILE* fin = freopen(inputFile, "r", stdin);
	FILE* foutH = freopen(hFile, "w", stdout);
	cout << "#pragma once\n";
	int n = 0;
	getline(cin, classname);
	while (1)
	{
		// Chuan hoa
		getline(cin, s);
		if (s == "") break;
		while (s[0] == ' ') s.erase(s.begin());
		while (*(s.end() - 1) == ' ') s.erase(s.end() - 1);
		while (s.find("  ") != string::npos)
		{
			s.erase(s.find("  "),1);
		}

		n++;
		while (!s.empty()) {
			string temp = "";
			while ((!s.empty()) && (*s.begin()) != ' ')
			{
				temp.push_back((*s.begin()));
				s.erase(0, 1);
			}
			if (!s.empty())
				s.erase(0, 1);
			a[n].push_back(temp);
		}
	}

	cout << "class " << classname << "{\n";
	cout << "private:\n";
	for (int i = 1; i <= n; ++i) {
		cout << "\t " << a[i][0] << " ";
		for (auto idx = a[i].begin() + 1; idx != a[i].end(); idx++)
		{
			if (idx != a[i].end() - 1)
				cout << "_" << (*idx) << ", ";
			else
				cout << "_" << (*idx) << "; \n";
		}
	}
	cout << "public: \n";
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j < a[i].size(); ++j) {
			cout << "\t" << a[i][0] << " " << a[i][j] << "();\n";
			string temp = a[i][j];
			temp[0] = toupper(temp[0]);
			cout << "\t" << "void set" << temp << "(" << a[i][0] << " " << a[i][j] << ") ;\n";
		}
	}


	cout << "public: \n";
	cout <<"\t" << classname << "();\n";
	cout <<"\t" << classname << "(";
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j < a[i].size(); ++j)
		{
			if (i == n && j == a[i].size() - 1)
				cout << a[i][0] << " " << a[i][j];
			else
			cout << a[i][0] << " " << a[i][j] << ", ";
		}
	}
	cout << ");\n";
	cout << "\t" << "~" << classname << "();\n";
	cout << "};\n";
	cout << "\n";

	foutH = freopen(cppFile, "w", stdout);
	cout << "#include \"" << hFile << "\" \n\n";
	// Code Ham 

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j < a[i].size(); ++j) {
			// ham getter
			cout  << a[i][0] <<" " << classname << "::" << a[i][j] << "()\n";
			cout << "{\n";
			cout << "\t return this->_" << a[i][j] << ";\n";
			cout << "}\n";

			string temp = a[i][j];
			temp[0] = toupper(temp[0]);
			cout << "void "<< classname << "::set" << temp << "(" << a[i][0] << " " << a[i][j] << ")\n";
			cout << "{\n";
			cout << "\t this->_" << a[i][j] << " = " << a[i][j] << ";\n";
			cout << "}\n";
		}
	}

	// 
	cout << classname << "::" << classname << "()\n";
	cout << "{\n";
	cout << "//Code your constructor here! \n\n";
	cout << "}\n";

	cout << classname <<"::"<< classname << "(";
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j < a[i].size(); ++j)
		{
			if (i == n && j == a[i].size() - 1)
				cout << a[i][0] << " " << a[i][j];
			else
				cout << a[i][0] << " " << a[i][j] << ", ";
		}
	}

	cout << ")\n";
	cout << "{\n";
	for (int i = 1; i <= n; ++i) 
	{
		for (int j = 1;j<a[i].size();++j)
			cout << "\t this->_" << a[i][j] << " = " << a[i][j] << ";\n";
	}
	cout << "}\n";


	cout << classname << "::" <<  "~" << classname << "()\n";
	cout << "{\n";
	cout << "//Code your destructor here! \n\n";
	cout << "}\n";

	return 0;
}