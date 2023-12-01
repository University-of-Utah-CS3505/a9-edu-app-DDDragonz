#include "level.h"
#include "ui_level.h"
#include "questionwindow.h"

Level::Level(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Level)
{
    ui->setupUi(this);
    connect(ui->nextLevel, &QPushButton::clicked, this, &Level::getToNextLevel);
}

void Level::getLevel(int level)
{
    this->ui->level->setText(&"Level" [ level]);
    emit sendLevel(level);
}

void Level::getToNextLevel()
{
    QuestionWindow window(this);
    connect(this, &Level::sendLevel, &window, &QuestionWindow::getLevel);
    connect(&window, &QuestionWindow::levelUp, this, &Level::getLevelUp);
    window.show();
}

void Level::getLevelUp()
{
    emit nextLevel();
}

Level::~Level()
{
    delete ui;
}
