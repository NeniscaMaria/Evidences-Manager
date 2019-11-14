#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtGuiApplication2.h"

class MyListWindow : public QMainWindow
{
	Q_OBJECT

public:
	MyListWindow(QWidget *parent = Q_NULLPTR);

private:
	Ui::MyListTable ui;
};
