#include <iostream>
#include <string>
#include <vector>
#include <io.h>
#include <string.h>

using namespace std;

void getFiles(string foler, vector<string>& files);

int main() {
	string folder = "E:/MATLAB/LBP/scene_categories/MITcoast";  //�˴��õ���б�ܣ�Ҳ�����÷�б
	//����ע���������C���Ե��ص㣬Ҫ��˫��б�ܣ���"E:\\MATLAB\\LBP\\scene_categories"
	//cin >> folder;   //Ҳ�����ô˶δ���ֱ����DOS���������ַ����ʱֻ�������ĵ���б�ܼ���

	vector<string> files;
	getFiles(folder, files);  //filesΪ���ص��ļ������ɵ��ַ���������

	for (int i = 0; i < files.size(); i++) {    //files.size()�����ļ�����

		//To do here
		cout << files[i] << endl;
	}
	system("pause");
	return 0;
}

void getFiles(string path, vector<string>& files) {
	//�ļ����
	long hFile = 0;
	//�ļ���Ϣ
	struct _finddata_t fileinfo;
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1) {
		do {
			//�����Ŀ¼,����֮
			//�������,�����б�
			if ((fileinfo.attrib & _A_SUBDIR)) {
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					getFiles(p.assign(path).append("\\").append(fileinfo.name), files);
			}
			else {
				files.push_back(p.assign(path).append("\\").append(fileinfo.name));
			}
		} while (_findnext(hFile, &fileinfo) == 0); 
		_findclose(hFile);
	}
}