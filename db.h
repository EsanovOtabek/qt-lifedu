#ifndef DB
#define DB
#include <QString>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QString>
#include <QDateTime>
#include <map>
using namespace std;

class DBHelper{

    QSqlDatabase db;
    QString tablename;
    void table_key(map <int,QString> &key, QString tablename){
        key[0]="id";
        if(tablename=="users"){
            key[1]="fio";
            key[2]="email";
            key[3]="password";
        }
        else if(tablename=="courses"){
            key[1]="name";
            key[2]="title";
            key[3]="image";
        }
        else if(tablename=="lessons"){
            key[1]="course_id";
            key[2]="title";
            key[3]="content";
            key[4]="video";
        }
        else if(tablename=="user_courses"){
            key[1]="user_id";
            key[2]="course_id";
            key[3]="vaqt";
        }
    }

public:
    QString echo;
    DBHelper(){
        this->db = QSqlDatabase::addDatabase("QSQLITE");
        this->db.setDatabaseName("C:/Users/beoo/Documents/LifeduTest/assets/lifedu.db");
        if(db.open()){
            this->echo="DB connect!";
        }
        else{
            this->echo="DB connection error!";
        }
    }

    int count(QString sql){
        QSqlQuery query;
        query.prepare(sql);
        query.exec();
        int k=0;
        while(query.next()){
            k++;
        }
        return k;
    }

    void select(QString sql, map< int, map<QString,QString> > &mp, QString tablename){
        int k=0;
        map<int,QString> key;
        table_key(key,tablename);
        QSqlQuery query;
        query.prepare(sql);
        query.exec();
        while(query.next()){
            for(int i=0;i<key.size();i++){
                mp[k][key[i]]=query.value(i).toString();
            }
            k++;
        }

//        this->echo=QString::number(k);
    }

    bool inupde(QString sql){
        QSqlQuery query;
        query.prepare(sql);
        return query.exec();
    }
};

class Session
{
public:
    QString id;
    QString fio;
    QString email;
    QString echo;

private:

    QSqlDatabase db;
    bool insert(){
        QSqlQuery query;
        QString T=QDateTime::currentDateTime().toString("d.MM.yyyy hh:mm:ss");
        QString sql="INSERT INTO session (user_id,fio,email,utime) VALUES("+
                this->id+",'"+this->fio+"','"+this->email+"','"+T+"')";
        query.prepare(sql);
        return query.exec();
    }
    bool delet(){
        QSqlQuery query;
        QString sql="DELETE FROM session";
        query.prepare(sql);
        return query.exec();
    }
    bool count(){
        QSqlQuery query;
        QString sql="SELECT * FROM session";
        query.prepare(sql);
        query.exec();
        while (query.next()){
            this->id=query.value(1).toString();
            this->fio=query.value(2).toString();
            this->email=query.value(3).toString();
            return 1;
        }
        return 0;
    }

public:
    Session(){
        this->db = QSqlDatabase::addDatabase("QSQLITE");
        this->db.setDatabaseName("C:/Users/beoo/Documents/LifeduTest/assets/user.db");
        if(db.open()){
            this->echo="DB connect!";
        }
        else{
            this->echo="DB connection error!";
        }
    }

    bool login(){
        return this->insert();
    }
    bool isActive(){
        return this->count();
    }
    bool logout(){
        return this->delet();
    }
};



#endif // DB

