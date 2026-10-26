#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/Side.hpp"
#include "../enums/TradeType.hpp"
#include "../messages/Message.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

class Visitor;

// This message is sent when orders are executed in the auction at the open of the market
class AuctionOrderExecutedMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::AuctionOrderExecutedMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 52;

    AuctionOrderExecutedMessage() = default;
    AuctionOrderExecutedMessage(std::chrono::nanoseconds nanoseconds, std::uint16_t trade_date, std::uint32_t tradeable_instrument_id, Side side, std::uint64_t order_id, std::uint32_t quantity_remaining, TradeType trade_type, std::uint64_t trade_id, std::uint32_t executed_quantity, Decimal trade_price, std::uint64_t opposite_order_id);

    // Nanoseconds: Nanoseconds portion of the Nanoseconds, accurate to 1,000 nanoseconds.
    std::chrono::nanoseconds nanoseconds() const;
    void set_nanoseconds(std::chrono::nanoseconds value);

    // Trade Date: Trade Date. Represented as number of days since 1 January 1970.
    std::uint16_t trade_date() const;
    void set_trade_date(std::uint16_t value);

    // Tradeable Instrument Id: Identifier of the Order Book.
    std::uint32_t tradeable_instrument_id() const;
    void set_tradeable_instrument_id(std::uint32_t value);

    // Side: Type of order
    Side side() const;
    void set_side(Side value);

    // Order Id: Public order id of the order.
    std::uint64_t order_id() const;
    void set_order_id(std::uint64_t value);

    // Quantity Remaining: Volume remaining on Order after matching, if 0, order has traded out
    // and should be deleted.
    std::uint32_t quantity_remaining() const;
    void set_quantity_remaining(std::uint32_t value);

    // Trade Type: Nature of the match
    TradeType trade_type() const;
    void set_trade_type(TradeType value);

    // Trade Id: Public trade id of the trade.
    std::uint64_t trade_id() const;
    void set_trade_id(std::uint64_t value);

    // Executed Quantity: Volume traded.
    std::uint32_t executed_quantity() const;
    void set_executed_quantity(std::uint32_t value);

    // Trade Price: Price of trade (may be negative for combination trades).
    Decimal trade_price() const;
    void set_trade_price(Decimal value);

    // Opposite Order Id: Public Order Id of the order to be removed from the opposite side of
    // the same Order Book id, as order has traded out.
    std::uint64_t opposite_order_id() const;
    void set_opposite_order_id(std::uint64_t value);

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

    bool operator==(const AuctionOrderExecutedMessage& other) const;
    bool operator!=(const AuctionOrderExecutedMessage& other) const;

  private:
    std::chrono::nanoseconds nanoseconds_{};
    std::uint16_t trade_date_{};
    std::uint32_t tradeable_instrument_id_{};
    Side side_{};
    std::uint64_t order_id_{};
    std::uint32_t quantity_remaining_{};
    TradeType trade_type_{};
    std::uint64_t trade_id_{};
    std::uint32_t executed_quantity_{};
    Decimal trade_price_{ 0, -2 };
    std::uint64_t opposite_order_id_{};
};

} // namespace asx::asxderivatives::ntp::itch::v1_05
