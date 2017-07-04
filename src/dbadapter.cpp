#include "dbadapter.h"

#include <QtSql>
#include <QSqlQueryModel>

#include <QDebug>

static dbAdapter *dbAdapterInstance = 0;

dbAdapter::dbAdapter(QObject *parent) : QObject(parent)
{
    QMutexLocker locker(&lock);

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(QDir::homePath()+"/.qvorum/db.sql");

    if(QFile(QDir::homePath()+"/.qvorum/db.sql").size() == 0)
    {
        qDebug() << QDir::homePath()+"/.qvorum/db.sql NOT FOUND";
        qDebug() << "Create db dir";
        QDir configDir = QDir(QDir::homePath()+"/.qvorum");
        if(!configDir.exists())
        {
            configDir.mkpath(QDir::homePath()+"/.qvorum");
        }
        initDB();
    }
    else
    {
        query = QSqlQuery(db);
    }

    if(!db.open())
    {
        qDebug() << db.lastError().text();
    }


}

dbAdapter::~dbAdapter()
{
    db.close();
}


dbAdapter& dbAdapter::instance(){
    static QMutex mutex;
    QMutexLocker locker(&mutex);
    if(!dbAdapterInstance) dbAdapterInstance = new dbAdapter();
    return *dbAdapterInstance;
}

void dbAdapter::initDB()
{
    db.exec("CREATE TABLE `users` (`id` INTEGER PRIMARY KEY AUTOINCREMENT,`nickName` TEXT )");
    emit baseCreate();
}
