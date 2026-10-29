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
#include "../structs/ConsolidatedData.hpp"
#include "../structs/CorrectedTrade.hpp"
#include "../structs/OriginalTrade.hpp"
#include "../structs/ParticipantData.hpp"
#include "../structs/Timestamp1.hpp"
#include "../structs/Timestamp2.hpp"

namespace siac::cts::output::cta::v1_91 {

class TradeMessagePayloadVisitor;

// The Trade Correction message is used to correct Cta eligible Equity, Local Issue or Bond
// information.
class TradeCorrectionMessage : public TradeMessagePayload {
  public:
    // The code that selects this message
    static constexpr TradeMessagePayloadCode message_type = TradeMessageType::TradeCorrectionMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 185;

    TradeCorrectionMessage() = default;
    TradeCorrectionMessage(ParticipantId participant_id, const Timestamp1& timestamp_1, std::uint8_t message_id, std::uint32_t transaction_id, std::int64_t participant_reference_number, const std::string& security_symbol, InstrumentType instrument_type, const CorrectedTrade& corrected_trade, TradeReportingFacilityId trade_reporting_facility_id, const Timestamp2& timestamp_2, std::int64_t original_participant_reference_number, const OriginalTrade& original_trade, PrimaryListingMarketParticipantId primary_listing_market_participant_id, FinancialStatusIndicator financial_status_indicator, const ConsolidatedData& consolidated_data, const ParticipantData& participant_data);

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

    // Corrected Trade: Corrected Trade
    const CorrectedTrade& corrected_trade() const;
    CorrectedTrade& corrected_trade();
    void set_corrected_trade(const CorrectedTrade& value);

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

    // Original Trade: Original Trade
    const OriginalTrade& original_trade() const;
    OriginalTrade& original_trade();
    void set_original_trade(const OriginalTrade& value);

    // Primary Listing Market Participant Id: Identifies the Primary Listing Market of the
    // security symbol
    PrimaryListingMarketParticipantId primary_listing_market_participant_id() const;
    void set_primary_listing_market_participant_id(PrimaryListingMarketParticipantId value);

    // Financial Status Indicator: Identifies the financial status of the security.
    FinancialStatusIndicator financial_status_indicator() const;
    void set_financial_status_indicator(FinancialStatusIndicator value);

    // Consolidated Data: Consolidated Data
    const ConsolidatedData& consolidated_data() const;
    ConsolidatedData& consolidated_data();
    void set_consolidated_data(const ConsolidatedData& value);

    // Participant Data: Participant Data
    const ParticipantData& participant_data() const;
    ParticipantData& participant_data();
    void set_participant_data(const ParticipantData& value);

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

    bool operator==(const TradeCorrectionMessage& other) const;
    bool operator!=(const TradeCorrectionMessage& other) const;

  private:
    ParticipantId participant_id_{};
    Timestamp1 timestamp_1_{};
    std::uint8_t message_id_{};
    std::uint32_t transaction_id_{};
    std::int64_t participant_reference_number_{};
    std::string security_symbol_{};
    InstrumentType instrument_type_{};
    CorrectedTrade corrected_trade_{};
    TradeReportingFacilityId trade_reporting_facility_id_{};
    Timestamp2 timestamp_2_{};
    std::int64_t original_participant_reference_number_{};
    OriginalTrade original_trade_{};
    PrimaryListingMarketParticipantId primary_listing_market_participant_id_{};
    FinancialStatusIndicator financial_status_indicator_{};
    ConsolidatedData consolidated_data_{};
    ParticipantData participant_data_{};
};

} // namespace siac::cts::output::cta::v1_91
