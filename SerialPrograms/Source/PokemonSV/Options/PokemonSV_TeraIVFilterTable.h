#ifndef POKEMONAUTOMATION_NINTENDOSWITCH_POKEMONSV_TERAIVFILTERTABLE_H
#define POKEMONAUTOMATION_NINTENDOSWITCH_POKEMONSV_TERAIVFILTERTABLE_H

#include "Common/Cpp/Options/EnumDropdownOption.h"
#include "Common/Cpp/Options/EditableTableOption.h"
#include "Common/Cpp/Options/BooleanCheckBoxOption.h"
#include "Pokemon/Options/Pokemon_IVCheckerOption.h"
#include "Pokemon/Inference/Pokemon_IVCheckerReader.h"
#include "PokemonSV_PokemonSelectOption.h"

namespace PokemonAutomation {
namespace NintendoSwitch {
namespace PokemonSV {

using namespace Pokemon;

enum class TeraIVAction{
    StopProgram,
    Keep,
    Release,
};

enum class TeraIVShinyFilter{
    Anything,
    NotShiny,
    Shiny
};

class TeraIVFilterRow : public EditableTableRow{
public:
    TeraIVFilterRow();
    TeraIVFilterRow(TeraIVShinyFilter p_shiny);
    virtual std::unique_ptr<EditableTableRow> clone() const override;

    EnumDropdownCell<TeraIVAction> action;
    PokemonSelectCell pokemon;
    EnumDropdownCell<TeraIVShinyFilter> shiny;
    IVCheckerFilterCell iv_hp;
    IVCheckerFilterCell iv_atk;
    IVCheckerFilterCell iv_def;
    IVCheckerFilterCell iv_spatk;
    IVCheckerFilterCell iv_spdef;
    IVCheckerFilterCell iv_speed;
};

class TeraIVFilterTable : public EditableTableOption_t<TeraIVFilterRow>{
public:
    TeraIVFilterTable();
    virtual std::vector<std::string> make_header() const override;
    static std::vector<std::unique_ptr<EditableTableRow>> make_defaults();

    TeraIVAction get_action(const std::string& pokemon_slug, bool shiny, const IVCheckerReader::Results& IVs) const;
};

} // namespace PokemonSV
} // namespace NintendoSwitch
} // namespace PokemonAutomation

#endif // POKEMONAUTOMATION_NINTENDOSWITCH_POKEMONSV_TERAIVFILTERTABLE_H
