#pragma once

#include "../types/Category1.hpp"
#include "../types/Category2.hpp"
#include "../types/Category3.hpp"
#include "../types/Category4.hpp"

namespace siac::cts::output::cta::v2_11_b {

#pragma pack(push, 1)

struct SaleCondition4 {

    Category1 category_1;
    Category2 category_2;
    Category3 category_3;
    Category4 category_4;

    // parse method
    static SaleCondition4* parse(std::byte* buffer) {
        return reinterpret_cast<SaleCondition4*>(buffer);
    }

    // parse method const
    static const SaleCondition4* parse(const std::byte* buffer) {
        return reinterpret_cast<const SaleCondition4*>(buffer);
    }
};

#pragma pack(pop)
}
