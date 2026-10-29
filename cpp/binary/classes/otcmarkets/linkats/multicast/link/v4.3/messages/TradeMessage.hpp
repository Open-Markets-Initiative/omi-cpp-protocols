#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../bitfields/TradeStatus.hpp"
#include "../common/Decimal.hpp"
#include "../enums/TradeAction.hpp"
#include "../messages/Message.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

class Visitor;

// A Trade Message is created for every trade that occurs on OTC Markets OTC Link ATS.
class TradeMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::TradeMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 43;

    TradeMessage() = default;
    TradeMessage(std::uint32_t channel_seq_num, std::uint32_t trade_id, TradeAction trade_action, std::uint8_t trade_flags, std::uint32_t security_id, const TradeStatus& trade_status, const std::string& deprecated, Decimal trade_price, std::uint32_t trade_size, std::uint64_t trade_time_milli);

    // Channel Seq Num: Monotonically increasing message sequence number at the channel level.
    std::uint32_t channel_seq_num() const;
    void set_channel_seq_num(std::uint32_t value);

    // Trade Id: Unique Trade ID.
    std::uint32_t trade_id() const;
    void set_trade_id(std::uint32_t value);

    // Trade Action: Trade action indicator.
    TradeAction trade_action() const;
    void set_trade_action(TradeAction value);

    // Trade Flags: Trade flags bitmap.
    std::uint8_t trade_flags() const;
    void set_trade_flags(std::uint8_t value);

    // Security Id: Unique security ID issued by OTC Markets.
    std::uint32_t security_id() const;
    void set_security_id(std::uint32_t value);

    // Trade Status: Trade Status Information
    const TradeStatus& trade_status() const;
    TradeStatus& trade_status();
    void set_trade_status(const TradeStatus& value);

    // Deprecated: Deprecated field. Spaces will be sent in the message.
    const std::string& deprecated() const;
    std::string& deprecated();
    void set_deprecated(const std::string& value);

    // Trade Price: Trade price with 6 decimal places assumed.
    Decimal trade_price() const;
    void set_trade_price(Decimal value);

    // Trade Size: Number of shares traded.
    std::uint32_t trade_size() const;
    void set_trade_size(std::uint32_t value);

    // Trade Time Milli: Trade timestamp in milliseconds from UTC epoch.
    std::uint64_t trade_time_milli() const;
    void set_trade_time_milli(std::uint64_t value);

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

    bool operator==(const TradeMessage& other) const;
    bool operator!=(const TradeMessage& other) const;

  private:
    std::uint32_t channel_seq_num_{};
    std::uint32_t trade_id_{};
    TradeAction trade_action_{};
    std::uint8_t trade_flags_{};
    std::uint32_t security_id_{};
    TradeStatus trade_status_{};
    std::string deprecated_{};
    Decimal trade_price_{ 0, -6 };
    std::uint32_t trade_size_{};
    std::uint64_t trade_time_milli_{};
};

} // namespace otcmarkets::linkats::multicast::link::v4_3
