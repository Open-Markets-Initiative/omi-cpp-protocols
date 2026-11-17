// Cme.Globex.Mdp3.Sbe.v1.5: actions/AdminHeartbeat.hpp
#pragma once

#include <cstdint>

namespace cme::mdp3::v5 {

// Admin Heartbeat
struct AdminHeartbeat {

    static constexpr auto name = "Admin Heartbeat";

    // selected when TemplateId == 12
    static constexpr auto field = "TemplateId";
    static constexpr std::uint16_t value = 12;
};

}
