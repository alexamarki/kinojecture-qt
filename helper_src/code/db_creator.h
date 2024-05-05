#include <string>
#include <vector>
#include <sqlite3.h>
#include <format>

struct Movies {
    std::string tconst;
    std::string titleType;
    std::string primaryTitle;
    int startYear;
    int endYear;
    int runtimeMinutes;
    float averageRating;
    bool isAdult;
};

struct PeopleToMovies {
    int id;
    std::string relationship;
    std::string tconst;
    std::string nconst;
};

struct People {
    std::string nconst;
    std::string primaryName;
    int birthYear;
    int deathYear;
    std::string job;
    std::string characters;
};