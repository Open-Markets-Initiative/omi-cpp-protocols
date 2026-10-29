#pragma once

#include "../types/IssueSymbol.hpp"
#include "../types/SecurityClass.hpp"
#include "../types/ReferenceForNetChange.hpp"
#include "../types/ReferencePrice.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

#pragma pack(push, 1)

// Denotes the reference price to be used for intraday net change calculations for an issue.
struct IpoInformationMessage {

    IssueSymbol issue_symbol;
    SecurityClass security_class;
    ReferenceForNetChange reference_for_net_change;
    ReferencePrice reference_price;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'I';

    // parse method
    static IpoInformationMessage* parse(std::byte* buffer) {
        return reinterpret_cast<IpoInformationMessage*>(buffer);
    }

    // parse method const
    static const IpoInformationMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const IpoInformationMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const IpoInformationMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const IpoInformationMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
