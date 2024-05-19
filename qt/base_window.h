#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QStackedWidget>
#include <QMainWindow>
#include <QObject>
#include <QtGui>
#include "../build/ui_base_window.h"

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
        //main buttons
        QObject::connect(ui.main_button, SIGNAL(clicked()), this, SLOT(MainPage()));
        QObject::connect(ui.start_button, SIGNAL(clicked()), this, SLOT(NewGame()));
        QObject::connect(ui.leaderboard_button, SIGNAL(clicked()), this, SLOT(Leaderboard()));
        QObject::connect(ui.settings_button, SIGNAL(clicked()), this, SLOT(Settings()));

        //new game buttons
        QObject::connect(ui.movie_mode_button, SIGNAL(clicked()), this, SLOT(Movies()));

    }

    ~MainWindow() = default;

private:
    Ui::Form ui;
public slots:
    void MainPage()
    {
        ui.stackedWidget->setCurrentWidget(ui.Kinojecture);
    }
    void NewGame()
    {
        ui.stackedWidget->setCurrentWidget(ui.NewGame);
    }
    void Leaderboard()
    {
        ui.stackedWidget->setCurrentWidget(ui.Leaderboard);
    }
    void Settings()
    {
        ui.stackedWidget->setCurrentWidget(ui.Settings);
    }
    void Movies()
    {
        ui.stackedWidget->setCurrentWidget(ui.Movies);
    }
};
}
QT_END_NAMESPACE

#endif
