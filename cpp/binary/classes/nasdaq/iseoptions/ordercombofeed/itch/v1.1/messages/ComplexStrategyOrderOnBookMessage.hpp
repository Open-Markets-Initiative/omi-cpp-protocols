#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../common/Day.hpp"
#include "../common/Decimal.hpp"
#include "../enums/ExecFlag.hpp"
#include "../enums/OrderCapacity.hpp"
#include "../enums/OrderType.hpp"
#include "../enums/Scope.hpp"
#include "../enums/Side.hpp"
#include "../messages/Message.hpp"

namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1 {

class Visitor;

// An Order on Book message is generated for all the following situations whenever an order
// free from any display restrictions is reported by the matching engine. In all such cases the
// order size to be displayed is as reported by the matching engine
class ComplexStrategyOrderOnBookMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::ComplexStrategyOrderOnBookMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 41;

    ComplexStrategyOrderOnBookMessage() = default;
    ComplexStrategyOrderOnBookMessage(std::chrono::nanoseconds timestamp, std::uint32_t strategy_id, OrderType order_type, Side side, Decimal price, std::uint32_t size, ExecFlag exec_flag, OrderCapacity order_capacity, Scope scope, const std::string& owner_id, const std::string& giveup, const std::string& cmta);

    // Timestamp: The time, expressed as the number of nanoseconds after midnight.
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);
    std::int64_t timestamp_utc(const calendar::Day& day) const;

    // Strategy Id: ISE’s Strategy ID assigned daily, valid while there are any open complex
    // orders for the day
    std::uint32_t strategy_id() const;
    void set_strategy_id(std::uint32_t value);

    // Order Type: Order Type
    OrderType order_type() const;
    void set_order_type(OrderType value);

    // Side: ‘B’ = Bid ‘A’ = Offer (Ask) ‘ ’ (blank) = not set (hidden)
    Side side() const;
    void set_side(Side value);

    // Price: Price of the order in fixed point format with 6 whole number places followed by 4
    // decimal digits.
    Decimal price() const;
    void set_price(Decimal value);

    // Size: Size of the order
    std::uint32_t size() const;
    void set_size(std::uint32_t value);

    // Exec Flag: ‘N’ = None ‘A’ = AON
    ExecFlag exec_flag() const;
    void set_exec_flag(ExecFlag value);

    // Order Capacity: Order Capacity value
    OrderCapacity order_capacity() const;
    void set_order_capacity(OrderCapacity value);

    // Scope: Scope value
    Scope scope() const;
    void set_scope(Scope value);

    // Owner Id: Spaces when not set
    const std::string& owner_id() const;
    std::string& owner_id();
    void set_owner_id(const std::string& value);

    // Giveup: Spaces when not set
    const std::string& giveup() const;
    std::string& giveup();
    void set_giveup(const std::string& value);

    // Cmta: Spaces when not set
    const std::string& cmta() const;
    std::string& cmta();
    void set_cmta(const std::string& value);

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

    bool operator==(const ComplexStrategyOrderOnBookMessage& other) const;
    bool operator!=(const ComplexStrategyOrderOnBookMessage& other) const;

  private:
    std::chrono::nanoseconds timestamp_{};
    std::uint32_t strategy_id_{};
    OrderType order_type_{};
    Side side_{};
    Decimal price_{ 0, -4 };
    std::uint32_t size_{};
    ExecFlag exec_flag_{};
    OrderCapacity order_capacity_{};
    Scope scope_{};
    std::string owner_id_{};
    std::string giveup_{};
    std::string cmta_{};
};

} // namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1
