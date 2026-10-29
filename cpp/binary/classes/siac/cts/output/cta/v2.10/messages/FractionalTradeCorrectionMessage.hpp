#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../enums/FinancialStatusIndicator.hpp"
#include "../enums/InstrumentType.hpp"
#include "../enums/ParticipantId.hpp"
#include "../enums/PrimaryListingMarketParticipantId.hpp"
#include "../enums/TradeReportingFacilityId.hpp"
#include "../messages/TradeMessagePayload.hpp"
#include "../structs/FractionalConsolidatedData.hpp"
#include "../structs/FractionalCorrectedTrade.hpp"
#include "../structs/FractionalOriginalTrade.hpp"
#include "../structs/FractionalParticipantData.hpp"
#include "../structs/Timestamp1.hpp"
#include "../structs/Timestamp2.hpp"

namespace siac::cts::output::cta::v2_10 {

class TradeMessagePayloadVisitor;

// The Trade Correction message is used to correct Cta eligible Equity, Local Issue or Bond
// information.
class FractionalTradeCorrectionMessage : public TradeMessagePayload {
  public:
    // The code that selects this message
    static constexpr TradeMessagePayloadCode message_type = TradeMessageType::FractionalTradeCorrectionMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 184;

    FractionalTradeCorrectionMessage() = default;
    FractionalTradeCorrectionMessage(ParticipantId participant_id, const Timestamp1& timestamp_1, std::uint8_t message_id, std::uint32_t transaction_id, std::int64_t participant_reference_number, const std::string& security_symbol, InstrumentType instrument_type, const FractionalCorrectedTrade& fractional_corrected_trade, TradeReportingFacilityId trade_reporting_facility_id, const Timestamp2& timestamp_2, std::int64_t original_participant_reference_number, const FractionalOriginalTrade& fractional_original_trade, PrimaryListingMarketParticipantId primary_listing_market_participant_id, FinancialStatusIndicator financial_status_indicator, const FractionalConsolidatedData& fractional_consolidated_data, const FractionalParticipantData& fractional_participant_data);

    // Participant Id: Participant or Processor that generated the message
    ParticipantId participant_id() const;
    void set_participant_id(ParticipantId value);

    // Timestamp 1: Timestamp 1
    const Timestamp1& timestamp_1() const;
    Timestamp1& timestamp_1();
    void set_timestamp_1(const Timestamp1& value);

    // Message Id: The Message ID identifies the individual message within the block beginning
    // with number one
    std::uint8_t message_id() const;
    void set_message_id(std::uint8_t value);

    // Transaction Id: The Transaction Id will be populated by CQS and is Reserved for Internal
    // Use only
    std::uint32_t transaction_id() const;
    void set_transaction_id(std::uint32_t value);

    // Participant Reference Number: Participant Reference Number is a pass-thru of the inbound
    // Participant Reference number assigned to a transaction
    std::int64_t participant_reference_number() const;
    void set_participant_reference_number(std::int64_t value);

    // Security Symbol: Contains the security symbol
    const std::string& security_symbol() const;
    std::string& security_symbol();
    void set_security_symbol(const std::string& value);

    // Instrument Type: Identifies the instrument type relevant to the trade
    InstrumentType instrument_type() const;
    void set_instrument_type(InstrumentType value);

    // Fractional Corrected Trade: Fractional Corrected Trade
    const FractionalCorrectedTrade& fractional_corrected_trade() const;
    FractionalCorrectedTrade& fractional_corrected_trade();
    void set_fractional_corrected_trade(const FractionalCorrectedTrade& value);

    // Trade Reporting Facility Id: Identifies the Participant with whom a Trade Reporting
    // Facility has been formed
    TradeReportingFacilityId trade_reporting_facility_id() const;
    void set_trade_reporting_facility_id(TradeReportingFacilityId value);

    // Timestamp 2: Timestamp 2
    const Timestamp2& timestamp_2() const;
    Timestamp2& timestamp_2();
    void set_timestamp_2(const Timestamp2& value);

    // Original Participant Reference Number: Contains the Participant Reference Number of
    // transaction to be corrected, cancelled or error
    std::int64_t original_participant_reference_number() const;
    void set_original_participant_reference_number(std::int64_t value);

    // Fractional Original Trade: Fractional Original Trade
    const FractionalOriginalTrade& fractional_original_trade() const;
    FractionalOriginalTrade& fractional_original_trade();
    void set_fractional_original_trade(const FractionalOriginalTrade& value);

    // Primary Listing Market Participant Id: Identifies the Primary Listing Market of the
    // security symbol
    PrimaryListingMarketParticipantId primary_listing_market_participant_id() const;
    void set_primary_listing_market_participant_id(PrimaryListingMarketParticipantId value);

    // Financial Status Indicator: Identifies the financial status of the security.
    FinancialStatusIndicator financial_status_indicator() const;
    void set_financial_status_indicator(FinancialStatusIndicator value);

    // Fractional Consolidated Data: Fractional Consolidated Data
    const FractionalConsolidatedData& fractional_consolidated_data() const;
    FractionalConsolidatedData& fractional_consolidated_data();
    void set_fractional_consolidated_data(const FractionalConsolidatedData& value);

    // Fractional Participant Data: Fractional Participant Data
    const FractionalParticipantData& fractional_participant_data() const;
    FractionalParticipantData& fractional_participant_data();
    void set_fractional_participant_data(const FractionalParticipantData& value);

    // TradeMessagePayload
    TradeMessagePayloadCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(TradeMessagePayloadVisitor& visitor) const override;
    std::unique_ptr<TradeMessagePayload> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const TradeMessagePayload& other) const override;

    bool operator==(const FractionalTradeCorrectionMessage& other) const;
    bool operator!=(const FractionalTradeCorrectionMessage& other) const;

  private:
    ParticipantId participant_id_{};
    Timestamp1 timestamp_1_{};
    std::uint8_t message_id_{};
    std::uint32_t transaction_id_{};
    std::int64_t participant_reference_number_{};
    std::string security_symbol_{};
    InstrumentType instrument_type_{};
    FractionalCorrectedTrade fractional_corrected_trade_{};
    TradeReportingFacilityId trade_reporting_facility_id_{};
    Timestamp2 timestamp_2_{};
    std::int64_t original_participant_reference_number_{};
    FractionalOriginalTrade fractional_original_trade_{};
    PrimaryListingMarketParticipantId primary_listing_market_participant_id_{};
    FinancialStatusIndicator financial_status_indicator_{};
    FractionalConsolidatedData fractional_consolidated_data_{};
    FractionalParticipantData fractional_participant_data_{};
};

} // namespace siac::cts::output::cta::v2_10
