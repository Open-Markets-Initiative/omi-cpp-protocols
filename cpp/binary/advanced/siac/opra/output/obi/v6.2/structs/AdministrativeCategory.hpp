#pragma once

#include <cstddef>
#include "../types/AdministrativeMessageType.hpp"

namespace siac::opra::output::obi::v6_2 {

namespace obi_output = ::siac::opra::output::obi::v6_2;

#pragma pack(push, 1)

struct administrative_category {

    obi_output::administrative_message_type administrative_message_type;

    // parse method
    static administrative_category* parse(std::byte* buffer) {
        return reinterpret_cast<administrative_category*>(buffer);
    }

    // parse method const
    static const administrative_category* parse(const std::byte* buffer) {
        return reinterpret_cast<const administrative_category*>(buffer);
    }
};

#pragma pack(pop)
}
