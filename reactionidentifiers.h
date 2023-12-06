#ifndef REACTIONIDENTIFIERS_H
#define REACTIONIDENTIFIERS_H

#include <QWidget>

namespace Ui {
class ReactionIdentifiers;
}

class ReactionIdentifiers : public QWidget
{
    Q_OBJECT

public:
    explicit ReactionIdentifiers(QWidget *parent = nullptr);
    ~ReactionIdentifiers();

private:
    Ui::ReactionIdentifiers *ui;

public slots:
    void mixSelected();
    void doneMixingSelected();
    void submitSelected();

signals:
    void sendIdentifiers(QString identifiers);
};

#endif // REACTIONIDENTIFIERS_H
