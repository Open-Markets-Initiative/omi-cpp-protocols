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
#include "../common/Decimal.hpp"
#include "../enums/ShortSaleRestrictionIndicator.hpp"
#include "../enums/PrimaryListingMarketParticipantId.hpp"
#include "../enums/FinancialStatusIndicator.hpp"

namespace siac::cts::output::cta::v1_91 {

// The Consolidated Start of Day Summary messages are transmitted shortly after the Multicast
// Line ‘Start of Day’ message
class ConsolidatedStartOfDaySummaryMessage {
  public:
    static constexpr const char* name = "ConsolidatedStartOfDaySummaryMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit ConsolidatedStartOfDaySummaryMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every ConsolidatedStartOfDaySummaryMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 51;
    static constexpr std::size_t fixed_size = 51;
    std::size_t encoded_size() const { return 51; }

    ParticipantId participant_id() const { return static_cast<ParticipantId>(wire::read_char(at(0))); }

    Timestamp1 timestamp_1() const { return Timestamp1{ bytes_.subspan(1) }; }

    std::uint8_t message_id() const { return wire::read_u8(at(9)); }

    std::uint32_t transaction_id() const { return wire::read_u32_be(at(10)); }

    std::int64_t participant_reference_number() const { return wire::read_i64_be(at(14)); }

    std::string_view security_symbol() const { return view::text(at(22), 11, ' '); }

    InstrumentType instrument_type() const { return static_cast<InstrumentType>(wire::read_char(at(33))); }

    char summary_participant_id() const { return wire::read_char(at(34)); }

    std::uint32_t previous_close_price_date() const { return wire::read_u32_be(at(35)); }

    Decimal previous_close_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_be(at(39))), -6); }

    ShortSaleRestrictionIndicator short_sale_restriction_indicator() const { return static_cast<ShortSaleRestrictionIndicator>(wire::read_char(at(47))); }

    PrimaryListingMarketParticipantId primary_listing_market_participant_id() const { return static_cast<PrimaryListingMarketParticipantId>(wire::read_char(at(48))); }

    FinancialStatusIndicator financial_status_indicator() const { return static_cast<FinancialStatusIndicator>(wire::read_char(at(49))); }

    std::uint8_t number_of_participants() const { return wire::read_u8(at(50)); }

    void print(std::ostream& out) const {
        out << "ConsolidatedStartOfDaySummaryMessage{";
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
        out << ", summary_participant_id=";
        print::character(out, summary_participant_id());
        out << ", previous_close_price_date=";
        out << previous_close_price_date();
        out << ", previous_close_price=";
        out << previous_close_price();
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

inline std::ostream& operator<<(std::ostream& out, const ConsolidatedStartOfDaySummaryMessage& value) {
    value.print(out);
    return out;
}

} // namespace siac::cts::output::cta::v1_91
