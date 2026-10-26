#pragma once

#include "../types/AdministrativeMessageType.hpp"

namespace siac::opra::output::obi::v6_2 {

#pragma pack(push, 1)

struct AdministrativeCategory {

    AdministrativeMessageType administrative_message_type;

    // parse method
    static AdministrativeCategory* parse(std::byte* buffer) {
        return reinterpret_cast<AdministrativeCategory*>(buffer);
    }

    // parse method const
    static const AdministrativeCategory* parse(const std::byte* buffer) {
        return reinterpret_cast<const AdministrativeCategory*>(buffer);
    }
};

#pragma pack(pop)
}
