#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QStackedWidget>
#include <QMainWindow>
#include <QObject>
#include <QtGui>
#include "hoverpushbutton.h"
#include "../controller/movie_controller.h"
#include "../controller/people_controller.h"
#include "../controller/game_controller.h"
#include "../build/ui_base_window.h"
#include <QSqlTableModel>
#include <QStringList>
#include "../game_logic/proxy_model.h"
#include "../game_logic/game_model.h"
#include "../db_code/cinema_db.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr)
    : QMainWindow(parent)
    {
        ui.setupUi(this);
        selectedCards.resize(25, false);
        this->movieController = new MovieController(this);
        this->controller = new Controller(this);
        // this->peopleController = new PeopleController(this);
        connect(ui.main_button, &QPushButton::clicked, this, &MainWindow::MainPage);
        // Main buttons
        connect(ui.main_button, &QPushButton::clicked, this, &MainWindow::MainPage);
        connect(ui.start_button, &QPushButton::clicked, this, &MainWindow::NewGame);
        // connect(ui.leaderboard_button, &QPushButton::clicked, this, &MainWindow::Leaderboard);
        connect(ui.leaderboard_button, &QPushButton::clicked, movieController, &MovieController::printHI);
        connect(ui.settings_button, &QPushButton::clicked, this, &MainWindow::Settings);
        
        connect(controller, &Controller::showTurnOverScreen, this, &MainWindow::callTurnOverScreen);
        connect(controller, &Controller::promptLowerFailPopup, this, &MainWindow::callFailPopup);

        // Table show buttons
        connect(ui.show_table_movies_button, &QPushButton::clicked, this, &MainWindow::ShowTableMovies);
        connect(ui.show_table_actors_button, &QPushButton::clicked, this, &MainWindow::ShowTableActors);
        connect(ui.show_table_directors_button, &QPushButton::clicked, this, &MainWindow::ShowTableDirectors);
        connect(ui.show_table_composers_button, &QPushButton::clicked, this, &MainWindow::ShowTableComposers);
        
        connect(ui.card_num_button_2, &QPushButton::clicked, this, &MainWindow::GameFieldLoad);
        connect(ui.ready_button, &QPushButton::clicked, controller, &Controller::onTurnOverEnd); 
        connect(controller, &Controller::showGameScreen, this, &MainWindow::GameFieldLoad);

        // Filter buttons
        connect(ui.choose_media_type, &QLineEdit::textChanged, [this]() {
            movieController->filterByTitleType(ui.choose_media_type->text());
        });
        connect(ui.choose_genre, &QLineEdit::textChanged, [this]() {
            movieController->filterByGenres(ui.choose_genre->text());
        });
        connect(ui.choose_title, &QLineEdit::textChanged, [this]() {
            movieController->filterByPrimaryTitle(ui.choose_title->text());
        });
        connect(ui.choose_runtime, &QSpinBox::valueChanged, [this]() {
            movieController->filterByRuntime(ui.choose_runtime->value(), true);
        });
        connect(ui.choose_year_before, &QSpinBox::valueChanged, [this]() {
            movieController->filterByYearRange(ui.choose_year_before->value(), false);
        });
        connect(ui.choose_year_after, &QSpinBox::valueChanged, [this]() {
            movieController->filterByYearRange(ui.choose_year_after->value(), true);
        });
        connect(ui.choose_rating_below, &QDoubleSpinBox::valueChanged, [this]() {
            movieController->filterByAverageRating(ui.choose_rating_below->value(), false);
        });
        connect(ui.choose_rating_above, &QDoubleSpinBox::valueChanged, [this]() {
            movieController->filterByAverageRating(ui.choose_rating_above->value(), true);
        });

        // for people; have to generalise the ppl functions so that we use the same ui but with a different additional filter each time
        // connect(ui.choose_name, &QLineEdit::textChanged, [this]() {
        //     peopleController->filterByPrimaryName(ui.choose_name->text());
        // });
        // connect(ui.choose_job, &QLineEdit::textChanged, [this]() {
        //     peopleController->filterByJob(ui.choose_job->text());
        // });
        // connect(ui.choose_born_before, &QSpinBox::valueChanged, [this]() {
        //     movieController->filterByBirthYear(ui.choose_year_before->value(), false);
        // });
        // connect(ui.choose_born_after, &QSpinBox::valueChanged, [this]() {
        //     movieController->filterByBirthYear(ui.choose_year_after->value(), true);
        // });

        // Submit to game engine buttons
        connect(ui.submit_movies_button, &QPushButton::clicked, this, &MainWindow::SubmitMovies);
        //connect(ui.submit_people_button, &QPushButton::clicked, this, &MainWindow::SubmitPeople);

        // New game buttons
        connect(ui.movie_mode_button, &QPushButton::clicked, this, &MainWindow::Movies);
        connect(ui.actors_mode_button, &QPushButton::clicked, this, &MainWindow::Actors);
        connect(ui.directors_mode_button, &QPushButton::clicked, this, &MainWindow::Directors);
        connect(ui.composers_mode_button, &QPushButton::clicked, this, &MainWindow::Composers);

        // Card buttons
        for (int i = 0; i < 25; ++i) {
            QString buttonName = QString("cardButton%1").arg(i + 1);
            HoverPushButton *button = this->findChild<HoverPushButton *>(buttonName);
            if (button) {
                button->setCheckable(true);
                button->setStyleSheet("background-color: lightgrey;");
                connect(button, &HoverPushButton::clicked, this, &MainWindow::CardSelection);
                connect(button, &HoverPushButton::hovered, this, &MainWindow::changeCardInfoOnHover);
                connect(button, &HoverPushButton::unhovered, this, &MainWindow::resetCardInfo);
            }
        }

        // Guess button
        connect(ui.guessButton, &QPushButton::clicked, this, &MainWindow::processGuess);

        //before game a lot of buttons
        connect(ui.from_rules_button, &QPushButton::clicked, this, &MainWindow::PrePlayer1);
        connect(ui.show_fpc, &QPushButton::clicked, this, &MainWindow::showPlayerCard);
        connect(ui.card_num_button, &QPushButton::clicked, this, &MainWindow::PrePlayer2);
        connect(ui.show_spc, &QPushButton::clicked, this, &MainWindow::showSecondPlayerCard);
    }

    ~MainWindow() = default;

