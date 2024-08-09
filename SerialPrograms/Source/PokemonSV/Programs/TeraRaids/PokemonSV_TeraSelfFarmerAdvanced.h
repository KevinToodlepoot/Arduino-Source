/*  Tera Farmer
 *
 *  From: https://github.com/PokemonAutomation/Arduino-Source
 *
 */

#ifndef PokemonAutomation_PokemonSV_TeraSelfFarmerAdvanced_H
#define PokemonAutomation_PokemonSV_TeraSelfFarmerAdvanced_H

#include "Common/Cpp/Options/BooleanCheckBoxOption.h"
#include "Common/Cpp/Options/SimpleIntegerOption.h"
#include "Common/Cpp/Options/TextEditOption.h"
#include "Common/Cpp/Options/StringOption.h"
#include "Common/Cpp/Options/EnumDropdownOption.h"
#include "Common/Cpp/Options/EditableTableOption.h"
#include "CommonFramework/Options/StringSelectOption.h"
#include "CommonFramework/Notifications/EventNotificationsTable.h"
#include "CommonFramework/Options/LanguageOCROption.h"
#include "NintendoSwitch/NintendoSwitch_SingleSwitchProgram.h"
#include "PokemonSV/Options/PokemonSV_TeraRollFilter.h"
#include "PokemonSV/Options/PokemonSV_TeraAIOption.h"
#include "PokemonSV/Options/PokemonSV_TeraCatchOnWinOption.h"

namespace PokemonAutomation{
struct VideoSnapshot;
namespace NintendoSwitch{
namespace PokemonSV{

class TeraSelfFarmerAdvanced;


class TeraSelfFarmerAdvanced_Descriptor : public SingleSwitchProgramDescriptor{
public:
    TeraSelfFarmerAdvanced_Descriptor();

    struct Stats;
    virtual std::unique_ptr<StatsTracker> make_stats() const override;

};




class TeraFarmerAdvancedStopConditions : public GroupOption{
public:
    TeraFarmerAdvancedStopConditions();

    SimpleIntegerOption<uint16_t> MAX_CATCHES;
    BooleanCheckBoxOption STOP_ON_SHINY;
    SimpleIntegerOption<uint8_t> STOP_ON_RARE_ITEMS;
};



class TeraSelfFarmerAdvanced : public SingleSwitchProgramInstance, public ConfigOption::Listener{
public:
    ~TeraSelfFarmerAdvanced();
    TeraSelfFarmerAdvanced();
    virtual void program(SingleSwitchProgramEnvironment& env, BotBaseContext& context) override;

private:
    virtual void value_changed(void* object) override;
    bool run_raid(SingleSwitchProgramEnvironment& env, BotBaseContext& context);

private:
    friend class TeraFarmerCatchOnWin;

    OCR::LanguageOCROption LANGUAGE;

    //    TeraFarmerOpponentFilter FILTER;
    TeraRollFilterAdvanced FILTER;
    TeraAIOption BATTLE_AI;
    SimpleIntegerOption<uint8_t> PERIODIC_RESET;
    TeraFarmerCatchOnWin CATCH_ON_WIN;
    TeraFarmerAdvancedStopConditions STOP_CONDITIONS;

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
