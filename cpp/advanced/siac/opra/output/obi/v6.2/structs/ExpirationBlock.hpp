#pragma once

#include <cstddef>
#include "../types/ExpirationMonth.hpp"
#include "../types/ExpirationDay.hpp"
#include "../types/ExpirationYear.hpp"

namespace siac::opra::output::obi::v6_2 {

namespace obi_output = ::siac::opra::output::obi::v6_2;

#pragma pack(push, 1)

struct expiration_block {

    obi_output::expiration_month expiration_month;
    obi_output::expiration_day expiration_day;
    obi_output::expiration_year expiration_year;

    // parse method
    static expiration_block* parse(std::byte* buffer) {
        return reinterpret_cast<expiration_block*>(buffer);
    }

    // parse method const
    static const expiration_block* parse(const std::byte* buffer) {
        return reinterpret_cast<const expiration_block*>(buffer);
    }
};

// layout verification
static_assert(offsetof(expiration_block, expiration_month) == 0, "unexpected offset of expiration_block::expiration_month");
static_assert(offsetof(expiration_block, expiration_day) == 1, "unexpected offset of expiration_block::expiration_day");
static_assert(offsetof(expiration_block, expiration_year) == 2, "unexpected offset of expiration_block::expiration_year");
static_assert(sizeof(expiration_block) == 3, "unexpected sizeof expiration_block");

#pragma pack(pop)
}
