#include "PokemonSV_TeraIVFilterTable.h"

#include <iostream>

namespace PokemonAutomation {
namespace NintendoSwitch {
namespace PokemonSV {

const EnumDatabase<TeraIVAction>& TeraIVAction_Database(){
    static const EnumDatabase<TeraIVAction> database({
        {TeraIVAction::StopProgram, "stop", "Stop Program"},
        {TeraIVAction::Keep, "keep", "Keep"},
    });
    return database;
}

const EnumDatabase<TeraIVShinyFilter>& TeraIVShinyFilter_Database(){
    static const EnumDatabase<TeraIVShinyFilter> database({
        {TeraIVShinyFilter::Anything, "anything", "Anything"},
        {TeraIVShinyFilter::NotShiny, "not-shiny", "Not Shiny"},
        {TeraIVShinyFilter::Shiny, "shiny", "Shiny"},
    });
    return database;
}

TeraIVFilterRow::TeraIVFilterRow()
    : action(TeraIVAction_Database(), LockWhileRunning::LOCKED, TeraIVAction::Keep)
    , pokemon("anything", true)
    , shiny(TeraIVShinyFilter_Database(), LockWhileRunning::LOCKED, TeraIVShinyFilter::Anything)
    , iv_hp(IVCheckerFilter::Anything)
    , iv_atk(IVCheckerFilter::Anything)
    , iv_def(IVCheckerFilter::Anything)
    , iv_spatk(IVCheckerFilter::Anything)
    , iv_spdef(IVCheckerFilter::Anything)
    , iv_speed(IVCheckerFilter::Anything)
{
    PA_ADD_OPTION(action);
    PA_ADD_OPTION(pokemon);
    PA_ADD_OPTION(shiny);
    PA_ADD_OPTION(iv_hp);
    PA_ADD_OPTION(iv_atk);
    PA_ADD_OPTION(iv_def);
    PA_ADD_OPTION(iv_spatk);
    PA_ADD_OPTION(iv_spdef);
    PA_ADD_OPTION(iv_speed);
}
TeraIVFilterRow::TeraIVFilterRow(TeraIVShinyFilter p_shiny)
    : TeraIVFilterRow()
{
    shiny.set(p_shiny);
}
std::unique_ptr<EditableTableRow> TeraIVFilterRow::clone() const{
    std::unique_ptr<TeraIVFilterRow> ret(new TeraIVFilterRow());
    ret->action.set(action);
    ret->pokemon.set_by_index(pokemon.index());
    ret->shiny.set(shiny);
    ret->iv_hp.set(iv_hp);
    ret->iv_atk.set(iv_atk);
    ret->iv_def.set(iv_def);
    ret->iv_spatk.set(iv_spatk);
    ret->iv_spdef.set(iv_spdef);
    ret->iv_speed.set(iv_speed);
    return ret;
}


TeraIVFilterTable::TeraIVFilterTable()
    : EditableTableOption_t<TeraIVFilterRow>(
        "<b>IV Table:</b><br>"
        "If a caught pokemon matches one of these filters, the specified action will be performed. "
        "Otherwise, it will be released. "
        "If multiple entries apply and have conflicting actions, the program will stop.<br>"
        "IV checking requires that your right panel be set to the IV Judge and that you have selected the correct game language above.",
        LockWhileRunning::LOCKED,
        make_defaults()
    )
{}
std::vector<std::string> TeraIVFilterTable::make_header() const{
    return std::vector<std::string>{
        "Action",
        "Pokemon",
        "Shiny",
        "HP",
        "Attack",
        "Defense",
        "Sp. Attack",
        "Sp. Defense",
        "Speed",
    };
}
std::vector<std::unique_ptr<EditableTableRow>> TeraIVFilterTable::make_defaults(){
    std::vector<std::unique_ptr<EditableTableRow>> ret;
    ret.emplace_back(new TeraIVFilterRow());
    return ret;
}

TeraIVAction TeraIVFilterTable::get_action(const std::string& pokemon_slug, bool shiny, const IVCheckerReader::Results& IVs) const{
    TeraIVAction action = TeraIVAction::Release;
    std::vector<std::unique_ptr<TeraIVFilterRow>> list = copy_snapshot();
    for (size_t c = 0; c < list.size(); c++){
        const TeraIVFilterRow& filter = *list[c];

        //  Check Pokemon filter
        std::cout << "Checking pokemon filter..." << std::endl;
        if (filter.pokemon.slug() != pokemon_slug && filter.pokemon.slug() != "anything") continue;
        std::cout << filter.pokemon.slug() << " and " << pokemon_slug << " are a match." << std::endl;

        // Check the shiny filter
        std::cout << "Checking shiny filter..." << std::endl;
        switch (filter.shiny){
        case TeraIVShinyFilter::Anything:
            break;
        case TeraIVShinyFilter::NotShiny:
            if (shiny)
                continue;
            break;
        case TeraIVShinyFilter::Shiny:
            if (!shiny)
                continue;
            break;
        }
        std::cout << "Shiny filter was a match." << std::endl;

        std::cout << "Checking all the IV filters..." << std::endl;
        //  Check all the IV filters.
        if (!IVChecker_filter_match(filter.iv_hp, IVs.hp)) continue;
        if (!IVChecker_filter_match(filter.iv_atk, IVs.attack)) continue;
        if (!IVChecker_filter_match(filter.iv_def, IVs.defense)) continue;
        if (!IVChecker_filter_match(filter.iv_spatk, IVs.spatk)) continue;
        if (!IVChecker_filter_match(filter.iv_spdef, IVs.spdef)) continue;
        if (!IVChecker_filter_match(filter.iv_speed, IVs.speed)) continue;

        std::cout << "IVs were a match! setting action to " << filter.action.current_display() << std::endl;
        TeraIVAction filter_action = filter.action;

        //  No action matched so far. Take the current action and continue.
        if (action == TeraIVAction::Release){
            action = filter_action;
            continue;
        }

        //  Conflicting actions.
        if (action != filter_action){
            global_logger_tagged().log("Multiple filters matched with conflicting actions. Stopping program...", COLOR_RED);
            return TeraIVAction::StopProgram;
        }
    }
    return action;
}

} // namespace PokemonSV
} // namespace NintendoSwitch
} // namespace PokemonAutomation
