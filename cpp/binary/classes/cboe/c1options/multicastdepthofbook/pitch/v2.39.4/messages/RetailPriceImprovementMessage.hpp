#pragma once

#include <chrono>
#include <cstddef>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../enums/RetailPriceImprovement.hpp"
#include "../messages/Message.hpp"

namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4 {

class Visitor;

// The Retail Price Improvement message is only available on the BYX Exchange.
class RetailPriceImprovementMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::RetailPriceImprovementMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 13;

    RetailPriceImprovementMessage() = default;
    RetailPriceImprovementMessage(std::chrono::nanoseconds time_offset, const std::string& expanded_symbol, RetailPriceImprovement retail_price_improvement);

    // Time Offset: Nanosecond offset from last unit timestamp
    std::chrono::nanoseconds time_offset() const;
    void set_time_offset(std::chrono::nanoseconds value);

    // Expanded Symbol: Symbol right padded with spaces.
    const std::string& expanded_symbol() const;
    std::string& expanded_symbol();
    void set_expanded_symbol(const std::string& value);

    // Retail Price Improvement: Retail price improvement value
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
    std::string expanded_symbol_{};
    RetailPriceImprovement retail_price_improvement_{};
};

} // namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4
