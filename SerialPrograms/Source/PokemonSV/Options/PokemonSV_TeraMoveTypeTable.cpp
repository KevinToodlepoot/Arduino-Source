#include "PokemonSV_TeraMoveTypeTable.h"

namespace PokemonAutomation {
namespace NintendoSwitch {
namespace PokemonSV {

const EnumDatabase<PokemonType>& tera_type_enum_database(){
    static EnumDatabase<PokemonType> database{
        {PokemonType::NONE,     "none", "None"},
        {PokemonType::NORMAL,   "normal", "Normal"},
        {PokemonType::FIRE,     "fire", "Fire"},
        {PokemonType::FIGHTING, "fighting", "Fighting"},
        {PokemonType::WATER,    "water", "Water"},
        {PokemonType::FLYING,   "flying", "Flying"},
        {PokemonType::GRASS,    "grass", "Grass"},
        {PokemonType::POISON,   "poison", "Poison"},
        {PokemonType::ELECTRIC, "electric", "Electric"},
        {PokemonType::GROUND,   "ground", "Ground"},
        {PokemonType::PSYCHIC,  "psychic", "Psychic"},
        {PokemonType::ROCK,     "rock", "Rock"},
        {PokemonType::ICE,      "ice", "Ice"},
        {PokemonType::BUG,      "bug", "Bug"},
        {PokemonType::DRAGON,   "dragon", "Dragon"},
        {PokemonType::GHOST,    "ghost", "Ghost"},
        {PokemonType::DARK,     "dark", "Dark"},
        {PokemonType::STEEL,    "steel", "Steel"},
        {PokemonType::FAIRY,    "fairy", "Fairy"},
    };
    return database;
};



TeraMoveTypeTableRow::TeraMoveTypeTableRow()
    : type(tera_type_enum_database(), LockWhileRunning::LOCKED, PokemonType::NONE)
{
    PA_ADD_OPTION(type);
}
std::unique_ptr<EditableTableRow> TeraMoveTypeTableRow::clone() const{
    std::unique_ptr<TeraMoveTypeTableRow> ret(new TeraMoveTypeTableRow());
    ret->type.set(type);
    return ret;
}


TeraMoveTypeTable::TeraMoveTypeTable()
    : EditableTableOption_t<TeraMoveTypeTableRow>(
        "<b>Alt Move Type Table:</b><br>"
        "If the opponent pokemon's tera type matches one of the types in this table,"
        "then the alternate move table will be used.",
        LockWhileRunning::LOCKED,
        make_defaults()
    )
{}
std::vector<std::string> TeraMoveTypeTable::make_header() const{
    return std::vector<std::string>{
        "Type",
    };
}
std::vector<std::unique_ptr<EditableTableRow>> TeraMoveTypeTable::make_defaults(){
    std::vector<std::unique_ptr<EditableTableRow>> ret;
    ret.emplace_back(new TeraMoveTypeTableRow);
    return ret;
}

bool TeraMoveTypeTable::check_type(const std::string& type_slug) const{
    std::vector<std::unique_ptr<TeraMoveTypeTableRow>> table = copy_snapshot();
    for (const std::unique_ptr<TeraMoveTypeTableRow>& row : table){
        if (row->type.current_display() == type_slug)
            return true;
    }
    return false;
}

} // namespace PokemonSV
} // namespace NintendoSwitch
} // namespace PokemonAutomation
