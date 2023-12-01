#include "questionwindow.h"
#include "ui_questionwindow.h"
#include <QRadioButton>
#include <QMessageBox>

QuestionWindow::QuestionWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QuestionWindow),
    m_level(0),
    m_currentQuestionIndex(0)
{
    ui->setupUi(this);
}

QuestionWindow::~QuestionWindow()
{
    delete ui;
}

void QuestionWindow::showCurrentQuestion()
{
    if(m_level != 0)
    {
        if(m_currentQuestionIndex < m_questions[m_level].size())
        {
            int correctAnswerIndex = m_questions[m_level][m_currentQuestionIndex].m_correctAnswerIndex;
            int chosenIndex = -1;
            int i = 0;
            foreach(QRadioButton *button, findChildren<QRadioButton *>())
            {
                if (button->isChecked())
                {
                    chosenIndex = i;
                    break;
                }
                ++i;
            }

            if (chosenIndex == correctAnswerIndex)
            {
                QMessageBox::information(this, "Correct", "That's the correct answer!");
                m_currentQuestionIndex ++;
                loadQuestion();
            }
            else
            {
                QMessageBox::warning(this, "Incorrect", "Sorry, that's the wrong answer.");
            }
        }
        else
        {
            QMessageBox::information(this, "Level Up", "Congratulations to next level!");
            emit levelUp();
        }
    }
}

void QuestionWindow::loadQuestion()
{
    if(m_level != 0 || m_currentQuestionIndex > m_questions[m_level].size())
    {
        return;
    }

    foreach(QRadioButton *button, findChildren<QRadioButton *>())
    {
        ui->choices->removeWidget(button);
        delete button;
    }

    Question question = m_questions[m_level][m_currentQuestionIndex];
    ui->question->setText(question.m_text);

    for (int i = 0; i < question.m_choices.size(); ++i)
    {
        QRadioButton *radioButton = new QRadioButton(question.m_choices[i]);
        ui->choices->addWidget(radioButton);
    }

}

void QuestionWindow::addQuestion()
{

}

void QuestionWindow::getLevel(int level)
{
    this->m_level = level;
}
