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
#include "PokemonSV/Options/PokemonSV_TeraIVFilterTable.h"
#include "PokemonSV/Options/PokemonSV_TeraMoveTypeTable.h"

namespace PokemonAutomation{
    struct VideoSnapshot;
namespace NintendoSwitch{
namespace PokemonSV{

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

    BooleanCheckBoxOption HAS_CLONE_RIDE_POKEMON;
//    BooleanCheckBoxOption STOP_ON_SHINY;
    SimpleIntegerOption<uint8_t> STOP_ON_RARE_ITEMS;
    TeraIVFilterTable IV_FILTER;
};



class TeraSelfFarmer : public SingleSwitchProgramInstance{
public:
    TeraSelfFarmer();
    virtual void program(SingleSwitchProgramEnvironment& env, BotBaseContext& context) override;

private:
    bool run_raid(SingleSwitchProgramEnvironment& env, BotBaseContext& context, const std::string& pokemon_slug, const std::string& type_slug);
    void process_caught_pokemon(SingleSwitchProgramEnvironment& env, BotBaseContext& context, const std::string& pokemon_slug);
    bool move_pokemon_to_keep(SingleSwitchProgramEnvironment& env, BotBaseContext& context, uint8_t pokemon_row_in_party);

private:
    friend class TeraFarmerCatchOnWin;

    OCR::LanguageOCROption LANGUAGE;

    TeraFarmerOpponentFilter FILTER;
    TeraAIOption BATTLE_AI; 
    TeraAIOption ALT_BATTLE_AI;
    TeraMoveTypeTable ALT_AI_TABLE;

    TeraFarmerCatchOnWin CATCH_ON_WIN;
    TeraFarmerStopConditions STOP_CONDITIONS;

    //  Notifications
    EventNotificationOption NOTIFICATION_STATUS_UPDATE;
    EventNotificationOption NOTIFICATION_NONSHINY;
    EventNotificationOption NOTIFICATION_NONSHINY_KEEP;
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
