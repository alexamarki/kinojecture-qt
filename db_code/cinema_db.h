#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QString>
#include <vector>
#include <iostream>

// Класс для работы с базой данных фильмов
class MovieDB 
{
public:
    MovieDB(const QString& db_path = "../data/game.db");
    ~MovieDB();

    std::vector<QString> sort_by_rating();
    std::vector<QString> filter_by_genre(const QString& genre);
    void print_first_15(const std::vector<QString>& results);

private:
    QSqlDatabase db;
    static std::vector<QString> query_to_vector(QSqlQuery& query);
};

// Класс для работы с базой данных людей
class PeopleDB 
{
public:
    PeopleDB(const QString& db_path = "../data/game.db");
    ~PeopleDB();

    std::vector<QString> sort_by_birthYear();
    std::vector<QString> filter_by_job(const QString& job);
    void print_first_15(const std::vector<QString>& results);

private:
    QSqlDatabase db;
    static std::vector<QString> query_to_vector(QSqlQuery& query);
};

// Реализация методов класса MovieDB
MovieDB::MovieDB(const QString& db_path) 
{
    db = QSqlDatabase::addDatabase("QSQLITE", "movie_connection");
    db.setDatabaseName(db_path);
    if (!db.open()) 
    {
        std::cerr << "Cannot open database: " << db.lastError().text().toStdString() << std::endl;
    }
}

MovieDB::~MovieDB() 
{
    db.close();
    QSqlDatabase::removeDatabase("movie_connection");
}

std::vector<QString> MovieDB::sort_by_rating() 
{
    QSqlQuery query(db);
    query.exec("SELECT title FROM movies ORDER BY rating DESC;");
    return query_to_vector(query);
}

std::vector<QString> MovieDB::filter_by_genre(const QString& genre) 
{
    QSqlQuery query(db);
    query.prepare("SELECT title FROM movies WHERE genres LIKE :genre;");
    query.bindValue(":genre", "%" + genre + "%");
    query.exec();
    return query_to_vector(query);
}

std::vector<QString> MovieDB::query_to_vector(QSqlQuery& query) 
{
    std::vector<QString> results;
    while (query.next()) 
    {
        results.push_back(query.value(0).toString());
    }
    return results;
}

void MovieDB::print_first_15(const std::vector<QString>& results) 
{
    int count = 0;
    for (const auto& result : results) 
    {
        std::cout << result.toStdString() << std::endl;
        if (++count >= 15) break;
    }
}

// Реализация методов класса PeopleDB
PeopleDB::PeopleDB(const QString& db_path) 
{
    db = QSqlDatabase::addDatabase("QSQLITE", "people_connection");
    db.setDatabaseName(db_path);
    if (!db.open()) 
    {
        std::cerr << "Cannot open database: " << db.lastError().text().toStdString() << std::endl;
    }
}

PeopleDB::~PeopleDB() 
{
    db.close();
    QSqlDatabase::removeDatabase("people_connection");
}

std::vector<QString> PeopleDB::sort_by_birthYear() 
{
    QSqlQuery query(db);
    query.exec("SELECT name FROM people ORDER BY birthYear ASC;");
    return query_to_vector(query);
}

std::vector<QString> PeopleDB::filter_by_job(const QString& job) 
{
    QSqlQuery query(db);
    query.prepare("SELECT name FROM people WHERE jobs LIKE :job;");
    query.bindValue(":job", "%" + job + "%");
    query.exec();
    return query_to_vector(query);
}

std::vector<QString> PeopleDB::query_to_vector(QSqlQuery& query) 
{
    std::vector<QString> results;
    while (query.next()) 
    {
        results.push_back(query.value(0).toString());
    }
    return results;
}

void PeopleDB::print_first_15(const std::vector<QString>& results) 
{
    int count = 0;
    for (const auto& result : results) 
    {
        std::cout << result.toStdString() << std::endl;
        if (++count >= 15) break;
    }
}