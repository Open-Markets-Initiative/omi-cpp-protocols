#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/ParticipantId.hpp"
#include "../structs/ParticipantTimestamp.hpp"
#include "../common/Decimal.hpp"
#include "../enums/PrimaryListingMarketParticipantId.hpp"
#include "../enums/NationalBboIndicator.hpp"
#include "../structs/NationalBestBidLongAppendage.hpp"
#include "../structs/NationalBestOfferLongAppendage.hpp"
#include "../structs/NationalBestBidShortAppendage.hpp"
#include "../structs/NationalBestOfferShortAppendage.hpp"

namespace siac::cqs::output::cta::v1_91 {

// The Auction Status message is used when a Participant in a Cta eligible security
class ShortQuoteMessage {
  public:
    static constexpr const char* name = "ShortQuoteMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit ShortQuoteMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every ShortQuoteMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 37;
    std::size_t encoded_size() const { return national_best_offer_short_appendage_end(); }

    ParticipantId participant_id() const { return static_cast<ParticipantId>(wire::read_char(at(0))); }

    ParticipantTimestamp participant_timestamp() const { return ParticipantTimestamp{ bytes_.subspan(1) }; }

    std::uint8_t message_id() const { return wire::read_u8(at(9)); }

    std::uint32_t transaction_id() const { return wire::read_u32_be(at(10)); }

    std::int64_t participant_reference_number() const { return wire::read_i64_be(at(14)); }

    std::string_view security_symbol_short() const { return view::text(at(22), 5, ' '); }

    Decimal bid_price_short() const { return Decimal(static_cast<std::int64_t>(wire::read_u16_be(at(27))), -2); }

    std::uint16_t bid_size_short() const { return wire::read_u16_be(at(29)); }

    Decimal offer_price_short() const { return Decimal(static_cast<std::int64_t>(wire::read_u16_be(at(31))), -2); }

    std::uint16_t offer_size_short() const { return wire::read_u16_be(at(33)); }

    PrimaryListingMarketParticipantId primary_listing_market_participant_id() const { return static_cast<PrimaryListingMarketParticipantId>(wire::read_char(at(35))); }

    NationalBboIndicator national_bbo_indicator() const { return static_cast<NationalBboIndicator>(wire::read_char(at(36))); }

    std::optional<NationalBestBidLongAppendage> national_best_bid_long_appendage() const {
        if (!(static_cast<char>(national_bbo_indicator()) == 'U')) { return std::nullopt; }
        wire::require("ShortQuoteMessage", 37 + NationalBestBidLongAppendage::minimum_size, bytes_.size());
        return NationalBestBidLongAppendage{ bytes_.subspan(37) };
    }

    std::optional<NationalBestOfferLongAppendage> national_best_offer_long_appendage() const {
        if (!(static_cast<char>(national_bbo_indicator()) == 'U')) { return std::nullopt; }
        wire::require("ShortQuoteMessage", national_best_bid_long_appendage_end() + NationalBestOfferLongAppendage::minimum_size, bytes_.size());
        return NationalBestOfferLongAppendage{ bytes_.subspan(national_best_bid_long_appendage_end()) };
    }

    std::optional<NationalBestBidShortAppendage> national_best_bid_short_appendage() const {
        if (!(static_cast<char>(national_bbo_indicator()) == 'T')) { return std::nullopt; }
        wire::require("ShortQuoteMessage", national_best_offer_long_appendage_end() + NationalBestBidShortAppendage::minimum_size, bytes_.size());
        return NationalBestBidShortAppendage{ bytes_.subspan(national_best_offer_long_appendage_end()) };
    }

    std::optional<NationalBestOfferShortAppendage> national_best_offer_short_appendage() const {
        if (!(static_cast<char>(national_bbo_indicator()) == 'T')) { return std::nullopt; }
        wire::require("ShortQuoteMessage", national_best_bid_short_appendage_end() + NationalBestOfferShortAppendage::minimum_size, bytes_.size());
        return NationalBestOfferShortAppendage{ bytes_.subspan(national_best_bid_short_appendage_end()) };
    }

    void print(std::ostream& out) const {
        out << "ShortQuoteMessage{";
        out << "participant_id=";
        out << participant_id();
        out << ", participant_timestamp=";
        participant_timestamp().print(out);
        out << ", message_id=";
        out << static_cast<int>(message_id());
        out << ", transaction_id=";
        out << transaction_id();
        out << ", participant_reference_number=";
        out << participant_reference_number();
        out << ", security_symbol_short=";
        print::text(out, security_symbol_short());
        out << ", bid_price_short=";
        out << bid_price_short();
        out << ", bid_size_short=";
        out << bid_size_short();
        out << ", offer_price_short=";
        out << offer_price_short();
        out << ", offer_size_short=";
        out << offer_size_short();
        out << ", primary_listing_market_participant_id=";
        out << primary_listing_market_participant_id();
        out << ", national_bbo_indicator=";
        out << national_bbo_indicator();
        out << ", national_best_bid_long_appendage=";
        print::optional(out, national_best_bid_long_appendage());
        out << ", national_best_offer_long_appendage=";
        print::optional(out, national_best_offer_long_appendage());
        out << ", national_best_bid_short_appendage=";
        print::optional(out, national_best_bid_short_appendage());
        out << ", national_best_offer_short_appendage=";
        print::optional(out, national_best_offer_short_appendage());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t national_best_bid_long_appendage_end() const { return 37 + (national_best_bid_long_appendage() ? national_best_bid_long_appendage()->encoded_size() : 0); }
    std::size_t national_best_offer_long_appendage_end() const { return national_best_bid_long_appendage_end() + (national_best_offer_long_appendage() ? national_best_offer_long_appendage()->encoded_size() : 0); }
    std::size_t national_best_bid_short_appendage_end() const { return national_best_offer_long_appendage_end() + (national_best_bid_short_appendage() ? national_best_bid_short_appendage()->encoded_size() : 0); }
    std::size_t national_best_offer_short_appendage_end() const { return national_best_bid_short_appendage_end() + (national_best_offer_short_appendage() ? national_best_offer_short_appendage()->encoded_size() : 0); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const ShortQuoteMessage& value) {
    value.print(out);
    return out;
}

} // namespace siac::cqs::output::cta::v1_91
