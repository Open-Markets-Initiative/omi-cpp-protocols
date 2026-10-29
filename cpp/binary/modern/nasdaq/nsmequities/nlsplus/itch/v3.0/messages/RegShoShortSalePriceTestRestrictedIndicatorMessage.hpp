#pragma once

#include "../types/IssueSymbol.hpp"
#include "../types/RegShoAction.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

#pragma pack(push, 1)

// Indicates the Reg Sho short sale price test restriction status for an issue, under Rule 201 of Regulation Sho.
struct RegShoShortSalePriceTestRestrictedIndicatorMessage {

    IssueSymbol issue_symbol;
    RegShoAction reg_sho_action;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'Y';

    // parse method
    static RegShoShortSalePriceTestRestrictedIndicatorMessage* parse(std::byte* buffer) {
        return reinterpret_cast<RegShoShortSalePriceTestRestrictedIndicatorMessage*>(buffer);
    }

    // parse method const
    static const RegShoShortSalePriceTestRestrictedIndicatorMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const RegShoShortSalePriceTestRestrictedIndicatorMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const RegShoShortSalePriceTestRestrictedIndicatorMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const RegShoShortSalePriceTestRestrictedIndicatorMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
