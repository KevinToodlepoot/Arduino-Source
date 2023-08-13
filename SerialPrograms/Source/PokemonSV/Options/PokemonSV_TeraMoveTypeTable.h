#ifndef POKEMONAUTOMATION_NINTENDOSWITCH_POKEMONSV_TERAMOVETYPETABLE_H
#define POKEMONAUTOMATION_NINTENDOSWITCH_POKEMONSV_TERAMOVETYPETABLE_H

#include "Common/Cpp/Options/EnumDropdownOption.h"
#include "Common/Cpp/Options/BooleanCheckBoxOption.h"
#include "Common/Cpp/Options/EditableTableOption.h"
#include "Pokemon/Pokemon_Types.h"

namespace PokemonAutomation {
namespace NintendoSwitch {
namespace PokemonSV {

using namespace Pokemon;

const EnumDatabase<PokemonType>& tera_type_enum_database();

class TeraMoveTypeTableRow : public EditableTableRow{
public:
    TeraMoveTypeTableRow();
    virtual std::unique_ptr<EditableTableRow> clone() const override;

    EnumDropdownCell<PokemonType> type;
};

class TeraMoveTypeTable : public EditableTableOption_t<TeraMoveTypeTableRow>{
public:
    TeraMoveTypeTable();
    virtual std::vector<std::string> make_header() const override;
    static std::vector<std::unique_ptr<EditableTableRow>> make_defaults();

    bool check_type(const std::string& type_slug) const;
};

} // namespace PokemonSV
} // namespace NintendoSwitch
} // namespace PokemonAutomation

#endif // POKEMONAUTOMATION_NINTENDOSWITCH_POKEMONSV_TERAMOVETYPETABLE_H
