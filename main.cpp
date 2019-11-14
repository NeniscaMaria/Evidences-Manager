
#include <QtWidgets/QApplication>
#include "MainWindow.h"
#include "Repository.h"
//TODO: implement: when clicking on a cell, display the full image separately
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ifstream file("storageChoice.txt");
	int storageChoice=0;
	file >> storageChoice;
	file.close();
	//storage choice: =1 --> file storage
	//				  =0 --> memory storage
	Repository<Evidence>* repo = new Repository<Evidence>;
	Repository<Evidence>* savedRepo=new Repository<Evidence>;
	MainWindow window{ repo,savedRepo, storageChoice };
	//window.show();
	return a.exec();
}
