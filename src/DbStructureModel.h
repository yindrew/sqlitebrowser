#ifndef DBSTRUCTUREMODEL_H
#define DBSTRUCTUREMODEL_H

#include <QAbstractItemModel>
#include <memory>

class DBBrowserDB;
class QTreeWidgetItem;
namespace sqlb { class Object; using ObjectPtr = std::shared_ptr<Object>; }

class DbStructureModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit DbStructureModel(DBBrowserDB& db, QObject* parent = nullptr);
    ~DbStructureModel() override;

    QVariant data(const QModelIndex& index, int role) const override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex& index) const override;
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& = QModelIndex()) const override;

    QStringList mimeTypes() const override;
    QMimeData* mimeData(const QModelIndexList& indices) const override;
    bool dropMimeData(const QMimeData* data, Qt::DropAction action, int row, int column, const QModelIndex& parent) override;

    /*!
     * \enum DbStructureModel::Columns
     *
     *  The Columns of a DbStructureModel Item.
     *
     * \value ColumnName Name of the datbase structure object (e.g. tablename, fieldname, indexname, databasename (alias, not filename!)
     * \value ColumnObjectType Type of the datbase structure object as QString ("table", "view", "index", "trigger", "field")
     * \value ColumnDataType Datatype of the database structure object itself. todo: investigate and document fully
     * \value ColumnSQL Original sql statement of the database structure object.
     * \value ColumnSchema Name of the datbase to which the database structure object belongs (alias, not filename!).
     * \value ColumnUrl Filename or url of the datbase of the object that represents the database.
     */
    enum Columns
    {
        ColumnName,
        ColumnObjectType,
        ColumnDataType,
        ColumnSQL,
        ColumnSchema,
        ColumnUrl
    };

public slots:
    void reloadData();
    void setDropQualifiedNames(bool value) { m_dropQualifiedNames = value; }
    void setDropEnquotedNames(bool value) { m_dropEnquotedNames = value; }

signals:
    void structureUpdated();

private:
    DBBrowserDB& m_db;
    QTreeWidgetItem* rootItem;
    QTreeWidgetItem* browsablesRootItem;
    bool m_dropQualifiedNames;
    bool m_dropEnquotedNames;

    void buildTree(QTreeWidgetItem* parent, const std::string& schema);
    QTreeWidgetItem* addNode(QTreeWidgetItem* parent, const sqlb::ObjectPtr& object, const std::string& schema);
    QString getNameForDropping(const QString& domain, const QString& object, const QString& field) const;
};

#endif
