#pragma once

#include "../types/Side.hpp"
#include "../types/Offset1Padding1.hpp"
#include "../types/Account.hpp"
#include "../types/EnteringFirmOptional.hpp"
#include "../types/Clordid.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

#pragma pack(push, 1)

struct CrossSidesGroup {

    Side side;
    Offset1Padding1 offset_1_padding_1;
    Account account;
    EnteringFirmOptional entering_firm_optional;
    Clordid clordid;

    // parse method
    static CrossSidesGroup* parse(std::byte* buffer) {
        return reinterpret_cast<CrossSidesGroup*>(buffer);
    }

    // parse method const
    static const CrossSidesGroup* parse(const std::byte* buffer) {
        return reinterpret_cast<const CrossSidesGroup*>(buffer);
    }
};

#pragma pack(pop)
}
