/*  Floating-Point Option
 *
 *  From: https://github.com/PokemonAutomation/Arduino-Source
 *
 */

#ifndef PokemonAutomation_FloatingPointWidget_H
#define PokemonAutomation_FloatingPointWidget_H

#include <QLineEdit>
#include "Common/Cpp/Options/FloatingPointOption.h"
#include "ConfigWidget.h"

namespace PokemonAutomation{


class FloatingPointCellWidget : public QLineEdit, public ConfigWidget{
public:
    ~FloatingPointCellWidget();
    FloatingPointCellWidget(QWidget& parent, FloatingPointCell& value);

    virtual void update_value() override;
    virtual void update_visibility(bool program_is_running) override;
    virtual void value_changed() override;

private:
    FloatingPointCell& m_value;
};


class FloatingPointOptionWidget : public QWidget, public ConfigWidget{
public:
    ~FloatingPointOptionWidget();
    FloatingPointOptionWidget(QWidget& parent, FloatingPointOption& value);

    virtual void update_visibility(bool program_is_running) override;
    virtual void value_changed() override;

private:
    FloatingPointCellWidget* m_cell;
};



}
#endif
