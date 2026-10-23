#pragma once

#include "../types/ExpirationMonth.hpp"
#include "../types/ExpirationDay.hpp"
#include "../types/ExpirationYear.hpp"

namespace siac::opra::output::obi::v6_2 {

#pragma pack(push, 1)

struct ExpirationBlock {

    ExpirationMonth expiration_month;
    ExpirationDay expiration_day;
    ExpirationYear expiration_year;

    // parse method
    static ExpirationBlock* parse(std::byte* buffer) {
        return reinterpret_cast<ExpirationBlock*>(buffer);
    }

    // parse method const
    static const ExpirationBlock* parse(const std::byte* buffer) {
        return reinterpret_cast<const ExpirationBlock*>(buffer);
    }
};

#pragma pack(pop)
}
