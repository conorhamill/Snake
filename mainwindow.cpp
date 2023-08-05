#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "board.h"

#include <Qtimer>
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    board = new Board(ui->widget_board);
    layout = new QHBoxLayout(ui->widget_board);
    layout->addWidget(board);
    board->setFixedSize(500,500);

    connect(mainTimer, &QTimer::timeout, this, MainWindow::timerMethod);
    mainTimer->start(100);
    ui->game_status_label->setText(board->getGameStatus());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timerMethod()
{

    if (board->getGameStatus() == "Game running")
    {
        ui->game_status_label->setText(board->getGameStatus());
        ui->score_label->setText(QString::number(board->getScore()));
        ui->time_label->setText(QString::number(board->getTime()));
        ui->solver_pushButton->setVisible(false);
    }
    if (board->getGameStatus() == "Game over. Press any key to reset.")
    {
        ui->game_status_label->setText(board->getGameStatus());
        board->setKeyPressEventEnabled(true);
        board->reset();
    }
    if (board->getGameStatus() == "Press any key to begin")
    {
        ui->game_status_label->setText(board->getGameStatus());
        ui->score_label->setText(QString::number(board->getScore()));
        ui->time_label->setText(QString::number(board->getTime()));
        board->setDifficulty(ui->difficulty_comboBox->currentText());
        ui->solver_pushButton->setVisible(true);
    }
}

void MainWindow::on_solver_pushButton_clicked()
{
    board->setKeyPressEventEnabled(false);
    board->runSolver();
    ui->solver_pushButton->setVisible(false);

}

