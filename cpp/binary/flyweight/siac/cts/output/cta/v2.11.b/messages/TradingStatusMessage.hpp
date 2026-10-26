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
#include "../enums/SecurityStatus.hpp"
#include "../enums/HaltReason.hpp"
#include "../enums/ShortSaleRestrictionIndicator.hpp"
#include "../enums/PrimaryListingMarketParticipantId.hpp"
#include "../enums/FinancialStatusIndicator.hpp"
#include "../enums/LimitUpLimitDownLuldIndicator.hpp"

namespace siac::cts::output::cta::v2_11_b {

// Transmitted when a Participant in a CTA eligible security, Local Issue or a Bond elects to
// notify CTS of a Trading Halt, a Trading Resume, a Price Indication or a Market Imbalance
class TradingStatusMessage {
  public:
    static constexpr const char* name = "TradingStatusMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit TradingStatusMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every TradingStatusMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 72;
    static constexpr std::size_t fixed_size = 72;
    std::size_t encoded_size() const { return 72; }

    ParticipantId participant_id() const { return static_cast<ParticipantId>(wire::read_char(at(0))); }

    Timestamp1 timestamp_1() const { return Timestamp1{ bytes_.subspan(1) }; }

    std::uint8_t message_id() const { return wire::read_u8(at(9)); }

    std::uint32_t transaction_id() const { return wire::read_u32_be(at(10)); }

    std::int64_t participant_reference_number() const { return wire::read_i64_be(at(14)); }

    std::string_view security_symbol() const { return view::text(at(22), 11, ' '); }

    InstrumentType instrument_type() const { return static_cast<InstrumentType>(wire::read_char(at(33))); }

    Decimal last_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_be(at(34))), -6); }

    Decimal high_indication_price_upper_limit_price_band() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_be(at(42))), -6); }

    Decimal low_indication_price_lower_limit_price_band() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_be(at(50))), -6); }

    std::uint32_t buy_volume() const { return wire::read_u32_be(at(58)); }

    std::uint32_t sell_volume() const { return wire::read_u32_be(at(62)); }

    SecurityStatus security_status() const { return static_cast<SecurityStatus>(wire::read_char(at(66))); }

    HaltReason halt_reason() const { return static_cast<HaltReason>(wire::read_char(at(67))); }

    ShortSaleRestrictionIndicator short_sale_restriction_indicator() const { return static_cast<ShortSaleRestrictionIndicator>(wire::read_char(at(68))); }

    PrimaryListingMarketParticipantId primary_listing_market_participant_id() const { return static_cast<PrimaryListingMarketParticipantId>(wire::read_char(at(69))); }

    FinancialStatusIndicator financial_status_indicator() const { return static_cast<FinancialStatusIndicator>(wire::read_char(at(70))); }

    LimitUpLimitDownLuldIndicator limit_up_limit_down_luld_indicator() const { return static_cast<LimitUpLimitDownLuldIndicator>(wire::read_char(at(71))); }

    void print(std::ostream& out) const {
        out << "TradingStatusMessage{";
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
        out << ", last_price=";
        out << last_price();
        out << ", high_indication_price_upper_limit_price_band=";
        out << high_indication_price_upper_limit_price_band();
        out << ", low_indication_price_lower_limit_price_band=";
        out << low_indication_price_lower_limit_price_band();
        out << ", buy_volume=";
        out << buy_volume();
        out << ", sell_volume=";
        out << sell_volume();
        out << ", security_status=";
        out << security_status();
        out << ", halt_reason=";
        out << halt_reason();
        out << ", short_sale_restriction_indicator=";
        out << short_sale_restriction_indicator();
        out << ", primary_listing_market_participant_id=";
        out << primary_listing_market_participant_id();
        out << ", financial_status_indicator=";
        out << financial_status_indicator();
        out << ", limit_up_limit_down_luld_indicator=";
        out << limit_up_limit_down_luld_indicator();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const TradingStatusMessage& value) {
    value.print(out);
    return out;
}

} // namespace siac::cts::output::cta::v2_11_b
