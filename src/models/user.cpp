#include "user.h"

#include "../dbadapter.h"

User::User(QObject *parent) : QObject(parent)
{
    _id = 0;
    _nickName = "";
}

QHash<int, User*> User::cache;


User* User::fromId(int userId)
{
    if(cache.contains(userId))
    {
        return cache.value(userId);
    }
    QSqlDatabase db = dbAdapter::instance().db;
    QSqlQuery query(db);
    query.prepare("SELECT nickName FROM users WHERE id=:id");
    query.bindValue(":id",userId);

    if(!query.exec())
    {
        qDebug() << query.lastQuery() << query.lastError().text();
    }

    if(query.next())
    {
        User* user = new User();
        user->_id = userId;
        user->_nickName = query.value(0).toString();

        cache.insert(userId,user);
        return user;
    }
    return 0;
}

int User::checkName(QString nickName)
{
    QSqlDatabase db = dbAdapter::instance().db;
    QSqlQuery query(db);
    query.prepare("SELECT id FROM users WHERE nickName LIKE %:nickName%");
    query.bindValue(":nickName",nickName);
    if(!query.exec())
    {
        qDebug() << query.lastQuery() << query.lastError().text();
    }

    if(query.next())
    {
        return query.value(0).toString();
    }

    return 0;
}

int User::insert(QString nickName)
{
    if(checkName(nickName) == 0)
    {
        QSqlDatabase db = dbAdapter::instance().db;
        QSqlQuery query(db);
        QString str = QString("INSERT INTO users (nickName) VALUES ('%1')").arg(nickName);

        if(query.exec(str))
        {
            return query.lastInsertId();
        }
    }
    return 0;
}
