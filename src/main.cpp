#include <QCoreApplication>

#include <qsqldatabase.h>
#include <qsqlquery.h>
#include <qsqlerror.h>
#include <qfile.h>
#include <qvariant.h>
#include <qsqlrecord.h>
#include <qdebug.h>


QString getQuery(const QString resourcename){
    QFile f(resourcename);
    f.open(QIODevice::ReadOnly);
    QString ret(f.readAll());
    f.close();
    return ret;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString driver{"QSQLITE"};
    QSqlDatabase db = QSqlDatabase::addDatabase(driver);

    db.setDatabaseName("C:/temp/filtertest.sql");
    db.open();

    QStringList words = getQuery(":/words.txt").split(" ");
    QSqlQuery q(db);
    q.exec(getQuery(":/sql_create_table.txt"));

    q.prepare(getQuery(":/sql_insert_data.txt"));
    db.transaction();
    for ( int i = 0; i < words.count(); i++ ){
        q.bindValue(0,words.at(i));
        q.bindValue(1,i);
        q.exec();
    }
    db.commit();


    q.exec(getQuery(":/paginate_query.txt").replace("__SKIP__","100").replace("__PAGESIZE__","10"));
    while(q.next()){
        QSqlRecord r=q.record();
        qDebug()<<r.value(0)<<"\t"<<r.value(1);
    }
    return a.exec();
}
