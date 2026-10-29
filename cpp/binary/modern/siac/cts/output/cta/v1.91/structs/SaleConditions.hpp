#pragma once

#include "../types/Category1.hpp"
#include "../types/Category2.hpp"
#include "../types/Category3.hpp"
#include "../types/Category4.hpp"

namespace siac::cts::output::cta::v1_91 {

#pragma pack(push, 1)

struct SaleConditions {

    Category1 category_1;
    Category2 category_2;
    Category3 category_3;
    Category4 category_4;

    // parse method
    static SaleConditions* parse(std::byte* buffer) {
        return reinterpret_cast<SaleConditions*>(buffer);
    }

    // parse method const
    static const SaleConditions* parse(const std::byte* buffer) {
        return reinterpret_cast<const SaleConditions*>(buffer);
    }
};

#pragma pack(pop)
}
