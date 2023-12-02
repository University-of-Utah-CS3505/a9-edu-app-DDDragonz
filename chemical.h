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
    /// @param cName Chemical's common name
    /// @param formula Chemical's chemical formula
    /// @param sName Chemical's systematic name
    /// @param pH Chemical's pH if in liquid state, -1 if not applicable
    /// @param note Any notes about Chemical that should be displayed when user clicks for more information
    /// @param state Chemical's state at STP, should be a solid, liquid, or gas
    explicit Chemical(QString formula, State state, QColor color);

    explicit Chemical(const Chemical& other);

    Chemical& operator=(const Chemical& other);

    /// @brief Getter for chemical's formula
    /// @return Returns the chemical's formula as a QString
    QString getFormula() const;

    /// @brief Getter for the state of the chemical at STP
    /// @return Returns state of chemical as QString
    State getState() const;

    QColor getColorOfSolid() const;

private:
    QString m_formula;
    State m_state;
    QColor m_colorOfSolid;
};

#endif // CHEMICAL_H
