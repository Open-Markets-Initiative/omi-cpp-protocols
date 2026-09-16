#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/CrossType.hpp"
#include "../messages/Message.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

class Visitor;

// Cross Trade message indicates that Nasdaq has completed its cross process for a specific
// security
class CrossTradeMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::CrossTradeMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 39;

    CrossTradeMessage() = default;
    CrossTradeMessage(std::uint16_t stock_locate, std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, std::uint64_t cross_shares, const std::string& stock, Decimal cross_price, std::uint64_t match_number, CrossType cross_type);

    // Stock Locate: Locate Code uniquely assigned to the security symbol for the day
    std::uint16_t stock_locate() const;
    void set_stock_locate(std::uint16_t value);

    // Tracking Number: Nasdaq internal tracking number
    std::uint16_t tracking_number() const;
    void set_tracking_number(std::uint16_t value);

    // Timestamp: Nanoseconds since midnight
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);

    // Cross Shares: The number of shares matched in the Nasdaq Cross
    std::uint64_t cross_shares() const;
    void set_cross_shares(std::uint64_t value);

    // Stock: Denotes the security symbol for the issue in the NASDAQ execution system.
    const std::string& stock() const;
    std::string& stock();
    void set_stock(const std::string& value);

    // Cross Price: The price at which the cross occurred
    Decimal cross_price() const;
    void set_cross_price(Decimal value);

    // Match Number: The Nasdaq generated day-unique Match Number of this execution
    std::uint64_t match_number() const;
    void set_match_number(std::uint64_t value);

    // Cross Type: The Nasdaq cross session for which the message is being generated
    CrossType cross_type() const;
    void set_cross_type(CrossType value);

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

    bool operator==(const CrossTradeMessage& other) const;
    bool operator!=(const CrossTradeMessage& other) const;

  private:
    std::uint16_t stock_locate_{};
    std::uint16_t tracking_number_{};
    std::chrono::nanoseconds timestamp_{};
    std::uint64_t cross_shares_{};
    std::string stock_{};
    Decimal cross_price_{ 0, -4 };
    std::uint64_t match_number_{};
    CrossType cross_type_{};
};

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
