#include <string>
#include <vector>
#include <sqlite3.h>
#include <format>


struct People 
{
    std::string nconst;
    std::string primaryName;
    int birthYear;
    int deathYear;
    std::string job;
    std::string knownFor;
};

struct Movies 
{
    std::string tconst;
    std::string titleType;
    std::string primaryTitle;
    std::string genres;
    int startYear;
    int endYear;
    int runtimeMinutes;
    float averageRating;
};

struct PeopleToMovies 
{
    int id;
    std::string relationship;
    std::string character;
    std::string tconst;
    std::string nconst;
};

struct Leaderboard
{
    // TODO: @icyshub should put their struct Leaderboard code here upon merging leaderboard.cpp and .h with the main db file
};

class BasicDB
{
public:
    BasicDB(const std::string& db_path)
    {
        exit = sqlite3_open(db_path.c_str(), &db);
    }
    ~BasicDB() 
    {
        sqlite3_close(db);
    }
    void createTables(std::vector<std::string> creation_queries) 
    {
        char* creationError;
        for (auto query : creation_queries)
            exit = sqlite3_exec(this->db, query.c_str(), NULL, NULL, &creationError);
    }
protected:
    sqlite3* db;
    int exit;
};

class CinemaDB : BasicDB
{
    std::string query_builder_base(std::vector<std::string> ) 
    {

    }
};

class LeaderboardDB : BasicDB
{
    // TODO: @icyshub should port their LeaderboardDB code here
};