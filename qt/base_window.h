#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QStackedWidget>
#include <QMainWindow>
#include <QObject>
#include <QtGui>
#include "hoverpushbutton.h"
#include "../controller/movie_controller.h"
#include "../build/ui_base_window.h"
#include <QSqlTableModel>
#include <QStringList>
#include "../game_logic/proxy_model.h"
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
        
        // Main buttons
        connect(ui.main_button, &QPushButton::clicked, this, &MainWindow::MainPage);
        connect(ui.start_button, &QPushButton::clicked, this, &MainWindow::NewGame);
        // connect(ui.leaderboard_button, &QPushButton::clicked, this, &MainWindow::Leaderboard);
        connect(ui.leaderboard_button, &QPushButton::clicked, movieController, &MovieController::printHI);
        connect(ui.settings_button, &QPushButton::clicked, this, &MainWindow::Settings);
        
        // Table show buttons
        connect(ui.show_table_movies_button, &QPushButton::clicked, this, &MainWindow::ShowTableMovies);
        connect(ui.show_table_actors_button, &QPushButton::clicked, this, &MainWindow::ShowTableActors);
        connect(ui.show_table_directors_button, &QPushButton::clicked, this, &MainWindow::ShowTableDirectors);
        connect(ui.show_table_composers_button, &QPushButton::clicked, this, &MainWindow::ShowTableComposers);

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
    }

    ~MainWindow() = default;

private:
    Ui::Form ui;
    MovieController *movieController;
    QTableView* movieTableView;
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
    void ShowTableMovies() {
        movieTableView = new QTableView(this);
        // QAbstractItemModel *model = movieController->getModelDirect();
        CinemaDB *database = new CinemaDB();
        QSqlTableModel *model = new QSqlTableModel(nullptr, database->getDB());
        qDebug() << "before";
        model->setTable("movies");
        model->select();
        for (int i = 0; i < model->rowCount(); ++i) {
            // int startYear = model->record(i).value("startYear").toInt();
            // QString name = model->record(i).value("genre").toString();
            qDebug() << i;
        }
        qDebug() << model->rowCount();
        qDebug() << "after";
        QVBoxLayout *layout = qobject_cast<QVBoxLayout *>(ui.verticalLayoutWidget->layout());
        if (!layout) {
            layout = new QVBoxLayout(ui.verticalLayoutWidget);
            ui.verticalLayoutWidget->setLayout(layout);
        }

        
        
        movieTableView->setModel(model);
        layout->addWidget(movieTableView);
        movieTableView->show();
        


        // table for print
        
        int rowCount = model->rowCount();
        int columnCount = model->columnCount();
        

        // print
        for (int row = 0; row < rowCount; ++row) {
            std::cout << "|";
            for (int column = 0; column < columnCount; ++column) {
                QModelIndex index = model->index(row, column);
                QString data = model->data(index).toString();
                std::cout << " " << data.toStdString() << " |";
            }
            std::cout << "\n";
        }

        // normal part again
        ui.tableMovies->setCurrentWidget(ui.table_show);
    }
    void ShowTableActors() {
        ui.tableActors->setCurrentWidget(ui.table_show_a);
    }
    void ShowTableDirectors() {
        ui.tableDirectors->setCurrentWidget(ui.table_show_d);
    }
    void ShowTableComposers() {
        ui.tableComposers->setCurrentWidget(ui.table_show_c);
    }
    void CardSelection() {
        HoverPushButton *button = qobject_cast<HoverPushButton *>(sender());
        if (button) {
            int index = button->objectName().remove("cardButton").toInt() - 1;
            selectedCards[index] = !selectedCards[index];

            if (selectedCards[index]) {
                button->setStyleSheet("background-color: blue;");
            } else {
                button->setStyleSheet("background-color: lightgrey;");
            }
        }
    }
    void changeCardInfoOnHover() {
        HoverPushButton *button = qobject_cast<HoverPushButton *>(sender());
        if (button) {
            button->setText("Hovered!");
        }
    }
    void resetCardInfo() {
        HoverPushButton *button = qobject_cast<HoverPushButton *>(sender());
        if (button) {
            button->setText("");
        }
    }
    void processGuess() {
        for (int i = 0; i < 25; ++i) {
            if (selectedCards[i]) {
                QString buttonName = QString("cardButton%1").arg(i + 1);
                HoverPushButton *button = this->findChild<HoverPushButton *>(buttonName);
                if (button) {
                    button->setStyleSheet("background-color: black;");
                    button->setEnabled(false);
                }
            }
        }
    }
};
}
QT_END_NAMESPACE

#endif // MAINWINDOW_H