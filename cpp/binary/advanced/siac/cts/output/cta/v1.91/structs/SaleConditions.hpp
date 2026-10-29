#pragma once

#include <cstddef>
#include "../types/Category1.hpp"
#include "../types/Category2.hpp"
#include "../types/Category3.hpp"
#include "../types/Category4.hpp"

namespace siac::cts::output::cta::v1_91 {

namespace cta_output = ::siac::cts::output::cta::v1_91;

#pragma pack(push, 1)

struct sale_conditions {

    cta_output::category_1 category_1;
    cta_output::category_2 category_2;
    cta_output::category_3 category_3;
    cta_output::category_4 category_4;

    // parse method
    static sale_conditions* parse(std::byte* buffer) {
        return reinterpret_cast<sale_conditions*>(buffer);
    }

    // parse method const
    static const sale_conditions* parse(const std::byte* buffer) {
        return reinterpret_cast<const sale_conditions*>(buffer);
    }
};

// layout verification
static_assert(offsetof(sale_conditions, category_1) == 0, "unexpected offset of sale_conditions::category_1");
static_assert(offsetof(sale_conditions, category_2) == 1, "unexpected offset of sale_conditions::category_2");
static_assert(offsetof(sale_conditions, category_3) == 2, "unexpected offset of sale_conditions::category_3");
static_assert(offsetof(sale_conditions, category_4) == 3, "unexpected offset of sale_conditions::category_4");
static_assert(sizeof(sale_conditions) == 4, "unexpected sizeof sale_conditions");

#pragma pack(pop)
}
