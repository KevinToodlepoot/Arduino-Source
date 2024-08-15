#ifndef PokemonAutomation_PokemonSV_TeraSpeciesTable_H
#define PokemonAutomation_PokemonSV_TeraSpeciesTable_H

#include "Common/Cpp/Options/EditableTableOption.h"
#include "Common/Cpp/Options/SimpleIntegerOption.h"
#include "Common/Cpp/Options/StringSelectOption.h"

namespace PokemonAutomation{
namespace NintendoSwitch{
namespace PokemonSV{

class TeraSpeciesRow : public EditableTableRow{
public:
    TeraSpeciesRow();
    virtual std::unique_ptr<EditableTableRow> clone() const override;

public:
    StringSelectOption species;
};

class TeraSpeciesTable : public EditableTableOption<TeraSpeciesRow>{
public:
    TeraSpeciesTable(std::string label);

    // Whether pokemon_slug is among the selected pokemon
    bool find_species(const std::string& pokemon_slug) const;
    // Return the pokemon slugs that the user has selected via the opponent filter table UI.
    std::vector<std::string> selected_pokemon() const;

    virtual std::vector<std::string> make_header() const override;

    static std::vector<std::unique_ptr<EditableTableRow>> make_defaults();
};

} // namespace PokemonSV
} // namespace NintendoSwitch
} // namespace PokemonAutomation

#endif // PokemonAutomation_PokemonSV_TeraSpeciesTable_H