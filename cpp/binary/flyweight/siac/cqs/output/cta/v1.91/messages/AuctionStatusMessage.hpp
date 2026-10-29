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
#include "../enums/InstrumentType.hpp"
#include "../common/Decimal.hpp"
#include "../enums/ShortSaleRestrictionIndicator.hpp"
#include "../enums/PrimaryListingMarketParticipantId.hpp"
#include "../enums/FinancialStatusIndicator.hpp"

namespace siac::cqs::output::cta::v1_91 {

// The Auction Status message is used when a Participant in a Cta eligible security
class AuctionStatusMessage {
  public:
    static constexpr const char* name = "AuctionStatusMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit AuctionStatusMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every AuctionStatusMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 63;
    static constexpr std::size_t fixed_size = 63;
    std::size_t encoded_size() const { return 63; }

    ParticipantId participant_id() const { return static_cast<ParticipantId>(wire::read_char(at(0))); }

    ParticipantTimestamp participant_timestamp() const { return ParticipantTimestamp{ bytes_.subspan(1) }; }

    std::uint8_t message_id() const { return wire::read_u8(at(9)); }

    std::uint32_t transaction_id() const { return wire::read_u32_be(at(10)); }

    std::int64_t participant_reference_number() const { return wire::read_i64_be(at(14)); }

    std::string_view security_symbol_long() const { return view::text(at(22), 11, ' '); }

    InstrumentType instrument_type() const { return static_cast<InstrumentType>(wire::read_char(at(33))); }

    std::optional<Decimal> auction_collar_reference_price() const { return wire::nullable_decimal(wire::read_u64_be(at(34)), static_cast<std::uint64_t>(0ULL), -6); }

    std::optional<Decimal> auction_collar_upper_threshold_price() const { return wire::nullable_decimal(wire::read_u64_be(at(42)), static_cast<std::uint64_t>(0ULL), -6); }

    std::optional<Decimal> auction_collar_lower_threshold_price() const { return wire::nullable_decimal(wire::read_u64_be(at(50)), static_cast<std::uint64_t>(0ULL), -6); }

    std::uint8_t number_of_extensions() const { return wire::read_u8(at(58)); }

    ShortSaleRestrictionIndicator short_sale_restriction_indicator() const { return static_cast<ShortSaleRestrictionIndicator>(wire::read_char(at(59))); }

    PrimaryListingMarketParticipantId primary_listing_market_participant_id() const { return static_cast<PrimaryListingMarketParticipantId>(wire::read_char(at(60))); }

    FinancialStatusIndicator financial_status_indicator() const { return static_cast<FinancialStatusIndicator>(wire::read_char(at(61))); }

    char future() const { return wire::read_char(at(62)); }

    void print(std::ostream& out) const {
        out << "AuctionStatusMessage{";
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
        out << ", security_symbol_long=";
        print::text(out, security_symbol_long());
        out << ", instrument_type=";
        out << instrument_type();
        out << ", auction_collar_reference_price=";
        print::optional(out, auction_collar_reference_price());
        out << ", auction_collar_upper_threshold_price=";
        print::optional(out, auction_collar_upper_threshold_price());
        out << ", auction_collar_lower_threshold_price=";
        print::optional(out, auction_collar_lower_threshold_price());
        out << ", number_of_extensions=";
        out << static_cast<int>(number_of_extensions());
        out << ", short_sale_restriction_indicator=";
        out << short_sale_restriction_indicator();
        out << ", primary_listing_market_participant_id=";
        out << primary_listing_market_participant_id();
        out << ", financial_status_indicator=";
        out << financial_status_indicator();
        out << ", future=";
        print::character(out, future());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const AuctionStatusMessage& value) {
    value.print(out);
    return out;
}

} // namespace siac::cqs::output::cta::v1_91
