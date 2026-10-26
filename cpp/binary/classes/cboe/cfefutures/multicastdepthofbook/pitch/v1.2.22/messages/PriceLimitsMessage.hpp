#pragma once

#include <chrono>
#include <cstddef>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../messages/Message.hpp"

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

class Visitor;

// The Price Limits message is sent out at the start of a session for products subject to price
// limits per the contract specifications.
class PriceLimitsMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::PriceLimitsMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 26;

    PriceLimitsMessage() = default;
    PriceLimitsMessage(std::chrono::nanoseconds time_offset, const std::string& symbol, Decimal upper_price_limit, Decimal lower_price_limit);

    // Time Offset: Nanosecond offset from last unit timestamp.
    std::chrono::nanoseconds time_offset() const;
    void set_time_offset(std::chrono::nanoseconds value);

    // Symbol: Six character, base 62 symbol.
    const std::string& symbol() const;
    std::string& symbol();
    void set_symbol(const std::string& value);

    // Upper Price Limit: Upper price limit
    Decimal upper_price_limit() const;
    void set_upper_price_limit(Decimal value);

    // Lower Price Limit: Lower price limit
    Decimal lower_price_limit() const;
    void set_lower_price_limit(Decimal value);

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

    bool operator==(const PriceLimitsMessage& other) const;
    bool operator!=(const PriceLimitsMessage& other) const;

  private:
    std::chrono::nanoseconds time_offset_{};
    std::string symbol_{};
    Decimal upper_price_limit_{ 0, -4 };
    Decimal lower_price_limit_{ 0, -4 };
};

} // namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22
