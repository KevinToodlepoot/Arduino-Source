/*  Money Farmer (Highlands)
 *
 *  From: https://github.com/PokemonAutomation/Arduino-Source
 *
 */

#ifndef PokemonAutomation_PokemonLA_MoneyFarmerHighlands_H
#define PokemonAutomation_PokemonLA_MoneyFarmerHighlands_H

#include "CommonFramework/Notifications/EventNotificationsTable.h"
#include "NintendoSwitch/Framework/NintendoSwitch_SingleSwitchProgram.h"

namespace PokemonAutomation{
namespace NintendoSwitch{
namespace PokemonLA{


class MoneyFarmerHighlands_Descriptor : public RunnableSwitchProgramDescriptor{
public:
    MoneyFarmerHighlands_Descriptor();
};


class MoneyFarmerHighlands : public SingleSwitchProgramInstance{
public:
    MoneyFarmerHighlands(const MoneyFarmerHighlands_Descriptor& descriptor);

    virtual std::unique_ptr<StatsTracker> make_stats() const override;
    virtual void program(SingleSwitchProgramEnvironment& env) override;


private:
    class Stats;

    EventNotificationOption NOTIFICATION_STATUS;
    EventNotificationsOption NOTIFICATIONS;
};





}
}
}
#endif
