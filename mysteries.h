#ifndef MYSTERIES_H
#define MYSTERIES_H

#include <QString>
#include <vector>

using std::vector;

class Mysteries
{
public:
    /// @brief Creates the mysteries
    /// @param chemicals The chemicals that the mysteris first starts out with
    Mysteries(vector<QString> chemicals);

    /// @brief Adds a chemical to the mysteries
    /// @param chemical The chemical to be added
    void addChemical(QString chemical);

    /// @brief Checks if the chemicals in the given order are the correct order
    /// @param toCheck The chemicals given in the selected order
    /// @return always return true
    bool checkChemicals(vector<QString> toCheck);

    /// @brief Gets the name of a mystery substance
    /// @param mysteryName The mystery name of the substance (ie- Substance A)
    /// @return the chemical
    QString getChemical(QString mysteryName);

    /// @brief Gets the name of a mystery substance with the specified number
    /// @param number The number associated with the substance
    /// @return the position of the chemical
    QString getChemical(int number);

private:
    QString m_substances[6];    // May not be filled, m_size is the correct size
    int m_size;

    /// @brief Shuffles the order of the mysteries
    void shuffle();
};

#endif // MYSTERIES_H
