// Cme.Globex.Mdp3.Sbe.v1.9: groups/IncrementalRefreshBookLegacyGroup.hpp
#pragma once

#include "../types/MdEntryPxOptional.hpp"
#include "../types/MdEntrySizeShortOptional.hpp"
#include "../types/SecurityId.hpp"
#include "../types/RptSeq.hpp"
#include "../types/NumberOfOrdersOptional.hpp"
#include "../types/MdPriceLevel.hpp"
#include "../types/MdUpdateAction.hpp"
#include "../types/MdEntryTypeBook.hpp"
#include "../types/Padding5.hpp"

namespace cme::mdp3::v9 {

#pragma pack(push, 1)

struct IncrementalRefreshBookLegacyGroup {

    MdEntryPxOptional md_entry_px_optional;
    MdEntrySizeShortOptional md_entry_size_short_optional;
    SecurityId security_id;
    RptSeq rpt_seq;
    NumberOfOrdersOptional number_of_orders_optional;
    MdPriceLevel md_price_level;
    MdUpdateAction md_update_action;
    MdEntryTypeBook md_entry_type_book;
    Padding5 padding_5;

    // parse method
    static IncrementalRefreshBookLegacyGroup* parse(std::byte* buffer) {
        return reinterpret_cast<IncrementalRefreshBookLegacyGroup*>(buffer);
    }

    // parse method const
    static const IncrementalRefreshBookLegacyGroup* parse(const std::byte* buffer) {
        return reinterpret_cast<const IncrementalRefreshBookLegacyGroup*>(buffer);
    }
};

#pragma pack(pop)
}
