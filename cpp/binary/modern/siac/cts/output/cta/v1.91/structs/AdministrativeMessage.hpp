#pragma once

#include "../types/AdministrativeMessageType.hpp"

namespace siac::cts::output::cta::v1_91 {

#pragma pack(push, 1)

struct AdministrativeMessage {

    AdministrativeMessageType administrative_message_type;

    // parse method
    static AdministrativeMessage* parse(std::byte* buffer) {
        return reinterpret_cast<AdministrativeMessage*>(buffer);
    }

    // parse method const
    static const AdministrativeMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const AdministrativeMessage*>(buffer);
    }
};

#pragma pack(pop)
}
