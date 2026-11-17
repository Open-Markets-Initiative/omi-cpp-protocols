// Cme.Globex.Mdp3.Sbe.v1.9: actions/SubscriberHeartbeat.hpp
#pragma once

#include <cstdint>

namespace cme::mdp3::v9 {

// Subscriber Heartbeat
struct SubscriberHeartbeat {

    static constexpr auto name = "Subscriber Heartbeat";

    // selected when TemplateId == 210
    static constexpr auto field = "TemplateId";
    static constexpr std::uint16_t value = 210;

    // action properties
    static constexpr auto session = "Heartbeat";
};

}
