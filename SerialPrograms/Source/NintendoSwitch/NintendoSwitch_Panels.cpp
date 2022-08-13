/*  Nintendo Switch Panels
 *
 *  From: https://github.com/PokemonAutomation/Arduino-Source
 *
 */

#include "CommonFramework/GlobalSettingsPanel.h"
#include "NintendoSwitch_Panels.h"

#include "NintendoSwitch_Settings.h"

#include "Programs/NintendoSwitch_VirtualConsole.h"
#include "Programs/NintendoSwitch_SwitchViewer.h"

#include "Programs/NintendoSwitch_TurboA.h"
#include "Programs/NintendoSwitch_TurboButton.h"
#include "Programs/NintendoSwitch_PreventSleep.h"
#include "Programs/NintendoSwitch_FriendCodeAdder.h"
#include "Programs/NintendoSwitch_FriendDelete.h"

#include "Programs/PokemonHome_PageSwap.h"

#include "TestProgramComputer.h"
#include "TestProgramSwitch.h"
#include "NintendoSwitch/InferenceTraining/PokemonHome_GenerateNameOCR.h"
#include "Pokemon/Inference/Pokemon_TrainIVCheckerOCR.h"
#include "Pokemon/Inference/Pokemon_TrainPokemonOCR.h"
#include "NintendoSwitch/TestPathMaker.h"

namespace PokemonAutomation{
namespace NintendoSwitch{


std::vector<PanelEntry> make_panels(){
    std::vector<PanelEntry> ret;

    ret.emplace_back("---- Settings ----");
    ret.emplace_back(make_settings<ConsoleSettings_Descriptor, ConsoleSettingsPanel>());

    ret.emplace_back("---- Virtual Consoles ----");
    ret.emplace_back(make_panel<VirtualConsole_Descriptor, VirtualConsole>());
    ret.emplace_back(make_panel<SwitchViewer_Descriptor, SwitchViewer>());

    ret.emplace_back("---- Programs ----");
    ret.emplace_back(make_single_switch_program<TurboA_Descriptor, TurboA>());
    ret.emplace_back(make_single_switch_program<TurboButton_Descriptor, TurboButton>());
    ret.emplace_back(make_single_switch_program<PreventSleep_Descriptor, PreventSleep>());
    ret.emplace_back(make_single_switch_program<FriendCodeAdder_Descriptor, FriendCodeAdder>());
    ret.emplace_back(make_single_switch_program<FriendDelete_Descriptor, FriendDelete>());

//    ret.emplace_back("---- " + STRING_POKEMON + " Home ----");
    ret.emplace_back(make_single_switch_program<PokemonHome::PageSwap_Descriptor, PokemonHome::PageSwap>());

    if (PreloadSettings::instance().DEVELOPER_MODE){
        ret.emplace_back("---- Developer Tools ----");
        ret.emplace_back(make_computer_program<TestProgramComputer_Descriptor, TestProgramComputer>());
        ret.emplace_back(make_multi_switch_program<TestProgram_Descriptor, TestProgram>());
        ret.emplace_back(make_single_switch_program<PokemonHome::GenerateNameOCRData_Descriptor, PokemonHome::GenerateNameOCRData>());
        ret.emplace_back(make_computer_program<Pokemon::TrainIVCheckerOCR_Descriptor, Pokemon::TrainIVCheckerOCR>());
        ret.emplace_back(make_computer_program<Pokemon::TrainPokemonOCR_Descriptor, Pokemon::TrainPokemonOCR>());
        ret.emplace_back(make_single_switch_program<TestPathMaker_Descriptor, TestPathMaker>());
    }

    return ret;
}



}
}
