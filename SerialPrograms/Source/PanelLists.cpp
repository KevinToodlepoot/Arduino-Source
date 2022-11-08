/*  Left-Side Panel
 *
 *  From: https://github.com/PokemonAutomation/Arduino-Source
 *
 */

#include <array>
#include <QStandardItemModel>
#include <QVBoxLayout>
#include <QLabel>
#include "Common/Qt/NoWheelComboBox.h"
#include "CommonFramework/PersistentSettings.h"
#include "CommonFramework/Windows/DpiScaler.h"
#include "NintendoSwitch/NintendoSwitch_Panels.h"
#include "Pokemon/Pokemon_Strings.h"
#include "PokemonSwSh/PokemonSwSh_Panels.h"
#include "PokemonHome/PokemonHome_Panels.h"
#include "PokemonBDSP/PokemonBDSP_Panels.h"
#include "PokemonLA/PokemonLA_Panels.h"
#include "PokemonSV/PokemonSV_Panels.h"
#include "PanelLists.h"

//#include <iostream>
//using std::cout;
//using std::endl;


namespace PokemonAutomation{





ProgramSelect::ProgramSelect(QWidget& parent, PanelHolder& holder)
    : QGroupBox("Program Select", &parent)
    , m_holder(holder)
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignTop);
    m_dropdown = new NoWheelComboBox(this);
    layout->addWidget(m_dropdown);

    add(PanelListDescriptor(
        "Nintendo Switch",
        &NintendoSwitch::make_panels
    ));
    add(PanelListDescriptor(
        Pokemon::STRING_POKEMON + " Home",
        NintendoSwitch::PokemonHome::make_panels
    ));
    add(PanelListDescriptor(
        Pokemon::STRING_POKEMON + " Sword and Shield",
        NintendoSwitch::PokemonSwSh::make_panels
    ));
    add(PanelListDescriptor(
        Pokemon::STRING_POKEMON + " Brilliant Diamond and Shining Pearl",
        NintendoSwitch::PokemonBDSP::make_panels
    ));
    add(PanelListDescriptor(
        Pokemon::STRING_POKEMON + " Legends Arceus",
        NintendoSwitch::PokemonLA::make_panels
    ));
    add(PanelListDescriptor(
        Pokemon::STRING_POKEMON + " Scarlet and Violet",
        NintendoSwitch::PokemonSV::make_panels, false
    ));

    //  Load the 1st list by default.
    m_dropdown->setCurrentIndex(0);
    m_active_index = 0;
    m_active_list = m_lists[0].make_QWidget(*this, m_holder);
    layout->addWidget(m_active_list);

    connect(
        m_dropdown, &QComboBox::activated,
        this, [this](int index){
            change_list(index);
        }
    );
}

void ProgramSelect::add(PanelListDescriptor list){
    int index = m_dropdown->count();
    m_dropdown->addItem(QString::fromStdString(list.name()));
    m_lists.emplace_back(std::move(list));
    if (!m_tab_map.emplace(m_lists.back().name(), index).second){
        m_lists.pop_back();
        throw InternalProgramError(nullptr, PA_CURRENT_FUNCTION, "Duplicate Category Name: " + m_lists.back().name());
    }
    if (!m_lists.back().enabled()){
        auto* model = qobject_cast<QStandardItemModel*>(m_dropdown->model());
        if (model != nullptr){
            QStandardItem* line_handle = model->item(index);
            if (line_handle != nullptr){
                line_handle->setEnabled(false);
            }
        }
    }
}



void ProgramSelect::load_persistent_panel(){
    const std::string* str = PERSISTENT_SETTINGS().panels.get_string("ProgramCategory");
    if (str == nullptr){
        return;
    }
    auto iter = m_tab_map.find(*str);
    if (iter == m_tab_map.end()){
        return;
    }
    m_dropdown->setCurrentIndex(iter->second);
    change_list(iter->second);
    str = PERSISTENT_SETTINGS().panels.get_string(PanelListWidget::JSON_PROGRAM_PANEL);
    if (str != nullptr){
        m_active_list->set_panel(*str);
    }
}

void ProgramSelect::change_list(int index){
    if (m_active_index == index && m_active_list != nullptr){
        return;
    }
    m_dropdown->setCurrentIndex(index);
    m_active_index = index;
    PERSISTENT_SETTINGS().panels["ProgramCategory"] = m_lists[index].name();
    delete m_active_list;
    m_active_list = m_lists[index].make_QWidget(*this, m_holder);
    layout()->addWidget(m_active_list);
}

QSize ProgramSelect::sizeHint() const{
    QSize size = QGroupBox::sizeHint();
//    cout << size.width() << " x " << size.height() << endl;
//    cout << this->size().width() << " x " << this->size().height() << endl;
    size.setWidth(scale_dpi_width(size.width() + 10));
    return size;
}







}
