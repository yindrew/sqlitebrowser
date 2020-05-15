#include "DbStructureModel.h"
#include "dbstructureqitemviewfacade.h"

DbStructureQItemViewFacade::DbStructureQItemViewFacade(QAbstractItemView *aitemView) : QObject(aitemView)
{
    m_itemView = aitemView;
}

const QAbstractItemView *DbStructureQItemViewFacade::itemView() const
{
    return m_itemView;
}

bool DbStructureQItemViewFacade::hasSelection() const
{
    return itemView()->selectionModel()->hasSelection();
}

QString DbStructureQItemViewFacade::displayName()
{
    try {
        QAbstractItemModel *model = itemView()->model();
        QModelIndex index = itemView()->currentIndex();
        return model->data(index.sibling(index.row(), DbStructureModel::ColumnName), Qt::DisplayRole).toString();
    } catch (...) {
        return QString();
    }
}

QString DbStructureQItemViewFacade::name()
{
    try {
        QAbstractItemModel *model = itemView()->model();
        QModelIndex index = itemView()->currentIndex();
        return model->data(index.sibling(index.row(), DbStructureModel::ColumnName), Qt::EditRole).toString();
    } catch (...) {
        return QString();
    }
}

QString DbStructureQItemViewFacade::objectType()
{
    try {
        QAbstractItemModel *model = itemView()->model();
        QModelIndex index = itemView()->currentIndex();
        return model->data(index.sibling(index.row(), DbStructureModel::ColumnObjectType), Qt::EditRole).toString();
    } catch (...) {
        return QString();
    }
}

QString DbStructureQItemViewFacade::schema()
{
    try {
        QAbstractItemModel *model = itemView()->model();
        QModelIndex index = itemView()->currentIndex();
        return model->data(index.sibling(index.row(), DbStructureModel::ColumnSchema), Qt::EditRole).toString();
    } catch (...) {
        return QString();
    }
}

QString DbStructureQItemViewFacade::sql()
{
    try {
        QAbstractItemModel *model = itemView()->model();
        QModelIndex index = itemView()->currentIndex();
        return model->data(index.sibling(index.row(), DbStructureModel::ColumnSQL), Qt::EditRole).toString();
    } catch (...) {
        return QString();
    }
}

sqlb::ObjectIdentifier DbStructureQItemViewFacade::object()
{
    try {
        return sqlb::ObjectIdentifier(schema().toStdString(), name().toStdString());
    } catch (...) {
        return sqlb::ObjectIdentifier();
    }
}
