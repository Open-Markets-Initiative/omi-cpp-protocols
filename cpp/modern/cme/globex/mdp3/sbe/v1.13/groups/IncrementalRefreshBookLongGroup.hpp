#pragma once

#include "../types/MdEntryPxOptionalEx.hpp"
#include "../types/MdEntrySizeOptional.hpp"
#include "../types/SecurityId.hpp"
#include "../types/RptSeq.hpp"
#include "../types/NumberOfOrdersOptional.hpp"
#include "../types/MdPriceLevel.hpp"
#include "../types/MdUpdateAction.hpp"
#include "../types/MdEntryTypeBook.hpp"
#include "../types/Padding1.hpp"

namespace cme::mdp3::v13 {

#pragma pack(push, 1)

struct IncrementalRefreshBookLongGroup {

    MdEntryPxOptionalEx md_entry_px_optional_ex;
    MdEntrySizeOptional md_entry_size_optional;
    SecurityId security_id;
    RptSeq rpt_seq;
    NumberOfOrdersOptional number_of_orders_optional;
    MdPriceLevel md_price_level;
    MdUpdateAction md_update_action;
    MdEntryTypeBook md_entry_type_book;
    Padding1 padding_1;

    // parse method
    static IncrementalRefreshBookLongGroup* parse(std::byte* buffer) {
        return reinterpret_cast<IncrementalRefreshBookLongGroup*>(buffer);
    }

    // parse method const
    static const IncrementalRefreshBookLongGroup* parse(const std::byte* buffer) {
        return reinterpret_cast<const IncrementalRefreshBookLongGroup*>(buffer);
    }
};

#pragma pack(pop)
}
