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

namespace siac::cts::output::cta::v2_10 {

class MarketStatusMessagePayloadVisitor;

// The Crossing Session message is used to report the total volume and dollar value of trades
// transacted after the close of a Participant’s regular session.
class CrossingSessionSummaryMessage : public MarketStatusMessagePayload {
  public:
    // The code that selects this message
    static constexpr MarketStatusMessagePayloadCode message_type = MarketStatusMessageType::CrossingSessionSummaryMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 46;

    CrossingSessionSummaryMessage() = default;
    CrossingSessionSummaryMessage(ParticipantId participant_id, const Timestamp1& timestamp_1, std::uint8_t message_id, std::uint32_t transaction_id, std::int64_t participant_reference_number, std::uint64_t crossing_session_i_total_trades_volume, Decimal crossing_session_ii_dollar_value, std::uint64_t crossing_session_ii_total_trades_volume);

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

    // Crossing Session I Total Trades Volume: Contains the number of shares traded at the
    // Participant’s close price and taking place after the close of a Participant’s regular
    // session.
    std::uint64_t crossing_session_i_total_trades_volume() const;
    void set_crossing_session_i_total_trades_volume(std::uint64_t value);

    // Crossing Session Ii Dollar Value: Contains the Dollar Value traded after the close of a
    // Participant’s regular session.
    Decimal crossing_session_ii_dollar_value() const;
    void set_crossing_session_ii_dollar_value(Decimal value);

    // Crossing Session Ii Total Trades Volume: Contains the number of shares traded after the
    // close of a Participant’s regular session.
    std::uint64_t crossing_session_ii_total_trades_volume() const;
    void set_crossing_session_ii_total_trades_volume(std::uint64_t value);

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

    bool operator==(const CrossingSessionSummaryMessage& other) const;
    bool operator!=(const CrossingSessionSummaryMessage& other) const;

  private:
    ParticipantId participant_id_{};
    Timestamp1 timestamp_1_{};
    std::uint8_t message_id_{};
    std::uint32_t transaction_id_{};
    std::int64_t participant_reference_number_{};
    std::uint64_t crossing_session_i_total_trades_volume_{};
    Decimal crossing_session_ii_dollar_value_{ 0, -6 };
    std::uint64_t crossing_session_ii_total_trades_volume_{};
};

} // namespace siac::cts::output::cta::v2_10
