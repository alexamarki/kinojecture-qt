#include "helper.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <set>

int main() {
    // Step 1: trimming data
    // 1.1: trim ratings
    // std::ifstream inputFile("../helper_src/data/title.ratings.tsv");
    // std::ofstream outputFile("../helper_src/data/title.ratings_2.tsv");
    // std::vector<std::string> acceptableMovies;
    // if (!inputFile) {
    //     std::cerr << "Error opening input file." << std::endl;
    //     return 1;
    // }
    // std::string line;
    // getline(inputFile, line);
    // outputFile << line << std::endl;
    // while (getline(inputFile, line)) {
    //     std::stringstream ss(line);
    //     std::string element;
    //     std::vector<std::string> elements;
    //     while (getline(ss, element, '\t')) {
    //         elements.push_back(element);
    //     }
    //     if (std::stod(elements[2]) >= 100000) {
    //         acceptableMovies.push_back(elements[0]);
    //         outputFile << line << std::endl;
    //     }
    // }
    // inputFile.close();
    // outputFile.close();
    // 1.2: trim movies by ratings
    // std::ifstream inputFile2("../helper_src/data/title.basics.tsv");
    // std::ofstream outputFile2("../helper_src/data/title.basics_2.tsv");
    // if (!inputFile2) {
    //     std::cerr << "Error opening input file." << std::endl;
    //     return 1;
    // }
    // getline(inputFile2, line);
    // outputFile2 << line << std::endl;
    // while (getline(inputFile2, line)) {
    //     std::stringstream ss(line);
    //     std::string element;
    //     std::vector<std::string> elements;
    //     while (getline(ss, element, '\t')) {
    //         elements.push_back(element);
    //     }
    //     if (std::find(acceptableMovies.begin(), acceptableMovies.end(), 
    //         elements[0]) != acceptableMovies.end()) {
    //         outputFile2 << line << std::endl;
    //     }
    // }
    // inputFile2.close();
    // outputFile2.close();
    // std::ifstream inputFile3("../helper_src/data/title.crew.tsv");
    // std::ofstream outputFile3("../helper_src/data/title.crew_2.tsv");
    // if (!inputFile3) {
    //     std::cerr << "Error opening input file." << std::endl;
    //     return 1;
    // }
    // getline(inputFile3, line);
    // outputFile3 << line << std::endl;
    // while (getline(inputFile3, line)) {
    //     std::stringstream ss(line);
    //     std::string element;
    //     std::vector<std::string> elements;
    //     while (getline(ss, element, '\t')) {
    //         elements.push_back(element);
    //     }
    //     if (std::find(acceptableMovies.begin(), acceptableMovies.end(), 
    //         elements[0]) != acceptableMovies.end()) {
    //         outputFile3 << line << std::endl;
    //     }
    // }
    // inputFile3.close();
    // outputFile3.close();
    // std::ifstream inputFile4("../helper_src/data/title.principals.tsv");
    // std::ofstream outputFile4("../helper_src/data/title.principals_2.tsv");
    // if (!inputFile4) {
    //     std::cerr << "Error opening input file." << std::endl;
    //     return 1;
    // }
    // getline(inputFile4, line);
    // outputFile4 << line << std::endl;
    // while (getline(inputFile4, line)) {
    //     std::stringstream ss(line);
    //     std::string element;
    //     std::vector<std::string> elements;
    //     while (getline(ss, element, '\t')) {
    //         elements.push_back(element);
    //     }
    //     if (std::find(acceptableMovies.begin(), acceptableMovies.end(), 
    //         elements[0]) != acceptableMovies.end()) {
    //         outputFile4 << line << std::endl;
    //     }
    // }
    // inputFile4.close();
    // outputFile4.close();
    // std::ifstream inputFile45("../helper_src/data/title.principals_2.tsv");
    // std::ofstream outputFile45("../helper_src/data/title.principals_3.tsv");
    // if (!inputFile45) {
    //     std::cerr << "Error opening input file." << std::endl;
    //     return 1;
    // }
    // getline(inputFile45, line);
    // while (getline(inputFile45, line)) {
    //     std::stringstream ss(line);
    //     std::string element;
    //     std::vector<std::string> elements;
    //     while (getline(ss, element, '\t')) {
    //         elements.push_back(element);
    //     }
    //     if (elements[3] == "director" || elements[3] == "composer" 
    //         || elements[3] == "actor" || elements[3] == "actress") {
    //         outputFile45 << line << std::endl;
    //     }
    // }
    // inputFile45.close();
    // outputFile45.close();
    // std::set<std::string> acceptableNames;
    // std::ifstream inputFile5("../helper_src/data/title.principals_3.tsv");
    // if (!inputFile5) {
    //     std::cerr << "Error opening input file." << std::endl;
    //     return 1;
    // }
    // getline(inputFile5, line);
    // while (getline(inputFile5, line)) {
    //     std::stringstream ss(line);
    //     std::string element;
    //     std::vector<std::string> elements;
    //     while (getline(ss, element, '\t')) {
    //         elements.push_back(element);
    //     }
    //     if (std::find(acceptableMovies.begin(), acceptableMovies.end(), 
    //         elements[0]) != acceptableMovies.end()) {
    //         acceptableNames.insert(elements[2]);
    //     }
    // }
    // inputFile5.close();
    // std::ifstream inputFile6("../helper_src/data/name.basics.tsv");
    // std::ofstream outputFile6("../helper_src/data/name.basics_2.tsv");
    // if (!inputFile6) {
    //     std::cerr << "Error opening input file." << std::endl;
    //     return 1;
    // }
    // getline(inputFile6, line);
    // outputFile6 << line << std::endl;
    // while (getline(inputFile6, line)) {
    //     std::stringstream ss(line);
    //     std::string element;
    //     std::vector<std::string> elements;
    //     while (getline(ss, element, '\t')) {
    //         elements.push_back(element);
    //     }
    //     if (std::find(acceptableNames.begin(), acceptableNames.end(), 
    //         elements[0]) != acceptableNames.end()) {
    //         outputFile6 << line << std::endl;
    //     }
    // }
    // inputFile6.close();
    // outputFile6.close();
    // Step 2: initiating DB
    // HelperDB helper_db;
    // helper_db.createTables();
    // helper_db.add_file_data("../helper_src/data/title.ratings_2.tsv", "ratings");
    // helper_db.add_file_data("../helper_src/data/name.basics_2.tsv", "name");
    // helper_db.add_file_data("../helper_src/data/title.basics_2.tsv", "media");
    // helper_db.add_file_data("../helper_src/data/title.principals_3.tsv", "profs");
    // helper_db.add_file_data("../helper_src/data/title.crew_2.tsv", "directors");
    HelperDB gameData_db("../data/game.db");
    std::string create_people = "CREATE TABLE IF NOT EXISTS people("
                                "nconst TEXT PRIMARY KEY,"
                                "primaryName TEXT,"
                                "birthYear INT,"
                                "deathYear INT,"
                                "job TEXT,"
                                "knownFor TEXT"
                                ");";
    std::string create_movies = "CREATE TABLE IF NOT EXISTS movies("
                                "tconst TEXT PRIMARY KEY,"
                                "titleType TEXT,"
                                "primaryTitle TEXT,"
                                "genres TEXT,"
                                "startYear INT,"
                                "endYear INT,"
                                "runtimeMinutes INT,"
                                "averageRating REAL"
                                ");";
    std::string create_peopletomovies = "CREATE TABLE IF NOT EXISTS peopleToMovies("
                                        "id INT PRIMARY KEY,"
                                        "relationship TEXT,"
                                        "character TEXT,"
                                        "tconst TEXT,"
                                        "nconst TEXT,"
                                        "FOREIGN KEY(tconst) REFERENCES Movies(tconst),"
                                        "FOREIGN KEY(nconst) REFERENCES People(nconst)"
                                        ");";
    gameData_db.sql_exec(create_people, NULL, NULL);
    gameData_db.sql_exec(create_movies, NULL, NULL);
    gameData_db.sql_exec(create_peopletomovies, NULL, NULL);
    std::string connect_to_og = "ATTACH DATABASE '../data/im.db' AS og_db;";
    gameData_db.sql_exec(connect_to_og, NULL, NULL);
    std::string populate_people = "INSERT INTO people (nconst, primaryName,"
                                    " birthYear, deathYear, job, knownFor) SELECT nconst, "
                                    "primaryName, birthYear, deathYear, "
                                    "primaryProfession, knownForTitles FROM og_db.name;";
    std::string media_w_ratings = "CREATE TEMP TABLE temp_media AS SELECT "
                                    "m.tconst, m.titleType, m.primaryTitle, "
                                    "m.genres, m.startYear, m.endYear, "
                                    "m.runtimeMinutes, r.averageRating "
                                    "FROM og_db.media m "
                                    "JOIN og_db.ratings r ON m.tconst = r.tconst;";
    std::string populate_movies = "INSERT INTO movies (tconst, titleType, "
                                    "primaryTitle, genres, startYear, endYear, "
                                    "runtimeMinutes, averageRating) "
                                    "SELECT tconst, titleType, primaryTitle, genres, "
                                    "startYear, endYear, runtimeMinutes, averageRating "
                                    "FROM temp_media;";
    gameData_db.sql_exec(populate_people, NULL, NULL);
    gameData_db.sql_exec(media_w_ratings, NULL, NULL);
    gameData_db.sql_exec(populate_movies, NULL, NULL);
    std::string easy_profs_population = "INSERT INTO peopleToMovies (relationship, character, "
                                        "tconst, nconst) SELECT category, characters, tconst, "
                                        "nconst FROM og_db.profs;";
    gameData_db.sql_exec(easy_profs_population, NULL, NULL);
}