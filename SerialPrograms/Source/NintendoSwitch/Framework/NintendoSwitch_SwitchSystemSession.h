/*  Switch System Session
 *
 *  From: https://github.com/PokemonAutomation/Arduino-Source
 *
 */

#ifndef PokemonAutomation_NintendoSwitch_SwitchSystemSession_H
#define PokemonAutomation_NintendoSwitch_SwitchSystemSession_H

#include "CommonFramework/Logging/LoggerQt.h"
#include "CommonFramework/ControllerDevices/SerialPortSession.h"
#include "CommonFramework/VideoPipeline/CameraSession.h"
#include "CommonFramework/AudioPipeline/AudioSession.h"
#include "NintendoSwitch_SwitchSystem.h"

namespace PokemonAutomation{
namespace NintendoSwitch{

class SwitchSystemFactory;




class SwitchSystemSession final : public ConsoleSystem{
public:
    ~SwitchSystemSession();
    SwitchSystemSession(
        SwitchSystemFactory& factory,
        Logger& raw_logger,
        uint64_t program_id
    );

    Logger& logger(){ return m_logger; }

    SerialPortSession& serial_session(){ return m_serial; }
    CameraSession& camera_session(){ return *m_camera; }
    AudioSession& audio_session(){ return m_audio; }

private:
    virtual BotBaseHandle& sender() override;
    virtual VideoFeed& video() override;
    virtual AudioFeed& audio() override;

private:
    uint64_t m_instance_id = 0;
    TaggedLogger m_logger;
    SwitchSystemFactory& m_factory;

    SerialPortSession m_serial;
    std::unique_ptr<CameraSession> m_camera;
    AudioSession m_audio;
};



}
}
#endif
