#include <string>
#include <vector>
#include <sqlite3.h>
#include <format>

class CinemaDB
{
public:
    CinemaDB(const std::string& db_path = "../data/im.db")
    {
        exit = sqlite3_open(db_path.c_str(), &db);
    }
    ~CinemaDB() 
    {
        sqlite3_close(db);
    }

    void createTables() 
    {
        char* creationError;
        std::string query_name_basics = "CREATE TABLE IF NOT EXISTS people("
                                        "nconst TEXT PRIMARY KEY,"
                                        "primaryName TEXT,"
                                        "birthYear INT,"
                                        "deathYear INT,"
                                        "primaryProfession TEXT,"
                                        "knownForTitles TEXT);";
        std::string query_film_basics = "CREATE TABLE IF NOT EXISTS media("
                                        "tconst TEXT PRIMARY KEY,"
                                        "titleType TEXT,"
                                        "primaryTitle TEXT,"
                                        "isAdult BOOL,"
                                        "startYear INT,"
                                        "runtimeMinutes INT,"
                                        "genres TEXT);";
        std::string query_jobs = "CREATE TABLE IF NOT EXISTS jobs("
                                        "ID INT PRIMARY KEY AUTOINCREMENT,"
                                        "tconst TEXT,"
                                        "nconst TEXT,"
                                        "CATEGORY TEXT,"
                                        "JOB TEXT,"
                                        "CHARACTERS TEXT);";
        std::string query_directors = "CREATE TABLE IF NOT EXISTS directors("
                                    "tconst TEXT PRIMARY KEY,"
                                    "directors TEXT);";
        std::string query_ratings = "CREATE TABLE IF NOT EXISTS ratings("
                                    "tconst TEXT PRIMARY KEY,"
                                    "averageRatings FLOAT,"
                                    "numVotes INT);";
        exit = sqlite3_exec(db, query_name_basics.c_str(), NULL, NULL, &creationError);
        exit = sqlite3_exec(db, query_film_basics.c_str(), NULL, NULL, &creationError);
        exit = sqlite3_exec(db, query_jobs.c_str(), NULL, NULL, &creationError);
        exit = sqlite3_exec(db, query_directors.c_str(), NULL, NULL, &creationError);
        exit = sqlite3_exec(db, query_ratings.c_str(), NULL, NULL, &creationError);
    }

    void add_name_basics(std::string nconst, std::string primaryName, int birthYear,
                            int deathYear, std::string primaryProfession, 
                            std::string knownForTitles)
    {
        char* injectionError;
        std::string query = std::format("INSERT INTO people (nconst, primaryName, birthYear, "
                                        "deathYear, primaryProfession, knownForTitles) VALUES"
                                        " ('{}', '{}', {}, {}, '{}', '{}')",
                                        nconst, primaryName, birthYear, deathYear, 
                                        primaryProfession, knownForTitles);
        exit = sqlite3_exec(db, query.c_str(), NULL, NULL, &injectionError);
    }
    void add_film_basics(std::string tconst, std::string titleType, std::string primaryTitle, 
                            bool isAdult, int startYear, int runtimeMinutes, std::string genres)
    {
        char* injectionError;
        std::string query = std::format("INSERT INTO media (tconst, titleType, primaryTitle, "
                                        "isAdult, startYear, runtimeMinutes, genres) VALUES"
                                        " ('{}', '{}', '{}', {}, {}, {}, '{}')",
                                        tconst, titleType, primaryTitle, isAdult, startYear, 
                                        runtimeMinutes, genres);
        exit = sqlite3_exec(db, query.c_str(), NULL, NULL, &injectionError);
    }
    void add_jobs(std::string tconst, std::string nconst, std::string category, 
                    std::string job, std::string characters)
    {
        char* injectionError;
        std::string query = std::format("INSERT INTO jobs (tconst, nconst, category, job, "
                                        "characters) VALUES"
                                        " ('{}', '{}', '{}', '{}', '{}')",
                                        tconst, nconst, category, job, characters);
        exit = sqlite3_exec(db, query.c_str(), NULL, NULL, &injectionError);
    }
    void add_directors(std::string tconst, std::string directors)
    {
        char* injectionError;
        std::string query = std::format("INSERT INTO directors (tconst, directors) VALUES"
                                        " ('{}', '{}')",
                                        tconst, directors);
        exit = sqlite3_exec(db, query.c_str(), NULL, NULL, &injectionError);
    }
    void add_ratings(std::string tconst, float averageRating, int numVotes)
    {
        char* injectionError;
        std::string query = std::format("INSERT INTO ratings (tconst, averageRating, numvotes) VALUES"
                                        " ('{}', {}, {})",
                                        tconst, averageRating, numVotes);
        exit = sqlite3_exec(db, query.c_str(), NULL, NULL, &injectionError);
    }

    void sql_exec(std::string query, sqlite3_callback callback, void* pArg)
    {
        char* queryError;
        exit = sqlite3_exec(db, query.c_str(), callback, pArg, &queryError);
    }
private:
    sqlite3* db;
    int exit;
};