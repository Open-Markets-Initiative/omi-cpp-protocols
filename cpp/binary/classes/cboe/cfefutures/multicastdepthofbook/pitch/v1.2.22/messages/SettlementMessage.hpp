#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/Issue.hpp"
#include "../messages/Message.hpp"

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

class Visitor;

// Settlement messages are used to provide information concerning indicative, approved, or
// corrected daily and final settlement prices for CFE products.
class SettlementMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::SettlementMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 23;

    SettlementMessage() = default;
    SettlementMessage(std::chrono::nanoseconds time_offset, const std::string& symbol, std::uint32_t trade_date, Decimal settlement_price, Issue issue);

    // Time Offset: Nanosecond offset from last unit timestamp.
    std::chrono::nanoseconds time_offset() const;
    void set_time_offset(std::chrono::nanoseconds value);

    // Symbol: Six character, base 62 symbol.
    const std::string& symbol() const;
    std::string& symbol();
    void set_symbol(const std::string& value);

    // Trade Date: Current Trade Date
    std::uint32_t trade_date() const;
    void set_trade_date(std::uint32_t value);

    // Settlement Price: Settlement Price
    Decimal settlement_price() const;
    void set_settlement_price(Decimal value);

    // Issue: Issue Values
    Issue issue() const;
    void set_issue(Issue value);

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

    bool operator==(const SettlementMessage& other) const;
    bool operator!=(const SettlementMessage& other) const;

  private:
    std::chrono::nanoseconds time_offset_{};
    std::string symbol_{};
    std::uint32_t trade_date_{};
    Decimal settlement_price_{ 0, -4 };
    Issue issue_{};
};

} // namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22
