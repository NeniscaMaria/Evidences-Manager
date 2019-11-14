#include "MyListTable.h"
#include <QFont>
#include <QBrush>
#include <algorithm>
#include <QDebug>
#include <QMessageBox>
#include <QPainter>
#include <qdebug.h>
#include <QStandardItemModel>
const int MyListTableModel::ITEMS_PER_PAGE = 10;

MyListTableModel::MyListTableModel(Repository<Evidence>* r, QObject* parent) : QAbstractTableModel{ parent }, repo{ r }
{
	this->loadedRows = 0;
}

MyListTableModel::~MyListTableModel()
{
}

int MyListTableModel::rowCount(const QModelIndex & parent) const
{
	int size = this->repo->size();
	if (size <= this->loadedRows)
		return size;
	return this->loadedRows;
}

int MyListTableModel::columnCount(const QModelIndex & parent) const
{
	return 6;
}

QVariant MyListTableModel::data(const QModelIndex & index, int role) const
{
	// get the genes
	std::vector<Evidence*> evidences = this->repo->getElements();

	int row = index.row();
	int column = index.column();
	Evidence* e = evidences[row];
	if (role == Qt::DisplayRole || role == Qt::EditRole)
	{
		switch (column)
		{
		case 0:
			return QString::fromStdString(e->getId());
		case 1:
			return QString::fromStdString(e->getMeasurement());
		case 2:
			return QString::fromStdString(std::to_string(e->getImageClarityLevel()));
		case 3:
			return QString::fromStdString(std::to_string(e->getQuantity()));
		case 4:
			return QString::fromStdString(e->getPhotograph());
		case 5:
			return QString::fromStdString(e->getPhotograph());
		default:
			break;
		}
	}
	if (role == Qt::FontRole)
	{
		QFont font("Times", 10 , 2 , true);
		font.setItalic(false);
		return font;
	}
	if (role == Qt::BackgroundRole)
	{
		if (row % 2 == 1)
		{
			return QBrush{ QColor{ 82,219,255 } };
		}
	}

	return QVariant{};
}

QVariant MyListTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole)
	{
		if (orientation == Qt::Horizontal)
		{
			switch (section)
			{
			case 0:
				return QString{ "ID" };
			case 1:
				return QString{ "Measurement" };
			case 2:
				return QString{ "Image clarity level" };
			case 3:
				return QString{ "Quantity" };
			case 4:
				return QString{ "Photograph address" };
			case 5:
				return QString{ "Photograph" };
			default:
				break;
			}
		}
	}
	if (role == Qt::FontRole)
	{
		QFont font("Times", 15, 10, true);
		font.setBold(true);
		font.setItalic(false);
		return font;
	}

	return QVariant{};
}

bool MyListTableModel::setData(const QModelIndex & index, const QVariant & value, int role)
{
	if (!index.isValid() || role != Qt::EditRole)
		return false;

	// set the new data to the gene
	int evidenceIndex = index.row();
	Evidence* currentEvidence = this->repo->getElements()[evidenceIndex];
	if (index.column() == 0)
	{
		char* ID = new char[30];
		strcpy(ID, value.toString().toStdString().c_str());
		this->repo->updateEvidence(evidenceIndex, new Evidence{ ID, currentEvidence->getMeasurement(), currentEvidence->getImageClarityLevel(),currentEvidence->getQuantity(),currentEvidence->getPhotograph() });
	}
	if (index.column() == 1)
	{
		char* measurement = new char[50];
		strcpy(measurement, value.toString().toStdString().c_str());
		this->repo->updateEvidence(evidenceIndex, new Evidence{ currentEvidence->getId(), measurement, currentEvidence->getImageClarityLevel(),currentEvidence->getQuantity(),currentEvidence->getPhotograph() });
	}
	if (index.column() == 2)
	{
		char* imageClarityLevel = new char[50];
		strcpy(imageClarityLevel, value.toString().toStdString().c_str());
		this->repo->updateEvidence(evidenceIndex, new Evidence{ currentEvidence->getId(), currentEvidence->getMeasurement(), atof(imageClarityLevel),currentEvidence->getQuantity(),currentEvidence->getPhotograph() });
	}
	if (index.column() == 0)
	{
		char* quantity = new char[50];
		strcpy(quantity, value.toString().toStdString().c_str());
		this->repo->updateEvidence(evidenceIndex, new Evidence{ currentEvidence->getId(), currentEvidence->getMeasurement(), currentEvidence->getImageClarityLevel(),atoi(quantity),currentEvidence->getPhotograph() });
	}
	if (index.column() == 0)
	{
		char* photo = new char[50];
		strcpy(photo, value.toString().toStdString().c_str());
		this->repo->updateEvidence(evidenceIndex, new Evidence{ currentEvidence->getId(), currentEvidence->getMeasurement(), currentEvidence->getImageClarityLevel(),currentEvidence->getQuantity(),photo });
	}

	// emit the dataChanged signal
	emit dataChanged(index, index);

	return true;
}

Qt::ItemFlags MyListTableModel::flags(const QModelIndex & index) const
{
	return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
}

bool MyListTableModel::canFetchMore(const QModelIndex & parent) const
{
	return this->repo->size() > this->loadedRows;
}

void MyListTableModel::fetchMore(const QModelIndex & parent)
{
	int remainedItems = this->repo->size() - this->loadedRows;
	int itemsToFetch = std::min(remainedItems, ITEMS_PER_PAGE);
	this->beginInsertRows(QModelIndex{}, this->loadedRows, this->loadedRows + itemsToFetch - 1);
	this->loadedRows += itemsToFetch;
	this->endInsertRows();

	qDebug() << "Fetched: " << this->loadedRows;
}
