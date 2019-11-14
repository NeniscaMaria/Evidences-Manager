#include <QtWidgets/QMainWindow>
#include "MyListTable.h"
#include "Repository.h"
#include "MyListTable.h"
#include <qtableview.h>
#include <QHBoxLayout>
#include "QtGuiApplication2.h"
#include <qpainter.h>
#include <qstyleditemdelegate.h>

class PictureDelegate : public QStyledItemDelegate
{
public:
	PictureDelegate(QWidget *parent = 0);

	// these two functions need to be overridden to draw an image for each item
	void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
	QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

class MyListModel : public QMainWindow
{
	Q_OBJECT

private:
	Repository<Evidence>* repo;
	MyListTableModel* tableModel;
	Ui::MyListTable ui;

public:
	MyListModel(Repository<Evidence>* r, QWidget *parent = 0);
	~MyListModel();

private:
	void setupTableView();
};

