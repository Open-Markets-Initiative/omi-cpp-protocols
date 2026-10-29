#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/ParticipantId.hpp"
#include "../structs/Timestamp1.hpp"
#include "../enums/InstrumentType.hpp"
#include "../enums/LastParticipantId.hpp"
#include "../common/Decimal.hpp"
#include "../enums/ShortSaleRestrictionIndicator.hpp"
#include "../enums/PrimaryListingMarketParticipantId.hpp"
#include "../enums/FinancialStatusIndicator.hpp"

namespace siac::cts::output::cta::v2_9 {

// The Consolidated End of Day Summary messages are transmitted shortly before the "Goodnight"
// messages
class ConsolidatedEndOfDaySummaryMessage {
  public:
    static constexpr const char* name = "ConsolidatedEndOfDaySummaryMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit ConsolidatedEndOfDaySummaryMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every ConsolidatedEndOfDaySummaryMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 75;
    static constexpr std::size_t fixed_size = 75;
    std::size_t encoded_size() const { return 75; }

    ParticipantId participant_id() const { return static_cast<ParticipantId>(wire::read_char(at(0))); }

    Timestamp1 timestamp_1() const { return Timestamp1{ bytes_.subspan(1) }; }

    std::uint8_t message_id() const { return wire::read_u8(at(9)); }

    std::uint32_t transaction_id() const { return wire::read_u32_be(at(10)); }

    std::int64_t participant_reference_number() const { return wire::read_i64_be(at(14)); }

    std::string_view security_symbol() const { return view::text(at(22), 11, ' '); }

    InstrumentType instrument_type() const { return static_cast<InstrumentType>(wire::read_char(at(33))); }

    LastParticipantId last_participant_id() const { return static_cast<LastParticipantId>(wire::read_char(at(34))); }

    std::uint32_t previous_close_price_date() const { return wire::read_u32_be(at(35)); }

    Decimal last_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_be(at(39))), -6); }

    Decimal high_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_be(at(47))), -6); }

    Decimal low_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_be(at(55))), -6); }

    std::uint64_t total_volume() const { return wire::read_u64_be(at(63)); }

    ShortSaleRestrictionIndicator short_sale_restriction_indicator() const { return static_cast<ShortSaleRestrictionIndicator>(wire::read_char(at(71))); }

    PrimaryListingMarketParticipantId primary_listing_market_participant_id() const { return static_cast<PrimaryListingMarketParticipantId>(wire::read_char(at(72))); }

    FinancialStatusIndicator financial_status_indicator() const { return static_cast<FinancialStatusIndicator>(wire::read_char(at(73))); }

    std::uint8_t number_of_participants() const { return wire::read_u8(at(74)); }

    void print(std::ostream& out) const {
        out << "ConsolidatedEndOfDaySummaryMessage{";
        out << "participant_id=";
        out << participant_id();
        out << ", timestamp_1=";
        timestamp_1().print(out);
        out << ", message_id=";
        out << static_cast<int>(message_id());
        out << ", transaction_id=";
        out << transaction_id();
        out << ", participant_reference_number=";
        out << participant_reference_number();
        out << ", security_symbol=";
        print::text(out, security_symbol());
        out << ", instrument_type=";
        out << instrument_type();
        out << ", last_participant_id=";
        out << last_participant_id();
        out << ", previous_close_price_date=";
        out << previous_close_price_date();
        out << ", last_price=";
        out << last_price();
        out << ", high_price=";
        out << high_price();
        out << ", low_price=";
        out << low_price();
        out << ", total_volume=";
        out << total_volume();
        out << ", short_sale_restriction_indicator=";
        out << short_sale_restriction_indicator();
        out << ", primary_listing_market_participant_id=";
        out << primary_listing_market_participant_id();
        out << ", financial_status_indicator=";
        out << financial_status_indicator();
        out << ", number_of_participants=";
        out << static_cast<int>(number_of_participants());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const ConsolidatedEndOfDaySummaryMessage& value) {
    value.print(out);
    return out;
}

} // namespace siac::cts::output::cta::v2_9
