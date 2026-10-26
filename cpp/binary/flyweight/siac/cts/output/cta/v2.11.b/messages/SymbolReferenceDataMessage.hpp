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
#include "../enums/PrimaryListingMarketParticipantId.hpp"
#include "../common/Decimal.hpp"
#include "../enums/MinimumPriceIncrementIndicator.hpp"
#include "../enums/LuldTier.hpp"
#include "../enums/Test.hpp"
#include "../enums/Ipo.hpp"
#include "../enums/FinancialStatusIndicator.hpp"
#include "../enums/ShortSaleRestrictionIndicator.hpp"
#include "../enums/HaltReason.hpp"
#include "../enums/InstrumentType.hpp"

namespace siac::cts::output::cta::v2_11_b {

// Symbol Reference Data message
class SymbolReferenceDataMessage {
  public:
    static constexpr const char* name = "SymbolReferenceDataMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SymbolReferenceDataMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SymbolReferenceDataMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 205;
    static constexpr std::size_t fixed_size = 205;
    std::size_t encoded_size() const { return 205; }

    ParticipantId participant_id() const { return static_cast<ParticipantId>(wire::read_char(at(0))); }

    Timestamp1 timestamp_1() const { return Timestamp1{ bytes_.subspan(1) }; }

    std::uint8_t message_id() const { return wire::read_u8(at(9)); }

    std::uint32_t transaction_id() const { return wire::read_u32_be(at(10)); }

    std::int64_t participant_reference_number() const { return wire::read_i64_be(at(14)); }

    std::string_view security_symbol() const { return view::text(at(22), 11, ' '); }

    std::string_view prior_security_symbol() const { return view::text(at(33), 11, ' '); }

    PrimaryListingMarketParticipantId primary_listing_market_participant_id() const { return static_cast<PrimaryListingMarketParticipantId>(wire::read_char(at(44))); }

    Decimal primary_listing_market_previous_closing_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_be(at(45))), -6); }

    Decimal consolidated_closing_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_be(at(53))), -6); }

    std::uint16_t round_lot_size() const { return wire::read_u16_be(at(61)); }

    MinimumPriceIncrementIndicator minimum_price_increment_indicator() const { return static_cast<MinimumPriceIncrementIndicator>(wire::read_char(at(63))); }

    LuldTier luld_tier() const { return static_cast<LuldTier>(wire::read_char(at(64))); }

    Decimal luld_leverage_ratio() const { return Decimal(static_cast<std::int64_t>(wire::read_u32_be(at(65))), -6); }

    Test test() const { return static_cast<Test>(wire::read_char(at(69))); }

    Ipo ipo() const { return static_cast<Ipo>(wire::read_char(at(70))); }

    FinancialStatusIndicator financial_status_indicator() const { return static_cast<FinancialStatusIndicator>(wire::read_char(at(71))); }

    ShortSaleRestrictionIndicator short_sale_restriction_indicator() const { return static_cast<ShortSaleRestrictionIndicator>(wire::read_char(at(72))); }

    HaltReason halt_reason() const { return static_cast<HaltReason>(wire::read_char(at(73))); }

    InstrumentType instrument_type() const { return static_cast<InstrumentType>(wire::read_char(at(74))); }

    char reserved() const { return wire::read_char(at(75)); }

    char second_reserved() const { return wire::read_char(at(76)); }

    std::string_view reserved_128() const { return view::text(at(77), 128, ' '); }

    void print(std::ostream& out) const {
        out << "SymbolReferenceDataMessage{";
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
        out << ", prior_security_symbol=";
        print::text(out, prior_security_symbol());
        out << ", primary_listing_market_participant_id=";
        out << primary_listing_market_participant_id();
        out << ", primary_listing_market_previous_closing_price=";
        out << primary_listing_market_previous_closing_price();
        out << ", consolidated_closing_price=";
        out << consolidated_closing_price();
        out << ", round_lot_size=";
        out << round_lot_size();
        out << ", minimum_price_increment_indicator=";
        out << minimum_price_increment_indicator();
        out << ", luld_tier=";
        out << luld_tier();
        out << ", luld_leverage_ratio=";
        out << luld_leverage_ratio();
        out << ", test=";
        out << test();
        out << ", ipo=";
        out << ipo();
        out << ", financial_status_indicator=";
        out << financial_status_indicator();
        out << ", short_sale_restriction_indicator=";
        out << short_sale_restriction_indicator();
        out << ", halt_reason=";
        out << halt_reason();
        out << ", instrument_type=";
        out << instrument_type();
        out << ", reserved=";
        print::character(out, reserved());
        out << ", second_reserved=";
        print::character(out, second_reserved());
        out << ", reserved_128=";
        print::text(out, reserved_128());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const SymbolReferenceDataMessage& value) {
    value.print(out);
    return out;
}

} // namespace siac::cts::output::cta::v2_11_b
