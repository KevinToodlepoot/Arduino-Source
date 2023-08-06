#ifndef POKEMONAUTOMATION_NINTENDOSWITCH_POKEMONSV_TERAOPPONENTTABLE_H
#define POKEMONAUTOMATION_NINTENDOSWITCH_POKEMONSV_TERAOPPONENTTABLE_H

#include "Common/Cpp/Options/SimpleIntegerOption.h"
#include "Common/Cpp/Options/EditableTableOption.h"
#include "PokemonSV_PokemonSelectOption.h"

namespace PokemonAutomation {
namespace NintendoSwitch {
namespace PokemonSV {

class TeraOpponentRow : public EditableTableRow{
public:
    TeraOpponentRow();
    virtual std::unique_ptr<EditableTableRow> clone() const override;

public:
    PokemonSelectCell opponent;
    SimpleIntegerCell<size_t> min_stars;
    SimpleIntegerCell<size_t> max_stars;
};

class TeraOpponentTable : public EditableTableOption_t<TeraOpponentRow>{
public:
    TeraOpponentTable(std::string label);

    // Whether pokemon_slug is among the selected pokemon
    bool find_opponent(const std::string& pokemon_slug, const size_t stars) const;
    // Return the pokemon slugs that the user has selected via the opponent filter table UI.
    std::vector<std::string> selected_pokemon() const;

    // Check if stars match up
    bool validate_opponent() const;

    virtual std::vector<std::string> make_header() const override;

    static std::vector<std::unique_ptr<EditableTableRow>> make_defaults();
};

} // namespace PokemonSV
} // namespace NintendoSwitch
} // namespace PokemonAutomation

#endif // POKEMONAUTOMATION_NINTENDOSWITCH_POKEMONSV_TERAOPPONENTTABLE_H
