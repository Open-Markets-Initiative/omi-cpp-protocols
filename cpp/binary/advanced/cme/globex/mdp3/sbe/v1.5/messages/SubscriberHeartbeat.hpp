// Cme.Globex.Mdp3.Sbe.v1.5: messages/SubscriberHeartbeat.hpp
#pragma once

#include <cstdint>

namespace cme::mdp3::v5 {

// Subscriber Heartbeat
struct subscriber_heartbeat {

    static constexpr auto name = "Subscriber Heartbeat";

    // selected when template_id == 210
    static constexpr auto field = "template_id";
    static constexpr std::uint16_t value = 210;
};

}
