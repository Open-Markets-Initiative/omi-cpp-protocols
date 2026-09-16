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
#include "../messages/Message.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

class Visitor;

// This message will be generated for attributed orders and quotations accepted by the Nasdaq
// system
class AddOrderWithMpidAttributionMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::AddOrderWithMpidAttributionMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 39;

    AddOrderWithMpidAttributionMessage() = default;
    AddOrderWithMpidAttributionMessage(std::uint16_t stock_locate, std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, std::uint64_t order_reference_number, BuySellIndicator buy_sell_indicator, std::uint32_t shares, const std::string& stock, Decimal price, const std::string& attribution);

    // Stock Locate: Locate Code uniquely assigned to the security symbol for the day
    std::uint16_t stock_locate() const;
    void set_stock_locate(std::uint16_t value);

    // Tracking Number: Nasdaq internal tracking number
    std::uint16_t tracking_number() const;
    void set_tracking_number(std::uint16_t value);

    // Timestamp: Nanoseconds since midnight
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);

    // Order Reference Number: The unique reference number assigned to the new order at the
    // time of receipt
    std::uint64_t order_reference_number() const;
    void set_order_reference_number(std::uint64_t value);

    // Buy Sell Indicator: The type of order being added
    BuySellIndicator buy_sell_indicator() const;
    void set_buy_sell_indicator(BuySellIndicator value);

    // Shares: The total number of shares associated with the order being added to the book
    std::uint32_t shares() const;
    void set_shares(std::uint32_t value);

    // Stock: Denotes the security symbol for the issue in the NASDAQ execution system.
    const std::string& stock() const;
    std::string& stock();
    void set_stock(const std::string& value);

    // Price: The display price of the new order
    Decimal price() const;
    void set_price(Decimal value);

    // Attribution: Nasdaq market participant identifier associated with the entered order
    const std::string& attribution() const;
    std::string& attribution();
    void set_attribution(const std::string& value);

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

    bool operator==(const AddOrderWithMpidAttributionMessage& other) const;
    bool operator!=(const AddOrderWithMpidAttributionMessage& other) const;

  private:
    std::uint16_t stock_locate_{};
    std::uint16_t tracking_number_{};
    std::chrono::nanoseconds timestamp_{};
    std::uint64_t order_reference_number_{};
    BuySellIndicator buy_sell_indicator_{};
    std::uint32_t shares_{};
    std::string stock_{};
    Decimal price_{ 0, -4 };
    std::string attribution_{};
};

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
