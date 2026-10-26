#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/ParticipantId.hpp"
#include "../messages/MarketStatusMessagePayload.hpp"
#include "../structs/Timestamp1.hpp"

namespace siac::cqs::output::cta::v2_10_a {

class MarketStatusMessagePayloadVisitor;

// Reports the calculated Level 1, Level 2 and Level 3 threshold values for the current trading
// day necessary to trigger a circuit breaker
class MarketWideCircuitBreakerDeclineLevelStatusMessage : public MarketStatusMessagePayload {
  public:
    // The code that selects this message
    static constexpr MarketStatusMessagePayloadCode message_type = MarketStatusMessageType::MarketWideCircuitBreakerDeclineLevelStatus;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 47;

    MarketWideCircuitBreakerDeclineLevelStatusMessage() = default;
    MarketWideCircuitBreakerDeclineLevelStatusMessage(ParticipantId participant_id, const Timestamp1& timestamp_1, std::uint8_t message_id, std::uint32_t transaction_id, std::int64_t participant_reference_number, Decimal mwcb_level_1, Decimal mwcb_level_2, Decimal mwcb_level_3, char reserved);

    // Participant Id: Identifies the Participant or Processor that generated the message
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

    // Transaction Id: The Transaction ID will be populated by CQS and is Reserved for Internal
    // Use only
    std::uint32_t transaction_id() const;
    void set_transaction_id(std::uint32_t value);

    // Participant Reference Number: Participant Reference Number is a pass-thru of the inbound
    // Participant Reference number assigned to a transaction
    std::int64_t participant_reference_number() const;
    void set_participant_reference_number(std::int64_t value);

    // Mwcb Level 1: Identifies the daily established drop level value associated with Level 1
    // = 7% of Previous Close S&P 500 Value. Has implied 6 decimal places
    Decimal mwcb_level_1() const;
    void set_mwcb_level_1(Decimal value);

    // Mwcb Level 2: Identifies the daily established drop level value associated with Level 2
    // = 13% of Previous Close S&P 500 Value. Has implied 6 decimal places
    Decimal mwcb_level_2() const;
    void set_mwcb_level_2(Decimal value);

    // Mwcb Level 3: Identifies the daily established drop level value associated with Level 3
    // = 20% of Previous Close S&P 500 Value. Has implied 6 decimal places
    Decimal mwcb_level_3() const;
    void set_mwcb_level_3(Decimal value);

    // Reserved: Space-filled. Field is reserved for future use
    char reserved() const;
    void set_reserved(char value);

    // MarketStatusMessagePayload
    MarketStatusMessagePayloadCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(MarketStatusMessagePayloadVisitor& visitor) const override;
    std::unique_ptr<MarketStatusMessagePayload> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const MarketStatusMessagePayload& other) const override;

    bool operator==(const MarketWideCircuitBreakerDeclineLevelStatusMessage& other) const;
    bool operator!=(const MarketWideCircuitBreakerDeclineLevelStatusMessage& other) const;

  private:
    ParticipantId participant_id_{};
    Timestamp1 timestamp_1_{};
    std::uint8_t message_id_{};
    std::uint32_t transaction_id_{};
    std::int64_t participant_reference_number_{};
    Decimal mwcb_level_1_{ 0, -6 };
    Decimal mwcb_level_2_{ 0, -6 };
    Decimal mwcb_level_3_{ 0, -6 };
    char reserved_{};
};

} // namespace siac::cqs::output::cta::v2_10_a
