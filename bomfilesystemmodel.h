#ifndef BOMFILESYSTEMMODEL_H
#define BOMFILESYSTEMMODEL_H

#include <memory>
#include <QFileSystemModel>
#include <QDir>
#include <QVariant>
#include <QModelIndex>
#include <QSet>

class BOMFileSystemModel : public QFileSystemModel
{
    Q_OBJECT

private:
    bool hasBOM(QFileInfo& fileInfo) const;
    void fixBOM(QString path) const;
    QSet<QString> m_bomPaths;

public:
    explicit BOMFileSystemModel(QObject *parent = 0);
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    void populateDirectory(const QDir& dir);

public slots:
    void slotFixBOM();
signals:
    void fixed();
};

#endif // BOMFILESYSTEMMODEL_H
