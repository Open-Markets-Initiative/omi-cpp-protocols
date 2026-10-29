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

namespace siac::cts::output::cta::v1_91 {

class MarketStatusMessagePayloadVisitor;

// The Approximate Trades and Total Dollar Value message allows a Participant to report the
// total trades and total dollar value of trades at their respective market centers.
class ApproximateTradesAndTotalDollarValueMessage : public MarketStatusMessagePayload {
  public:
    // The code that selects this message
    static constexpr MarketStatusMessagePayloadCode message_type = MarketStatusMessageType::ApproximateTradesAndTotalDollarValueMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 34;

    ApproximateTradesAndTotalDollarValueMessage() = default;
    ApproximateTradesAndTotalDollarValueMessage(ParticipantId participant_id, const Timestamp1& timestamp_1, std::uint8_t message_id, std::uint32_t transaction_id, std::int64_t participant_reference_number, std::uint32_t total_trades, Decimal dollar_value);

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

    // Total Trades: Contains the total number of trade transactions executed from a Market
    // Center
    std::uint32_t total_trades() const;
    void set_total_trades(std::uint32_t value);

    // Dollar Value: The Dollar Value represents the total dollar worth of the daily trade
    // transactions.
    Decimal dollar_value() const;
    void set_dollar_value(Decimal value);

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

    bool operator==(const ApproximateTradesAndTotalDollarValueMessage& other) const;
    bool operator!=(const ApproximateTradesAndTotalDollarValueMessage& other) const;

  private:
    ParticipantId participant_id_{};
    Timestamp1 timestamp_1_{};
    std::uint8_t message_id_{};
    std::uint32_t transaction_id_{};
    std::int64_t participant_reference_number_{};
    std::uint32_t total_trades_{};
    Decimal dollar_value_{ 0, -6 };
};

} // namespace siac::cts::output::cta::v1_91
