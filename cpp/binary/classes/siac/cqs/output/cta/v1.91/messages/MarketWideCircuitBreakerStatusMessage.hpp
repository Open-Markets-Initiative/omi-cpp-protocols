#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../enums/MarketWideCircuitBreakerLevelIndicator.hpp"
#include "../enums/ParticipantId.hpp"
#include "../messages/MarketStatusMessagePayload.hpp"
#include "../structs/ParticipantTimestamp.hpp"

namespace siac::cqs::output::cta::v1_91 {

class MarketStatusMessagePayloadVisitor;

// The Market-Wide Circuit Breaker Status message is used to report the Market-Wide Circuit
// Breaker threshold Level that has been breached.
class MarketWideCircuitBreakerStatusMessage : public MarketStatusMessagePayload {
  public:
    // The code that selects this message
    static constexpr MarketStatusMessagePayloadCode message_type = MarketStatusMessageType::MarketWideCircuitBreakerStatusMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 24;

    MarketWideCircuitBreakerStatusMessage() = default;
    MarketWideCircuitBreakerStatusMessage(ParticipantId participant_id, const ParticipantTimestamp& participant_timestamp, std::uint8_t message_id, std::uint32_t transaction_id, std::int64_t participant_reference_number, MarketWideCircuitBreakerLevelIndicator market_wide_circuit_breaker_level_indicator, std::uint8_t reserved);

    // Participant Id: Participant or Processor that generated the message
    ParticipantId participant_id() const;
    void set_participant_id(ParticipantId value);

    // Participant Timestamp: Participant Timestamp
    const ParticipantTimestamp& participant_timestamp() const;
    ParticipantTimestamp& participant_timestamp();
    void set_participant_timestamp(const ParticipantTimestamp& value);

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

    // Market Wide Circuit Breaker Level Indicator: Identifies the threshold level that was
    // breached
    MarketWideCircuitBreakerLevelIndicator market_wide_circuit_breaker_level_indicator() const;
    void set_market_wide_circuit_breaker_level_indicator(MarketWideCircuitBreakerLevelIndicator value);

    // Reserved: Field is reserved for future use.
    std::uint8_t reserved() const;
    void set_reserved(std::uint8_t value);

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

    bool operator==(const MarketWideCircuitBreakerStatusMessage& other) const;
    bool operator!=(const MarketWideCircuitBreakerStatusMessage& other) const;

  private:
    ParticipantId participant_id_{};
    ParticipantTimestamp participant_timestamp_{};
    std::uint8_t message_id_{};
    std::uint32_t transaction_id_{};
    std::int64_t participant_reference_number_{};
    MarketWideCircuitBreakerLevelIndicator market_wide_circuit_breaker_level_indicator_{};
    std::uint8_t reserved_{};
};

} // namespace siac::cqs::output::cta::v1_91
