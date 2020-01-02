#include <iostream>
#include <string>
#include <vector>
#include <io.h>
#include <string.h>

using namespace std;

void getFiles(string foler, vector<string>& files);

int main() {
	string folder = "E:/MATLAB/LBP/scene_categories/MITcoast";  //此处用的是斜杠，也可以用反斜
	//但需注意的是由于C语言的特点，要用双反斜杠，即"E:\\MATLAB\\LBP\\scene_categories"
	//cin >> folder;   //也可以用此段代码直接在DOS窗口输入地址，此时只需正常的单反斜杠即可

	vector<string> files;
	getFiles(folder, files);  //files为返回的文件名构成的字符串向量组

	for (int i = 0; i < files.size(); i++) {    //files.size()返回文件数量

		//To do here
		cout << files[i] << endl;
	}
	system("pause");
	return 0;
}

void getFiles(string path, vector<string>& files) {
	//文件句柄
	long hFile = 0;
	//文件信息
	struct _finddata_t fileinfo;
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1) {
		do {
			//如果是目录,迭代之
			//如果不是,加入列表
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