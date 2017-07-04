#ifndef USER_H
#define USER_H

#include <QObject>

#include "../dbadapter.h"

class User : public QObject
{
    Q_OBJECT
public:
    explicit User(QObject *parent = nullptr);
    static User* fromId(int userId);

    void insert(QString nickName);
    void checkName(QString nickName);

    QString nickName() {return this->_nickName;}
signals:

public slots:

private:
    int _id;
    QString _nickName;

    static QHash<int, User*> cache;
};

#endif // USER_H