private:
    Ui::Form ui;
    MovieController *movieController;
    //PeopleController *peopleController;
    Controller *controller;
    QTableView* movieTableView;
    std::vector<std::pair<std::string, std::string>> selectedMovies;
    std::vector<bool> selectedCards;

public slots:
    void MainPage() {
        ui.stackedWidget->setCurrentWidget(ui.Kinojecture);
    }
    void NewGame() {
        // ui.stackedWidget->setCurrentWidget(ui.GameField);
        ui.stackedWidget->setCurrentWidget(ui.NewGame);
    }
    void Leaderboard() {
        ui.stackedWidget->setCurrentWidget(ui.Leaderboard);
    }
    void Settings() {
        ui.stackedWidget->setCurrentWidget(ui.Settings);
    }
    void Movies() {
        ui.stackedWidget->setCurrentWidget(ui.Movies);
    }
    void Actors() {
        ui.stackedWidget->setCurrentWidget(ui.Actors);
    }
    void Directors() {
        ui.stackedWidget->setCurrentWidget(ui.Directors);
    }
    void Composers() {
        ui.stackedWidget->setCurrentWidget(ui.Composers);
    }
    void onCellClicked(const QModelIndex &index) {
        if (!index.isValid()) return;

        QItemSelectionModel *selectionModel = movieTableView->selectionModel();
        QString cellValue = index.sibling(index.row(), 2).data().toString();
        //1, 3, 4, 5, 6, 7
        QString cellValue_data = index.sibling(index.row(), 1).data().toString() + " " + index.sibling(index.row(), 3).data().toString() + " " +
                            index.sibling(index.row(), 4).data().toString() + " " + index.sibling(index.row(), 5).data().toString() + " " +
                            index.sibling(index.row(), 6).data().toString() + " " + index.sibling(index.row(), 7).data().toString();
        std::pair<std::string, std::string> pair_cell = {cellValue.toStdString(), cellValue_data.toStdString()};
        auto it = std::find(selectedMovies.begin(), selectedMovies.end(), pair_cell);
        if (it != selectedMovies.end()) {
            selectedMovies.erase(it);
            selectionModel->select(index, QItemSelectionModel::Deselect | QItemSelectionModel::Rows);
        } else {
            selectedMovies.push_back(pair_cell);
            selectionModel->select(index, QItemSelectionModel::Select | QItemSelectionModel::Rows);
        }
    }
    void SubmitMovies() {
        if (selectedMovies.size() != 25)
            return;
        ui.main_widget->setCurrentWidget(ui.game_mode);
        ui.game_pages->setCurrentWidget(ui.rules_page);
        controller->startGame(selectedMovies);
    }
    void ShowTableMovies() {
        movieTableView = new QTableView(this);
        ProxyModel *model = movieController->getModelDirect();
        QVBoxLayout *layout = qobject_cast<QVBoxLayout *>(ui.verticalLayoutWidget->layout());
        // if (!layout) {
        //     layout = new QVBoxLayout(ui.verticalLayoutWidget);
        //     ui.verticalLayoutWidget->setLayout(layout);
        // }
        movieTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        movieTableView->setModel(model);
        movieTableView->setSortingEnabled(true);
        // movieTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        movieTableView->setSelectionMode(QAbstractItemView::MultiSelection);
        connect(movieTableView, &QTableView::clicked, this, &MainWindow::onCellClicked);
        layout->addWidget(movieTableView);
        movieTableView->show();
        ui.tableMovies->setCurrentWidget(ui.table_show);
    }
    // void ShowTablePeople(QString argument) {
    //     peopleTableView = new QTableView(this);
    //     ProxyModel *model = peopleController->getModelDirect();
    //     QVBoxLayout *layout = qobject_cast<QVBoxLayout *>(ui.verticalLayoutWidget->layout());
    //     if (!layout) {
    //         layout = new QVBoxLayout(ui.verticalLayoutWidget);
    //         ui.verticalLayoutWidget->setLayout(layout);
    //     }
    //     peopleTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //     peopleTableView->setModel(model);
    //     peopleTableView->setSortingEnabled(true);
    //     layout->addWidget(peopleTableView);
    //     peopleTableView->show();
    //     ui.tablePeople->setCurrentWidget(ui.table_show_p);
    // }
    void ShowTableActors() {
        ui.tableActors->setCurrentWidget(ui.table_show_a);
    }
    void ShowTableDirectors() {
        ui.tableDirectors->setCurrentWidget(ui.table_show_d);
    }
    void ShowTableComposers() {
        ui.tableComposers->setCurrentWidget(ui.table_show_c);
    }
    void GameFieldLoad() {
        ui.main_widget->setCurrentWidget(ui.not_game);
        ui.stackedWidget->setCurrentWidget(ui.GameField);
        bool primaryPlayer = controller->getPlayerTurn();
        std::unordered_set<int> loweredCards = controller->getLowered(primaryPlayer);
        this->loadCards(loweredCards);
    }
    void CardSelection() {
        HoverPushButton *button = qobject_cast<HoverPushButton *>(sender());
        if (button) {
            int index = button->objectName().remove("cardButton").toInt() - 1;
            selectedCards[index] = !selectedCards[index];

            if (selectedCards[index]) {
                button->setStyleSheet("background-color: blue;");
                controller->onCardSelected(index);
            } else {
                button->setStyleSheet("background-color: lightgrey;");
                controller->onCardDeselected(index);
            }
        }
    }
    void changeCardInfoOnHover() {
        HoverPushButton *button = qobject_cast<HoverPushButton *>(sender());
        if (button) {
            QString buttonName = button->objectName();
            bool ok;
            int index = buttonName.remove("cardButton").toInt(&ok);
            if (ok && index >= 1 && index <= 25) {
                index -= 1;
                button->setText(QString::fromStdString(controller->model->dataList[index].second));
            }
        }
    }
    void resetCardInfo() {
        HoverPushButton *button = qobject_cast<HoverPushButton *>(sender());
        if (button) {
            QString buttonName = button->objectName();
            bool ok;
            int index = buttonName.remove("cardButton").toInt(&ok);
            if (ok && index >= 1 && index <= 25) {
                index -= 1;
                button->setText(QString::fromStdString(controller->model->dataList[index].first));
            }
        }
    }
    void processGuess() {
        this->clearGameFieldSelection();
        controller->onCardsLowered();
    }
    void callTurnOverScreen() {
        ui.main_widget->setCurrentWidget(ui.game_mode);
        ui.game_pages->setCurrentWidget(ui.turnover);
        qDebug() << "turn over screen";
    }
    void callFailPopup() {
        this->GameFieldLoad();
        qDebug() << "fail popup";
    }
    void clearGameFieldSelection() {
        for (int i = 0; i < 25; ++i) {
            QString buttonName = QString("cardButton%1").arg(i + 1);
            HoverPushButton *button = this->findChild<HoverPushButton *>(buttonName);
            button->setText(QString::fromStdString(controller->model->dataList[i].first));
            if (button) {
                button->setStyleSheet("background-color: lightgrey;");
                button->setEnabled(true);
            }
        }
        selectedCards.assign(25, false);
    }
    void loadCards(std::unordered_set<int> loweredCards) {
        for (int i = 0; i < 25; ++i) {
            if (loweredCards.contains(i)) {
                QString buttonName = QString("cardButton%1").arg(i + 1);
                HoverPushButton *button = this->findChild<HoverPushButton *>(buttonName);
                button->setText(QString::fromStdString(controller->model->dataList[i].first));
                if (button) {
                    button->setStyleSheet("background-color: black;");
                    button->setEnabled(false);
                }
            }
        }
    }
    void showPlayerCard() {
        ui.game_pages->setCurrentWidget(ui.player_card1);
        ui.card_number->setText(QString::fromStdString(controller->model->dataList[controller->getRandomisedCards().first].first));
    }
    void showSecondPlayerCard() {
        ui.game_pages->setCurrentWidget(ui.player_card2);
        ui.card_number_2->setText(QString::fromStdString(controller->model->dataList[controller->getRandomisedCards().second].first));
    }
    void PrePlayer1() {
        ui.game_pages->setCurrentWidget(ui.pre_player_card1);
    }
    void PrePlayer2() {
        ui.game_pages->setCurrentWidget(ui.pre_player_card2);
    }
};
}
QT_END_NAMESPACE

#endif // MAINWINDOW_H