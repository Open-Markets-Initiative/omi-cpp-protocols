#pragma once

#include <cstddef>
#include "../types/MessageLength.hpp"
#include "../types/MessageCategory.hpp"

namespace siac::cqs::output::cta::v2_10_a {

namespace cta_output = ::siac::cqs::output::cta::v2_10_a;

#pragma pack(push, 1)

struct message {

    cta_output::message_length message_length;
    cta_output::message_category message_category;

    // parse method
    static message* parse(std::byte* buffer) {
        return reinterpret_cast<message*>(buffer);
    }

    // parse method const
    static const message* parse(const std::byte* buffer) {
        return reinterpret_cast<const message*>(buffer);
    }
};

#pragma pack(pop)
}
