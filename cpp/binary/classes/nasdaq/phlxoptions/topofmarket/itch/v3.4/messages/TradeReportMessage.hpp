#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../messages/SequencedMessage.hpp"

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {

class SequencedMessageVisitor;

// The Trade Report message will be used to relay execution system transactions that are
// reported during the current business day. The options system only reports one-side of a
// trade execution on the feed and other data feed products.
class TradeReportMessage : public SequencedMessage {
  public:
    // The code that selects this message
    static constexpr SequencedMessageCode message_type = SequencedMessageType::TradeReportMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 21;

    TradeReportMessage() = default;
    TradeReportMessage(std::chrono::nanoseconds nanoseconds, std::uint32_t option_id, std::uint32_t cross_id, char trade_condition, Decimal price_4, std::uint32_t volume);

    // Nanoseconds: The sub-second portion of the time, in nanoseconds (0-999999999). The
    // second portion of the time is obtained from the most recent timestamp message.
    std::chrono::nanoseconds nanoseconds() const;
    void set_nanoseconds(std::chrono::nanoseconds value);

    // Option Id: Option ID for this option, assigned daily, valid for trading day.
    std::uint32_t option_id() const;
    void set_option_id(std::uint32_t value);

    // Cross Id: Indicates the internal control number (cross id) associated with the given
    // option trade transaction.
    std::uint32_t cross_id() const;
    void set_cross_id(std::uint32_t value);

    // Trade Condition: To obtain a list of Trade Conditions, refer to the NOTE below.
    char trade_condition() const;
    void set_trade_condition(char value);

    // Price 4: Best bid or ask price, the side determined by the Message Type.
    Decimal price_4() const;
    void set_price_4(Decimal value);

    // Volume: Reflects the number of contracts traded for an option in one trade.
    std::uint32_t volume() const;
    void set_volume(std::uint32_t value);

    // SequencedMessage
    SequencedMessageCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(SequencedMessageVisitor& visitor) const override;
    std::unique_ptr<SequencedMessage> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const SequencedMessage& other) const override;

    bool operator==(const TradeReportMessage& other) const;
    bool operator!=(const TradeReportMessage& other) const;

  private:
    std::chrono::nanoseconds nanoseconds_{};
    std::uint32_t option_id_{};
    std::uint32_t cross_id_{};
    char trade_condition_{};
    Decimal price_4_{ 0, -4 };
    std::uint32_t volume_{};
};

} // namespace nasdaq::phlxoptions::topofmarket::itch::v3_4
