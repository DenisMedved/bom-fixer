#include "bomfilesystemmodel.h"
#include <iostream>

BOMFileSystemModel::BOMFileSystemModel(QObject *parent/* = Q_NULLPTR */) :
    QFileSystemModel(parent)
{

}

bool BOMFileSystemModel::hasBOM(QFileInfo& fileInfo) const
{
    QFile file(fileInfo.filePath());

    if (!file.open(QIODevice::ReadOnly)) {
        return false;
    }

    QByteArray head = file.read(3);

    if (head.length() < 3) {
        return false;
    }

    return head.at(0) == '\xEF'
            && head.at(1) == '\xBB'
            && head.at(2) == '\xBF';
}

void BOMFileSystemModel::fixBOM(QString path) const
{
    QFile file(path);
    if (!file.open(QIODevice::ReadWrite))
        return ;

    QByteArray content = file.readAll();
    content.remove(0,3); //drop 3 bytes from the begin
    file.resize(0);
    file.write(content);
    file.close();
}

void BOMFileSystemModel::slotFixBOM()
{
    QSet<QString>::iterator it = m_bomPaths.begin();
    while (it != m_bomPaths.end()) {
        fixBOM(*it);
        ++it;
    }

    populateDirectory(rootDirectory());

    emit fixed();
}

void BOMFileSystemModel::populateDirectory(const QDir& dir)
{
    setRootPath(dir.path());

    m_bomPaths.clear();
    QDirIterator it(rootDirectory(), QDirIterator::Subdirectories);
    while (it.hasNext()) {
        it.next();
        QFileInfo info = it.fileInfo();

        if (!info.path().contains("/.") //ignore hidden dirs and subdirs
                && info.fileName().at(0) != '.' //ignore hidden files
                && info.isFile()
                && !m_bomPaths.contains(info.filePath()) //check if already handled
                && hasBOM(info))

            m_bomPaths.insert(info.filePath());
    }

    emit dataChanged(QModelIndex(), QModelIndex());
}

QVariant BOMFileSystemModel::data(const QModelIndex &index, int role /*= Qt::DisplayRole*/) const
{
    if (role == Qt::TextColorRole){
        if (m_bomPaths.contains(filePath(index)))
            return QColor(Qt::red);
    }

    return QFileSystemModel::data(index, role);
}
