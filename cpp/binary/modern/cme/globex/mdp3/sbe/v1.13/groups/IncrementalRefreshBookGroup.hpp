#pragma once

#include "../types/MdEntryPxOptionalEx.hpp"
#include "../types/MdEntrySizeShortOptional.hpp"
#include "../types/SecurityId.hpp"
#include "../types/RptSeq.hpp"
#include "../types/NumberOfOrdersOptional.hpp"
#include "../types/MdPriceLevel.hpp"
#include "../types/MdUpdateAction.hpp"
#include "../types/MdEntryTypeBook.hpp"
#include "../types/TradeableSize.hpp"
#include "../types/Padding1.hpp"

namespace cme::mdp3::v13 {

#pragma pack(push, 1)

struct IncrementalRefreshBookGroup {

    MdEntryPxOptionalEx md_entry_px_optional_ex;
    MdEntrySizeShortOptional md_entry_size_short_optional;
    SecurityId security_id;
    RptSeq rpt_seq;
    NumberOfOrdersOptional number_of_orders_optional;
    MdPriceLevel md_price_level;
    MdUpdateAction md_update_action;
    MdEntryTypeBook md_entry_type_book;
    TradeableSize tradeable_size;
    Padding1 padding_1;

    // parse method
    static IncrementalRefreshBookGroup* parse(std::byte* buffer) {
        return reinterpret_cast<IncrementalRefreshBookGroup*>(buffer);
    }

    // parse method const
    static const IncrementalRefreshBookGroup* parse(const std::byte* buffer) {
        return reinterpret_cast<const IncrementalRefreshBookGroup*>(buffer);
    }
};

#pragma pack(pop)
}
