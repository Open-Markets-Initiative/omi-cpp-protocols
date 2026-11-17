// Cme.Globex.Mdp3.Sbe.v1.8: messages/AdminHeartbeat.hpp
#pragma once

#include <cstdint>

namespace cme::mdp3::v8 {

// Admin Heartbeat
struct admin_heartbeat {

    static constexpr auto name = "Admin Heartbeat";

    // selected when template_id == 12
    static constexpr auto field = "template_id";
    static constexpr std::uint16_t value = 12;
};

}
