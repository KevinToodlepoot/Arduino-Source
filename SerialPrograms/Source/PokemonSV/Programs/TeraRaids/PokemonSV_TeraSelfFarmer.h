/*  Tera Farmer
 *
 *  From: https://github.com/PokemonAutomation/Arduino-Source
 *
 */

#ifndef PokemonAutomation_PokemonSV_TeraSelfFarmer_H
#define PokemonAutomation_PokemonSV_TeraSelfFarmer_H

#include "Common/Cpp/Options/BooleanCheckBoxOption.h"
#include "Common/Cpp/Options/SimpleIntegerOption.h"
#include "Common/Cpp/Options/TextEditOption.h"
#include "CommonFramework/Notifications/EventNotificationsTable.h"
#include "CommonFramework/Options/LanguageOCROption.h"
#include "NintendoSwitch/NintendoSwitch_SingleSwitchProgram.h"
#include "PokemonSwSh/Options/PokemonSwSh_BallSelectOption.h"
#include "PokemonSV/Options/PokemonSV_TeraAIOption.h"
#include "Common/Cpp/Options/StringOption.h"
#include "Common/Cpp/Options/EnumDropdownOption.h"
#include "Common/Cpp/Options/EditableTableOption.h"
#include "CommonFramework/Options/StringSelectOption.h"
#include "PokemonSV/Options/PokemonSV_TeraOpponentTable.h"

namespace PokemonAutomation{
    struct VideoSnapshot;
namespace NintendoSwitch{
namespace PokemonSV{

// opponent filter option
//StringSelectDatabase make_tera_name_database(const std::vector<std::string>& slugs);

//const StringSelectDatabase& ALL_POKEMON_TERA_NAMES();



//class OpponentFilterSelectCell : public StringSelectCell{
//public:
//    OpponentFilterSelectCell(const std::string& default_slug);
//};



//class OpponentFilterSelectorRow : public EditableTableRow{
//public:
//    OpponentFilterSelectorRow();
//    virtual std::unique_ptr<EditableTableRow> clone() const override;

//public:
//    OpponentFilterSelectCell opponent;
//    SimpleIntegerCell<size_t> min_stars;
//    SimpleIntegerCell<size_t> max_stars;
//};

//class OpponentFilterTable : public EditableTableOption_t<OpponentFilterSelectorRow>{
//public:
//    OpponentFilterTable(std::string label);

//    // Whether pokemon_slug is among the selected pokemon
//    bool find_opponent(const std::string& pokemon_slug, const size_t stars) const;
//    // Return the pokemon slugs that the user has selected via the opponent filter table UI.
//    std::vector<std::string> selected_pokemon() const;

//    // Check if stars match up
//    bool validate_opponent() const;

//    virtual std::vector<std::string> make_header() const override;

//    static std::vector<std::unique_ptr<EditableTableRow>> make_defaults();
//};



class TeraSelfFarmer;


class TeraSelfFarmer_Descriptor : public SingleSwitchProgramDescriptor{
public:
    TeraSelfFarmer_Descriptor();

    struct Stats;
    virtual std::unique_ptr<StatsTracker> make_stats() const override;

};




class TeraFarmerOpponentFilter : public GroupOption{
public:
    TeraFarmerOpponentFilter();

    bool should_battle(size_t stars, const std::string& pokemon) const;

//    BooleanCheckBoxOption SKIP_HERBA;
//    SimpleIntegerOption<uint8_t> MIN_STARS;
//    SimpleIntegerOption<uint8_t> MAX_STARS;
    TeraOpponentTable TARGET_POKEMON;

private:

};
class TeraFarmerCatchOnWin : public GroupOption{
public:
    TeraFarmerCatchOnWin(TeraSelfFarmer& program);
    virtual void on_set_enabled(bool enabled) override;

private:
    TeraSelfFarmer& m_program;

public:
    PokemonSwSh::PokemonBallSelectOption BALL_SELECT;
    BooleanCheckBoxOption FIX_TIME_ON_CATCH;
};
class TeraFarmerStopConditions : public GroupOption{
public:
    TeraFarmerStopConditions();

    SimpleIntegerOption<uint16_t> MAX_CATCHES;
    BooleanCheckBoxOption STOP_ON_SHINY;
    SimpleIntegerOption<uint8_t> STOP_ON_RARE_ITEMS;
};



class TeraSelfFarmer : public SingleSwitchProgramInstance{
public:
    TeraSelfFarmer();
    virtual void program(SingleSwitchProgramEnvironment& env, BotBaseContext& context) override;

private:
    bool run_raid(SingleSwitchProgramEnvironment& env, BotBaseContext& context);

private:
    friend class TeraFarmerCatchOnWin;

    OCR::LanguageOCROption LANGUAGE;

    TeraFarmerOpponentFilter FILTER;
    TeraAIOption BATTLE_AI;
    TeraFarmerCatchOnWin CATCH_ON_WIN;
    TeraFarmerStopConditions STOP_CONDITIONS;

    //  Notifications
    EventNotificationOption NOTIFICATION_STATUS_UPDATE;
    EventNotificationOption NOTIFICATION_NONSHINY;
    EventNotificationOption NOTIFICATION_SHINY;
    EventNotificationsOption NOTIFICATIONS;

    uint16_t m_number_caught;

    //  Per iteration flags.
//    bool m_battle_finished;
//    bool m_caught;
//    bool m_summary_read;
};




}
}
}
#endif
