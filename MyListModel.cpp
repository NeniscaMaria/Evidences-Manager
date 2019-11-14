#include "MyListModel.h"
#include "MyListTable.h"
#include <QSortFilterProxyModel>

MyListModel::MyListModel(Repository<Evidence>* r, QWidget *parent) : QMainWindow(parent), repo{ r }
{
	this->ui.setupUi(this);

	// create the model
	this->tableModel = new MyListTableModel{ this->repo };

	// set the model for the table view
	this->setupTableView();
}

MyListModel::~MyListModel() {}

void MyListModel::setupTableView()
{
	// set the model
	 ui.tableView->setModel(this->tableModel);

	 ui.tableView->setItemDelegate(new PictureDelegate{});
	 ui.tableView->verticalHeader()->setDefaultSectionSize(100);
	// force the columns to resize, according to the size of their contents
	this->ui.tableView->resizeColumnsToContents();
	this->ui.tableView->resizeRowsToContents();
}

#include <QPixmap>
#include <qdebug.h>
PictureDelegate::PictureDelegate(QWidget *parent) : QStyledItemDelegate{ parent }
{
}

#include <qresource.h>
void PictureDelegate::paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const
{
	QString photograph = index.model()->data(index, Qt::EditRole).toString();

	if (index.column() != 5)
	{
		QStyledItemDelegate::paint(painter, option, index);
		return;
	}
	std::string p = "../QtGuiApplication2/Resources/" + photograph.toStdString();
	QString photo = QString::fromLocal8Bit(p.c_str());
	if (photograph.contains(".jpg"))
	{
		QPixmap pixmap(photo);
		if (pixmap.isNull())
			qDebug() << "NULL pixmap at " << photograph;
		painter->drawPixmap(option.rect, pixmap);
	}
}

QSize PictureDelegate::sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const
{
	if (index.column() == 5)
	{
		return QSize(500,500);
	}

	return QStyledItemDelegate::sizeHint(option, index);
}
