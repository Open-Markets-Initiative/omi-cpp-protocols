#pragma once

#include "../types/Symbol.hpp"
#include "../types/SecurityId.hpp"
#include "../types/OrderQty.hpp"
#include "../types/QuoteType.hpp"
#include "../types/SideOptional.hpp"
#include "../types/Padding2.hpp"

namespace cme::mdp3::v13 {

#pragma pack(push, 1)

struct RelatedSymGroup {

    Symbol symbol;
    SecurityId security_id;
    OrderQty order_qty;
    QuoteType quote_type;
    SideOptional side_optional;
    Padding2 padding_2;

    // parse method
    static RelatedSymGroup* parse(std::byte* buffer) {
        return reinterpret_cast<RelatedSymGroup*>(buffer);
    }

    // parse method const
    static const RelatedSymGroup* parse(const std::byte* buffer) {
        return reinterpret_cast<const RelatedSymGroup*>(buffer);
    }
};

#pragma pack(pop)
}
