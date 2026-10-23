#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../messages/Message.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

class Visitor;

// Used to disseminate top of book changes when the instrument is in a scheduled level 1 only
// auction.
class TopOfBookMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::TopOfBookMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 32;

    TopOfBookMessage() = default;
    TopOfBookMessage(std::uint32_t nanosecond, std::uint32_t instrument_id, std::int64_t buy_limit_price, std::uint32_t buy_limit_size, std::int64_t sell_limit_price, std::uint32_t sell_limit_size);

    // Nanosecond: Nanoseconds since last message, accurate to the nearest microsecond.
    std::uint32_t nanosecond() const;
    void set_nanosecond(std::uint32_t value);

    // Instrument Id: Instrument's symbol.
    std::uint32_t instrument_id() const;
    void set_instrument_id(std::uint32_t value);

    // Buy Limit Price: Best bid price. Will contain zero if there are no visible limit orders
    // on the buy side
    std::int64_t buy_limit_price() const;
    void set_buy_limit_price(std::int64_t value);

    // Buy Limit Size: Cumulative visible size at best bid price. Will contain zero if there
    // are no visible limit orders on the buy side
    std::uint32_t buy_limit_size() const;
    void set_buy_limit_size(std::uint32_t value);

    // Sell Limit Price: Best offer price. Will contain zero if there are no visible limit
    // orders on the sell side
    std::int64_t sell_limit_price() const;
    void set_sell_limit_price(std::int64_t value);

    // Sell Limit Size: Cumulative visible size at best offer price. Will contain zero if there
    // are no visible limit orders on the sell side
    std::uint32_t sell_limit_size() const;
    void set_sell_limit_size(std::uint32_t value);

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

    bool operator==(const TopOfBookMessage& other) const;
    bool operator!=(const TopOfBookMessage& other) const;

  private:
    std::uint32_t nanosecond_{};
    std::uint32_t instrument_id_{};
    std::int64_t buy_limit_price_{};
    std::uint32_t buy_limit_size_{};
    std::int64_t sell_limit_price_{};
    std::uint32_t sell_limit_size_{};
};

} // namespace lseg::millennium::level2::mitch::v11_9
