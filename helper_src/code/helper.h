#include <format>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <sqlite3.h>
#include <map>

class HelperDB
{
public:
    HelperDB(const std::string& db_path = "../data/im.db")
    {
        exit = sqlite3_open(db_path.c_str(), &db);
    }
    ~HelperDB() 
    {
        sqlite3_close(db);
    }

    void createTables() 
    {
        char* creationError;
        std::string query_name_basics = "CREATE TABLE IF NOT EXISTS name("
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
                                        "endYear INT,"
                                        "runtimeMinutes INT,"
                                        "genres TEXT);";
        std::string query_profs = "CREATE TABLE IF NOT EXISTS profs("
                                "ID INT PRIMARY KEY,"
                                "tconst TEXT,"
                                "nconst TEXT,"
                                "category TEXT,"
                                "prof TEXT,"
                                "characters TEXT);";
        std::string query_directors = "CREATE TABLE IF NOT EXISTS directors("
                                    "tconst TEXT PRIMARY KEY,"
                                    "directors TEXT);";
        std::string query_ratings = "CREATE TABLE IF NOT EXISTS ratings("
                                    "tconst TEXT PRIMARY KEY,"
                                    "averageRating REAL,"
                                    "numVotes INT);";
        exit = sqlite3_exec(this->db, query_name_basics.c_str(), NULL, NULL, &creationError);
        exit = sqlite3_exec(this->db, query_film_basics.c_str(), NULL, NULL, &creationError);
        exit = sqlite3_exec(this->db, query_profs.c_str(), NULL, NULL, &creationError);
        exit = sqlite3_exec(this->db, query_directors.c_str(), NULL, NULL, &creationError);
        exit = sqlite3_exec(this->db, query_ratings.c_str(), NULL, NULL, &creationError);
    }

    void sql_exec(std::string query, sqlite3_callback callback, void* pArg)
    {
        char* queryError;
        exit = sqlite3_exec(this->db, query.c_str(), callback, pArg, &queryError);
    }

    void add_file_data(std::string filepath, std::string table)
    // the datamap functions as following:
    // -1 - this column is ignored during parsing
    // 0 - this column holds a string value
    // 1 - this column holds a numeric value
    // 2 - this column holds a boolean value
    // 3 - this column holds a double value
    {
        std::vector<int> datamap = dataMap.at(table);
        char* fileError;
        std::ifstream file(filepath);
        if (!file.is_open()) {
            exit = sqlite3_exec(NULL, NULL, NULL, NULL, &fileError);
        }
        std::string line;
        std::getline(file, line);
        while (getline(file, line))
        {
            std::istringstream iss(line);
            std::string value;
            std::ostringstream oss_sql;
            int counter = 0;
            while (getline(iss, value, '\t')) {
                if (counter != 0 and datamap[counter] != -1) oss_sql << ", ";
                if (value == "\\N" and datamap[counter] != -1) oss_sql << "NULL";
                else if (datamap[counter] == 0) oss_sql << "'" << value << "'";
                else if (datamap[counter] == 1) oss_sql << value;
                else if (datamap[counter] == 2) 
                {
                    oss_sql << (value == "1" ? "TRUE" : "FALSE");
                } 
                counter++;
            }
            std::string insert = oss_sql.str();
            std::string to_format = this->queryMap.at(table);
            std::string formatted = to_format + insert + ");";
            this->sql_exec(formatted, NULL, NULL);
        }
    }
private:
    sqlite3* db;
    int exit;
    const std::unordered_map<std::string, std::string> queryMap = {
        {"name", "INSERT INTO name (nconst, primaryName, birthYear, deathYear, primaryProfession, knownForTitles) VALUES ("},
        {"media", "INSERT INTO media (tconst, titleType, primaryTitle, isAdult, startYear, endYear, runtimeMinutes, genres) VALUES ("},
        {"profs", "INSERT INTO profs (tconst, nconst, category, prof, characters) VALUES ("},
        {"directors", "INSERT INTO directors (tconst, directors) VALUES ("},
        {"ratings", "INSERT INTO ratings (tconst, averageRating, numvotes) VALUES ("}
    };
    const std::unordered_map<std::string, std::vector<int>> dataMap = {
        {"name", {0, 0, 1, 1, 0, 0}},
        {"media", {0, 0, 0, -1, 2, 1, 1, 1, 0}},
        {"profs", {0, -1, 0, 0, 0, 0}},
        {"directors", {0, 0, -1}},
        {"ratings", {0, 1, 1}}
    };
};