#ifndef CHEMICAL_H
#define CHEMICAL_H

#include <QObject>
#include <QMap>
#include <QList>
#include <QColor>

enum class State {gas, liquid, solid, aqueous};

class Chemical
{
public:
    /// @brief Constructor for Chemical
    /// @param formula Chemical's chemical formula
    /// @param state Chemical's state at STP, should be a solid, liquid, or gas
    /// @param color The color of the chemical
    explicit Chemical(QString formula, State state, QColor color);

    /// @brief Copy Constructor Operator
    Chemical(const Chemical& other);

    /// @brief Assignment Operator
    Chemical& operator=(const Chemical& other);

    /// @brief Getter for chemical's formula
    /// @return Returns the chemical's formula as a QString
    QString getFormula() const;

    /// @brief Getter for the state of the chemical at STP
    /// @return Returns state of chemical as QString
    State getState() const;

    /// @brief Getter for the color of the solid
    /// @return the color of the solid
    QColor getColorOfSolid() const;

private:
    QString m_formula;
    State m_state;
    QColor m_colorOfSolid;
};

#endif // CHEMICAL_H
