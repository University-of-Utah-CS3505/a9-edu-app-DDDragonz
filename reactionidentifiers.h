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
    /// @brief Standard Constructor. Makes connections and sets up the ui
    explicit ReactionIdentifiers(QWidget *parent = nullptr);

    /// @brief Standard Deconstructor.
    ~ReactionIdentifiers();

private:
    Ui::ReactionIdentifiers *m_ui;

public slots:
    /// @brief Disable button
    void mixSelected();

    /// @brief Disable button
    void doneMixingSelected();

    /// @brief Creates a string of the selected identifiers
    void submitSelected();

signals:
    /// @brief Send the identifiers
    /// @param identifiers A string of the identifiers
    void sendIdentifiers(QString identifiers);
};

#endif // REACTIONIDENTIFIERS_H
