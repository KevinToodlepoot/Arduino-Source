#ifndef POKEMONAUTOMATION_NINTENDOSWITCH_POKEMONSV_POKEMONSELECTCELL_H
#define POKEMONAUTOMATION_NINTENDOSWITCH_POKEMONSV_POKEMONSELECTCELL_H

#include "CommonFramework/Options/StringSelectOption.h"

namespace PokemonAutomation {
namespace NintendoSwitch {
namespace PokemonSV {

class PokemonSelectCell : public StringSelectCell{
public:
    PokemonSelectCell(const std::string& default_slug, bool);
};

} // namespace PokemonSV
} // namespace NintendoSwitch
} // namespace PokemonAutomation

#endif // POKEMONAUTOMATION_NINTENDOSWITCH_POKEMONSV_POKEMONSELECTCELL_H
