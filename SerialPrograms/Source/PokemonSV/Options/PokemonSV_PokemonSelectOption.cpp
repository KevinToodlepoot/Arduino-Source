#include "PokemonSV/Resources/PokemonSV_TeraNameDatabase.h"
#include "PokemonSV_PokemonSelectOption.h"

namespace PokemonAutomation {
namespace NintendoSwitch {
namespace PokemonSV {

PokemonSelectCell::PokemonSelectCell(
        const std::string& default_slug
)
    : StringSelectCell(
          ALL_POKEMON_TERA_NAMES(),
          LockWhileRunning::LOCKED,
          default_slug
    )
{}

} // namespace PokemonSV
} // namespace NintendoSwitch
} // namespace PokemonAutomation
