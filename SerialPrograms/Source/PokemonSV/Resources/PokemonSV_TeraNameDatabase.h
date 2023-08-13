#include "CommonFramework/Options/StringSelectOption.h"

namespace PokemonAutomation {
namespace NintendoSwitch {
namespace PokemonSV {

StringSelectDatabase make_tera_name_database(const std::vector<std::string>& slugs);

const StringSelectDatabase& ALL_POKEMON_TERA_NAMES();

const StringSelectDatabase& ALL_POKEMON_TERA_NAMES_WITH_ANYTHING();

} // namespace PokemonSV
} // namespace NintendoSwitch
} // namespace PokemonAutomation
