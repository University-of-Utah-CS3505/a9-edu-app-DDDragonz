#ifndef QUESTIONWINDOW_H
#define QUESTIONWINDOW_H

#include <QWidget>

namespace Ui {
class QuestionWindow;
}

class QuestionWindow : public QWidget
{
    Q_OBJECT

public:
    explicit QuestionWindow(QWidget *parent = nullptr);
    ~QuestionWindow();
    void showCurrentQuestion();

private:
    Ui::QuestionWindow *ui;
    int m_level;
    int m_currentQuestionIndex;

    struct Question {
        QString m_text;
        QStringList m_choices;
        int m_correctAnswerIndex;
    };

    QMap<int, QVector<Question>> m_questions;

    void loadQuestion();
    void addQuestion();

signals:
    void levelUp();

public slots:
    void getLevel(int level);
};

#endif // QUESTIONWINDOW_H
