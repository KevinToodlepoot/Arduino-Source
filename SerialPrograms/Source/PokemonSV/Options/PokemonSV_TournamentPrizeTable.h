/* Tournament prize table
 *
 *  From: https://github.com/PokemonAutomation/Arduino-Source
 *
 */

#ifndef PokemonAutomation_PokemonSV_TournamentPrizeSelector_H
#define PokemonAutomation_PokemonSV_TournamentPrizeSelector_H

#include "Common/Cpp/Options/EditableTableOption.h"
#include "PokemonSV_TournamentPrizeSelectOption.h"

namespace PokemonAutomation{
namespace NintendoSwitch{
namespace PokemonSV{



class TournamentPrizeSelectorRow : public EditableTableRow{
public:
    TournamentPrizeSelectorRow();
    virtual std::unique_ptr<EditableTableRow> clone() const override;

public:
    TournamentPrizeSelectCell item;
};



class TournamentPrizeTable : public EditableTableOption_t<TournamentPrizeSelectorRow>{
public:
    TournamentPrizeTable(std::string label);


    // Whether item_slug is among the selected items.
    bool find_item(const std::string& item_slug) const;
    std::vector<std::string> selected_items() const;

    virtual std::vector<std::string> make_header() const override;

    static std::vector<std::unique_ptr<EditableTableRow>> make_defaults();
};





}
}
}
#endif
