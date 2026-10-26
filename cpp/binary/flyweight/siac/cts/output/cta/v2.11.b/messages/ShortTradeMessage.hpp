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
#include "../enums/SaleCondition1.hpp"
#include "../enums/SaleConditionCategory.hpp"
#include "../common/Decimal.hpp"
#include "../enums/PrimaryListingMarketParticipantId.hpp"
#include "../enums/ConsolidatedHighLowLastIndicator.hpp"
#include "../enums/ParticipantOpenHighLowLastIndicator.hpp"

namespace siac::cts::output::cta::v2_11_b {

// Used to report trade information for CTA eligible Equity only. To be descoped when
// Fractional Trade Volume publication is activated
class ShortTradeMessage {
  public:
    static constexpr const char* name = "ShortTradeMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit ShortTradeMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every ShortTradeMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 36;
    static constexpr std::size_t fixed_size = 36;
    std::size_t encoded_size() const { return 36; }

    ParticipantId participant_id() const { return static_cast<ParticipantId>(wire::read_char(at(0))); }

    Timestamp1 timestamp_1() const { return Timestamp1{ bytes_.subspan(1) }; }

    std::uint8_t message_id() const { return wire::read_u8(at(9)); }

    std::uint32_t transaction_id() const { return wire::read_u32_be(at(10)); }

    std::int64_t participant_reference_number() const { return wire::read_i64_be(at(14)); }

    std::string_view security_symbol_5() const { return view::text(at(22), 5, ' '); }

    SaleCondition1 sale_condition_1() const { return static_cast<SaleCondition1>(wire::read_char(at(27))); }

    SaleConditionCategory sale_condition_category() const { return static_cast<SaleConditionCategory>(wire::read_char(at(28))); }

    Decimal trade_price_2() const { return Decimal(static_cast<std::int64_t>(wire::read_u16_be(at(29))), -2); }

    std::uint16_t trade_volume_2() const { return wire::read_u16_be(at(31)); }

    PrimaryListingMarketParticipantId primary_listing_market_participant_id() const { return static_cast<PrimaryListingMarketParticipantId>(wire::read_char(at(33))); }

    ConsolidatedHighLowLastIndicator consolidated_high_low_last_indicator() const { return static_cast<ConsolidatedHighLowLastIndicator>(wire::read_char(at(34))); }

    ParticipantOpenHighLowLastIndicator participant_open_high_low_last_indicator() const { return static_cast<ParticipantOpenHighLowLastIndicator>(wire::read_char(at(35))); }

    void print(std::ostream& out) const {
        out << "ShortTradeMessage{";
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
        out << ", security_symbol_5=";
        print::text(out, security_symbol_5());
        out << ", sale_condition_1=";
        out << sale_condition_1();
        out << ", sale_condition_category=";
        out << sale_condition_category();
        out << ", trade_price_2=";
        out << trade_price_2();
        out << ", trade_volume_2=";
        out << trade_volume_2();
        out << ", primary_listing_market_participant_id=";
        out << primary_listing_market_participant_id();
        out << ", consolidated_high_low_last_indicator=";
        out << consolidated_high_low_last_indicator();
        out << ", participant_open_high_low_last_indicator=";
        out << participant_open_high_low_last_indicator();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const ShortTradeMessage& value) {
    value.print(out);
    return out;
}

} // namespace siac::cts::output::cta::v2_11_b
