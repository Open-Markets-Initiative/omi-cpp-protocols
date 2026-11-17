// Cme.Globex.Mdp3.Sbe.v1.9: messages/SubscriberHeartbeat.hpp
#pragma once

#include <cstdint>

namespace cme::mdp3::v9 {

// Subscriber Heartbeat
struct subscriber_heartbeat {

    static constexpr auto name = "Subscriber Heartbeat";

    // selected when template_id == 210
    static constexpr auto field = "template_id";
    static constexpr std::uint16_t value = 210;

    // action properties
    static constexpr auto session = "Heartbeat";
};

}
