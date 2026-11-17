// Cme.Globex.Mdp3.Sbe.v1.9: actions/AdminHeartbeat.hpp
#pragma once

#include <cstdint>

namespace cme::mdp3::v9 {

// Admin Heartbeat
struct AdminHeartbeat {

    static constexpr auto name = "Admin Heartbeat";

    // selected when TemplateId == 12
    static constexpr auto field = "TemplateId";
    static constexpr std::uint16_t value = 12;

    // action properties
    static constexpr auto session = "Heartbeat";
    static constexpr auto origin = "Exchange";
};

}
