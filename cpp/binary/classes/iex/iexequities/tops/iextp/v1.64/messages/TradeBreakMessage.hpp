#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../bitfields/SaleConditionFlags.hpp"
#include "../common/Decimal.hpp"
#include "../messages/Message.hpp"

namespace iex::iexequities::tops::iextp::v1_64 {

class Visitor;

// Trade Break Messages are sent when an execution on IEX is broken on that same trading day
class TradeBreakMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::TradeBreakMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 37;

    TradeBreakMessage() = default;
    TradeBreakMessage(const SaleConditionFlags& sale_condition_flags, std::chrono::nanoseconds timestamp, const std::string& symbol, std::uint32_t size, Decimal price, std::uint64_t trade_id);

    // Sale Condition Flags: Sale Condition Flags
    const SaleConditionFlags& sale_condition_flags() const;
    SaleConditionFlags& sale_condition_flags();
    void set_sale_condition_flags(const SaleConditionFlags& value);

    // Timestamp: Time stamp of the system event
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);

    // Symbol: Security identifier
    const std::string& symbol() const;
    std::string& symbol();
    void set_symbol(const std::string& value);

    // Size: Trade volume
    std::uint32_t size() const;
    void set_size(std::uint32_t value);

    // Price: Trade price
    Decimal price() const;
    void set_price(Decimal value);

    // Trade Id: IEX Generated Identifier. Trade ID is also
    std::uint64_t trade_id() const;
    void set_trade_id(std::uint64_t value);

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

    bool operator==(const TradeBreakMessage& other) const;
    bool operator!=(const TradeBreakMessage& other) const;

  private:
    SaleConditionFlags sale_condition_flags_{};
    std::chrono::nanoseconds timestamp_{};
    std::string symbol_{};
    std::uint32_t size_{};
    Decimal price_{ 0, -4 };
    std::uint64_t trade_id_{};
};

} // namespace iex::iexequities::tops::iextp::v1_64
