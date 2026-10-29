#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/FinancialStatusIndicator.hpp"
#include "../enums/InstrumentType.hpp"
#include "../enums/LastParticipantId.hpp"
#include "../enums/ParticipantId.hpp"
#include "../enums/PrimaryListingMarketParticipantId.hpp"
#include "../enums/ShortSaleRestrictionIndicator.hpp"
#include "../messages/SummaryMessagePayload.hpp"
#include "../structs/Timestamp1.hpp"

namespace siac::cts::output::cta::v2_10 {

class SummaryMessagePayloadVisitor;

// The Consolidated End of Day Summary messages are transmitted shortly before the "Goodnight"
// messages
class ConsolidatedEndOfDaySummaryMessage : public SummaryMessagePayload {
  public:
    // The code that selects this message
    static constexpr SummaryMessagePayloadCode message_type = SummaryMessageType::ConsolidatedEndOfDaySummaryMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 75;

    ConsolidatedEndOfDaySummaryMessage() = default;
    ConsolidatedEndOfDaySummaryMessage(ParticipantId participant_id, const Timestamp1& timestamp_1, std::uint8_t message_id, std::uint32_t transaction_id, std::int64_t participant_reference_number, const std::string& security_symbol, InstrumentType instrument_type, LastParticipantId last_participant_id, std::uint32_t previous_close_price_date, Decimal last_price, Decimal high_price, Decimal low_price, std::uint64_t total_volume, ShortSaleRestrictionIndicator short_sale_restriction_indicator, PrimaryListingMarketParticipantId primary_listing_market_participant_id, FinancialStatusIndicator financial_status_indicator, std::uint8_t number_of_participants);

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

    // Last Participant Id: Refer to Participant ID field description for Participant codes
    LastParticipantId last_participant_id() const;
    void set_last_participant_id(LastParticipantId value);

    // Previous Close Price Date: Represents the date the security last traded
    std::uint32_t previous_close_price_date() const;
    void set_previous_close_price_date(std::uint32_t value);

    // Last Price: The Last Price represents the last price for that security either on a
    // Consolidated or an individual Participant basis at the time it is disseminated
    Decimal last_price() const;
    void set_last_price(Decimal value);

    // High Price: The High Price represents the highest price paid for a security during the
    // trading day
    Decimal high_price() const;
    void set_high_price(Decimal value);

    // Low Price: The Low Price represents the lowest price paid for a security during the
    // trading day
    Decimal low_price() const;
    void set_low_price(Decimal value);

    // Total Volume: Contains Total Volume of shares traded in a security either on a
    // Consolidated or an individual Participant basis at the time it is disseminated
    std::uint64_t total_volume() const;
    void set_total_volume(std::uint64_t value);

    // Short Sale Restriction Indicator: Identifies whether or not a Short Sale Restriction is
    // in effect for a security
    ShortSaleRestrictionIndicator short_sale_restriction_indicator() const;
    void set_short_sale_restriction_indicator(ShortSaleRestrictionIndicator value);

    // Primary Listing Market Participant Id: Identifies the Primary Listing Market of the
    // security symbol
    PrimaryListingMarketParticipantId primary_listing_market_participant_id() const;
    void set_primary_listing_market_participant_id(PrimaryListingMarketParticipantId value);

    // Financial Status Indicator: Identifies the financial status of the security.
    FinancialStatusIndicator financial_status_indicator() const;
    void set_financial_status_indicator(FinancialStatusIndicator value);

    // Number Of Participants: Represents the actual number of Participants for which an issue
    // will be reported.
    std::uint8_t number_of_participants() const;
    void set_number_of_participants(std::uint8_t value);

    // SummaryMessagePayload
    SummaryMessagePayloadCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(SummaryMessagePayloadVisitor& visitor) const override;
    std::unique_ptr<SummaryMessagePayload> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const SummaryMessagePayload& other) const override;

    bool operator==(const ConsolidatedEndOfDaySummaryMessage& other) const;
    bool operator!=(const ConsolidatedEndOfDaySummaryMessage& other) const;

  private:
    ParticipantId participant_id_{};
    Timestamp1 timestamp_1_{};
    std::uint8_t message_id_{};
    std::uint32_t transaction_id_{};
    std::int64_t participant_reference_number_{};
    std::string security_symbol_{};
    InstrumentType instrument_type_{};
    LastParticipantId last_participant_id_{};
    std::uint32_t previous_close_price_date_{};
    Decimal last_price_{ 0, -6 };
    Decimal high_price_{ 0, -6 };
    Decimal low_price_{ 0, -6 };
    std::uint64_t total_volume_{};
    ShortSaleRestrictionIndicator short_sale_restriction_indicator_{};
    PrimaryListingMarketParticipantId primary_listing_market_participant_id_{};
    FinancialStatusIndicator financial_status_indicator_{};
    std::uint8_t number_of_participants_{};
};

} // namespace siac::cts::output::cta::v2_10
