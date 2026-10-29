#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/BuySellIndicator.hpp"
#include "../enums/Group.hpp"
#include "../enums/OrderType.hpp"
#include "../messages/PacketMessage.hpp"

namespace jnx::jnxequities::pts::itch::v1_7 {

class PacketMessageVisitor;

// Order Added with Attributes Message will be generated for orders with market specific
// attributes accepted by the system.
class UdpPayloadOrderAddedWithAttributesMessage : public PacketMessage {
  public:
    // The code that selects this message
    static constexpr PacketMessageCode message_type = MessageType::OrderAddedWithAttributesMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 34;

    UdpPayloadOrderAddedWithAttributesMessage() = default;
    UdpPayloadOrderAddedWithAttributesMessage(std::chrono::nanoseconds nanoseconds, std::uint64_t order_number, BuySellIndicator buy_sell_indicator, std::uint32_t quantity, std::uint32_t orderbook_id, const std::string& group, Decimal price, const std::string& attribution, OrderType order_type);

    // Nanoseconds: Number of nanoseconds since last Timestamp Seconds Message.
    std::chrono::nanoseconds nanoseconds() const;
    void set_nanoseconds(std::chrono::nanoseconds value);

    // Order Number: Reference number of the accepted order; zero indicates a reference price
    // message.
    std::uint64_t order_number() const;
    void set_order_number(std::uint64_t value);

    // Buy Sell Indicator: Side of the order.
    BuySellIndicator buy_sell_indicator() const;
    void set_buy_sell_indicator(BuySellIndicator value);

    // Quantity: Total number of shares added to the book.
    std::uint32_t quantity() const;
    void set_quantity(std::uint32_t value);

    // Orderbook Id: 4 digit Quick code.
    std::uint32_t orderbook_id() const;
    void set_orderbook_id(std::uint32_t value);

    // Group: Orderbook group identifier.
    const std::string& group() const;
    std::string& group();
    void set_group(const std::string& value);

    // Price: Price of the order; for a reference price message, a value of 214,748,364.7
    // (7FFFFFFF hex) denotes no reference price available.
    Decimal price() const;
    void set_price(Decimal value);

    // Attribution: Reserved; always blank.
    const std::string& attribution() const;
    std::string& attribution();
    void set_attribution(const std::string& value);

    // Order Type: Type of the order.
    OrderType order_type() const;
    void set_order_type(OrderType value);

    // PacketMessage
    PacketMessageCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(PacketMessageVisitor& visitor) const override;
    std::unique_ptr<PacketMessage> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const PacketMessage& other) const override;

    bool operator==(const UdpPayloadOrderAddedWithAttributesMessage& other) const;
    bool operator!=(const UdpPayloadOrderAddedWithAttributesMessage& other) const;

  private:
    std::chrono::nanoseconds nanoseconds_{};
    std::uint64_t order_number_{};
    BuySellIndicator buy_sell_indicator_{};
    std::uint32_t quantity_{};
    std::uint32_t orderbook_id_{};
    std::string group_{};
    Decimal price_{ 0, -1 };
    std::string attribution_{};
    OrderType order_type_{};
};

} // namespace jnx::jnxequities::pts::itch::v1_7
