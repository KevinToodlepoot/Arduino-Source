#include "PokemonSV_TeraOpponentTable.h"

#include <iostream>

namespace PokemonAutomation {
namespace NintendoSwitch {
namespace PokemonSV {

TeraOpponentRow::TeraOpponentRow()
    : opponent("abomasnow-female")
    , min_stars(LockWhileRunning::LOCKED, 1)
    , max_stars(LockWhileRunning::LOCKED, 7)
{
    PA_ADD_OPTION(opponent);
    PA_ADD_OPTION(min_stars);
    PA_ADD_OPTION(max_stars);
}
std::unique_ptr<EditableTableRow> TeraOpponentRow::clone() const{
    std::unique_ptr<TeraOpponentRow> ret(new TeraOpponentRow());
    ret->opponent.set_by_index(opponent.index());
    ret->min_stars.set(min_stars);
    ret->max_stars.set(max_stars);
    return ret;
}



TeraOpponentTable::TeraOpponentTable(std::string label)
    : EditableTableOption_t<TeraOpponentRow>(
          std::move(label),
          LockWhileRunning::LOCKED,
          make_defaults()
    )
{}

bool TeraOpponentTable::find_opponent(const std::string& pokemon_slug, const size_t stars) const{
    std::vector<std::unique_ptr<TeraOpponentRow>> table = copy_snapshot();
    for (const std::unique_ptr<TeraOpponentRow>& row : table){
        if (row->opponent.slug() == pokemon_slug){
            std::cout << "Pokemon's a match!" << std::endl;
            if (! (stars < row->min_stars || stars > row->max_stars)){
                std::cout << "Stars are a match!" << std::endl;
                return true;
            }else{
                std::cout << "But stars did not match..." << std::endl;
            }
        }
    }
    return false;
}

bool TeraOpponentTable::validate_opponent() const{
    std::vector<std::unique_ptr<TeraOpponentRow>> table = copy_snapshot();
    for (const std::unique_ptr<TeraOpponentRow>& row : table){
        if (row->min_stars > row->max_stars)
            return false;
    }
    return true;
}

std::vector<std::string> TeraOpponentTable::selected_pokemon() const{
    std::vector<std::unique_ptr<TeraOpponentRow>> table = copy_snapshot();
    std::vector<std::string> slugs;
    for (const std::unique_ptr<TeraOpponentRow>& row : table){
        slugs.emplace_back(row->opponent.slug());
    }
    return slugs;
}

std::vector<std::string> TeraOpponentTable::make_header() const{
    return std::vector<std::string>{
        "Pokemon",
        "Min Stars",
        "Max Stars",
    };
}

std::vector<std::unique_ptr<EditableTableRow>> TeraOpponentTable::make_defaults(){
    std::vector<std::unique_ptr<EditableTableRow>> ret;
    ret.emplace_back(std::make_unique<TeraOpponentRow>());
    return ret;
}

} // namespace PokemonSV
} // namespace NintendoSwitch
} // namespace PokemonAutomation
