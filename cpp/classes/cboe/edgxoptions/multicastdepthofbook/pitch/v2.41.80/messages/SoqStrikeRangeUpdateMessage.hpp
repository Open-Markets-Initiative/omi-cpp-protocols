#pragma once

#include <chrono>
#include <cstddef>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../messages/Message.hpp"

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {

class Visitor;

// C1 Only. The SOQ Strike Range Update message is only available on the C1 Exchange. This
// message disseminates the minimum and maximum strike prices of the strike price range used to
// calculate the Special Opening Quote (SOQ) on a Volatility Settlement date. In the event that
// multiple distinct SOQ calculations occur on the same day, the applicable SOQ is
// differentiated by the SOQ Identifier field, which is set to the CSMi symbol on which the
// final settlement SOQ value is disseminated.
class SoqStrikeRangeUpdateMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::SoqStrikeRangeUpdateMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 40;

    SoqStrikeRangeUpdateMessage() = default;
    SoqStrikeRangeUpdateMessage(std::chrono::nanoseconds time_offset, const std::string& soq_identifier, Decimal lower_strike_price, Decimal upper_strike_price);

    // Time Offset: Nanosecond offset from last unit timestamp.
    std::chrono::nanoseconds time_offset() const;
    void set_time_offset(std::chrono::nanoseconds value);

    // Soq Identifier: Dissemination symbol of the final SOQ right padded with spaces.
    const std::string& soq_identifier() const;
    std::string& soq_identifier();
    void set_soq_identifier(const std::string& value);

    // Lower Strike Price: SOQ lower strike price.
    Decimal lower_strike_price() const;
    void set_lower_strike_price(Decimal value);

    // Upper Strike Price: SOQ upper strike price.
    Decimal upper_strike_price() const;
    void set_upper_strike_price(Decimal value);

    // Message
    MessageCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(Visitor& visitor) const override;
    std::unique_ptr<Message> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const Message& other) const override;

    bool operator==(const SoqStrikeRangeUpdateMessage& other) const;
    bool operator!=(const SoqStrikeRangeUpdateMessage& other) const;

  private:
    std::chrono::nanoseconds time_offset_{};
    std::string soq_identifier_{};
    Decimal lower_strike_price_{ 0, -4 };
    Decimal upper_strike_price_{ 0, -4 };
};

} // namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80
