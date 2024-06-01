#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QString>
#include <QVariant>
#include <QFile>
#include <QIODevice>
#include <filesystem>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <iostream>

/**
 * A brief history of JavaDoc-style (C-style) comments.
 *
 * This is the typical JavaDoc-style C-style comment. It starts with two
 * asterisks.
 *
 * @param theory Even if there is only one possible unified theory. it is just a
 *               set of rules and equations.
 */

class LeaderboardDB 
{
public:
    LeaderboardDB(const QString& db_path = "../data/leaderboard.db");
    /**
     * hello
     * bye
    */
    ~LeaderboardDB();

    void createTable();
    void sql_exec(const QString& query);
    void replace_player_data(const QString& filepath);
    void merge_player_data(const QString& filepath);
    bool is_player_in_leaderboard(const QString& uuid);
    void add_player(const QString& uuid, const QString& nickname, int rating = 0, int games_played = 1);
    void update_player_rating(const QString& uuid, int rating_points);
    void save_database(const std::string& filepath);
    void rename_player(const QString& uuid, const QString& new_nickname);
    QSqlDatabase getDB();


private:
    QSqlDatabase db;
    static std::vector<QString> query_to_vector(QSqlQuery& query);
};

#endif