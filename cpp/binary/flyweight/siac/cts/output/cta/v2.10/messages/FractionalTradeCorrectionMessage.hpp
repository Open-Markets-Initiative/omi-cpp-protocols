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
#include "../structs/FractionalCorrectedTrade.hpp"
#include "../enums/TradeReportingFacilityId.hpp"
#include "../structs/Timestamp2.hpp"
#include "../structs/FractionalOriginalTrade.hpp"
#include "../enums/PrimaryListingMarketParticipantId.hpp"
#include "../enums/FinancialStatusIndicator.hpp"
#include "../structs/FractionalConsolidatedData.hpp"
#include "../structs/FractionalParticipantData.hpp"

namespace siac::cts::output::cta::v2_10 {

// The Trade Correction message is used to correct Cta eligible Equity, Local Issue or Bond
// information.
class FractionalTradeCorrectionMessage {
  public:
    static constexpr const char* name = "FractionalTradeCorrectionMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit FractionalTradeCorrectionMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every FractionalTradeCorrectionMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 184;
    static constexpr std::size_t fixed_size = 184;
    std::size_t encoded_size() const { return 184; }

    ParticipantId participant_id() const { return static_cast<ParticipantId>(wire::read_char(at(0))); }

    Timestamp1 timestamp_1() const { return Timestamp1{ bytes_.subspan(1) }; }

    std::uint8_t message_id() const { return wire::read_u8(at(9)); }

    std::uint32_t transaction_id() const { return wire::read_u32_be(at(10)); }

    std::int64_t participant_reference_number() const { return wire::read_i64_be(at(14)); }

    std::string_view security_symbol() const { return view::text(at(22), 11, ' '); }

    InstrumentType instrument_type() const { return static_cast<InstrumentType>(wire::read_char(at(33))); }

    FractionalCorrectedTrade fractional_corrected_trade() const { return FractionalCorrectedTrade{ bytes_.subspan(34) }; }

    TradeReportingFacilityId trade_reporting_facility_id() const { return static_cast<TradeReportingFacilityId>(wire::read_char(at(58))); }

    Timestamp2 timestamp_2() const { return Timestamp2{ bytes_.subspan(59) }; }

    std::int64_t original_participant_reference_number() const { return wire::read_i64_be(at(67)); }

    FractionalOriginalTrade fractional_original_trade() const { return FractionalOriginalTrade{ bytes_.subspan(75) }; }

    PrimaryListingMarketParticipantId primary_listing_market_participant_id() const { return static_cast<PrimaryListingMarketParticipantId>(wire::read_char(at(99))); }

    FinancialStatusIndicator financial_status_indicator() const { return static_cast<FinancialStatusIndicator>(wire::read_char(at(100))); }

    FractionalConsolidatedData fractional_consolidated_data() const { return FractionalConsolidatedData{ bytes_.subspan(101) }; }

    FractionalParticipantData fractional_participant_data() const { return FractionalParticipantData{ bytes_.subspan(139) }; }

    void print(std::ostream& out) const {
        out << "FractionalTradeCorrectionMessage{";
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
        out << ", fractional_corrected_trade=";
        fractional_corrected_trade().print(out);
        out << ", trade_reporting_facility_id=";
        out << trade_reporting_facility_id();
        out << ", timestamp_2=";
        timestamp_2().print(out);
        out << ", original_participant_reference_number=";
        out << original_participant_reference_number();
        out << ", fractional_original_trade=";
        fractional_original_trade().print(out);
        out << ", primary_listing_market_participant_id=";
        out << primary_listing_market_participant_id();
        out << ", financial_status_indicator=";
        out << financial_status_indicator();
        out << ", fractional_consolidated_data=";
        fractional_consolidated_data().print(out);
        out << ", fractional_participant_data=";
        fractional_participant_data().print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const FractionalTradeCorrectionMessage& value) {
    value.print(out);
    return out;
}

} // namespace siac::cts::output::cta::v2_10
