#pragma once

#include <chrono>
#include <cstddef>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../enums/RetailPriceImprovement.hpp"
#include "../messages/Message.hpp"

namespace cboe::byxequities::multicastdepthofbook::pitch::v2_41_29 {

class Visitor;

// This message is a Retail Liquidity Indicator (RLI) that includes symbol and side, but not
// price and size
class RetailPriceImprovementMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::RetailPriceImprovementMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 13;

    RetailPriceImprovementMessage() = default;
    RetailPriceImprovementMessage(std::chrono::nanoseconds time_offset, const std::string& symbol_long, RetailPriceImprovement retail_price_improvement);

    // Time Offset: Nanosecond offset from last unit timestamp
    std::chrono::nanoseconds time_offset() const;
    void set_time_offset(std::chrono::nanoseconds value);

    // Symbol Long: Symbol
    const std::string& symbol_long() const;
    std::string& symbol_long();
    void set_symbol_long(const std::string& value);

    // Retail Price Improvement: Retail Price Improvement
    RetailPriceImprovement retail_price_improvement() const;
    void set_retail_price_improvement(RetailPriceImprovement value);

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

    bool operator==(const RetailPriceImprovementMessage& other) const;
    bool operator!=(const RetailPriceImprovementMessage& other) const;

  private:
    std::chrono::nanoseconds time_offset_{};
    std::string symbol_long_{};
    RetailPriceImprovement retail_price_improvement_{};
};

} // namespace cboe::byxequities::multicastdepthofbook::pitch::v2_41_29
