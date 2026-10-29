#pragma once

#include "../types/IndicesMessageType.hpp"

namespace siac::cts::output::cta::v1_91 {

#pragma pack(push, 1)

struct IndicesMessage {

    IndicesMessageType indices_message_type;

    // parse method
    static IndicesMessage* parse(std::byte* buffer) {
        return reinterpret_cast<IndicesMessage*>(buffer);
    }

    // parse method const
    static const IndicesMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const IndicesMessage*>(buffer);
    }
};

#pragma pack(pop)
}
