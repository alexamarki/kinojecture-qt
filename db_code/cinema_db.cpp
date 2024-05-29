#include <iostream>
#include "cinema_db.h"  // Теперь мы используем объединенный заголовочный файл

int main() {
    {
        MovieDB movieDB("../data/game.db");

        // Сортировка по рейтингу и вывод первых 15 строк
        std::vector<QString> sorted_movies_by_rating = movieDB.sort_by_rating();
        std::cout << "Top 15 movies sorted by rating:" << std::endl;
        movieDB.print_first_15(sorted_movies_by_rating);

        // Фильтрация по жанру и вывод первых 15 строк
        std::vector<QString> filtered_movies_by_genre = movieDB.filter_by_genre("Action");
        std::cout << "\nTop 15 Action movies:" << std::endl;
        movieDB.print_first_15(filtered_movies_by_genre);
    }

    {
        PeopleDB peopleDB("../data/game.db");

        // Сортировка по году рождения и вывод первых 15 строк
        std::vector<QString> sorted_people_by_birthYear = peopleDB.sort_by_birthYear();
        std::cout << "\nTop 15 people sorted by birth year:" << std::endl;
        peopleDB.print_first_15(sorted_people_by_birthYear);

        // Фильтрация по работе и вывод первых 15 строк
        std::vector<QString> filtered_people_by_job = peopleDB.filter_by_job("Director");
        std::cout << "\nTop 15 Directors:" << std::endl;
        peopleDB.print_first_15(filtered_people_by_job);
    }

    return 0;
}
