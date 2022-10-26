/*  Encounter Filter
 *
 *  From: https://github.com/PokemonAutomation/Arduino-Source
 *
 */

#ifndef PokemonAutomation_PokemonSwSh_EncounterFilterWidget_H
#define PokemonAutomation_PokemonSwSh_EncounterFilterWidget_H

#include <QComboBox>
#include "Common/Qt/Options/ConfigWidget.h"
#include "PokemonSwSh_EncounterFilterOption.h"

namespace PokemonAutomation{
namespace NintendoSwitch{
namespace PokemonSwSh{




class EncounterFilterWidget : public QWidget, public ConfigWidget{
public:
    EncounterFilterWidget(QWidget& parent, EncounterFilterOption& value);

    virtual void update_visibility(bool program_is_running) override;

private:
    EncounterFilterOption& m_value;

    QComboBox* m_shininess = nullptr;
    ConfigWidget* m_table = nullptr;
};



}
}
}
#endif
