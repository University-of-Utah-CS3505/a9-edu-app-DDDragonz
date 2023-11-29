#ifndef CHEMICAL_H
#define CHEMICAL_H

#include <QObject>
#include <QMap>
#include <QList>

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
    explicit Chemical(QString cName, QString formula, QString sName, double pH, QString note, QString state);

    explicit Chemical(const Chemical& other);

    Chemical& operator=(const Chemical& other);

    /// @brief Getter for chemical's common name
    /// @return Returns the chemical's common name as a QString
    QString getCommonName();

    /// @brief Getter for chemical's formula
    /// @return Returns the chemical's formula as a QString
    QString getFormula();

    /// @brief Getter for chemical's systematic name
    /// @return Returns the chemical's systematic name as a Qstring
    QString getSystematicName();

    /// @brief Getter for chemical's pH
    /// @return Returns the chemical's pH as a double if applicable, otherwise returns -1
    double getPH();

    /// @brief Getter for any notes associated with the chemical
    /// @return Returns note as a QString
    QString getNote();

    /// @brief Getter for the state of the chemical at STP
    /// @return Returns state of chemical as QString
    QString getState();

    /// @brief Adds a list of products resulting with this Chemcial's reaction to the provided chemical
    /// @param Formula of chemical this chemical is reacting with
    /// @param List of Chemicals that will be produced from the reaction
    void addReaction(QString chemical, QList<Chemical> products);

    /// @brief Returns a list of chemical's that are produced when this chemical reacts with the provided chemical
    /// @param The formula of the chemical that will react with this chemical
    /// @return Returns the products of the reaction as a QList<Chemical>
    QList<Chemical> getReactions(QString chemical);

private:
    QString m_commonName;
    QString m_formula;
    QString m_systematicName;
    QMap<QString, QList<Chemical>> m_reactions;
    double m_pH;
    QString m_state;
    QString m_note;
};

#endif // CHEMICAL_H
