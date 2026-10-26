#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../bitfields/OrderExecutionFlags.hpp"
#include "../common/Decimal.hpp"
#include "../messages/Data.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

class DataVisitor;

// This message format is used when a displayed order on the book executes in whole or in part.
// The execution is identified by a unique Trade ID that is unique across the exchange for the
// trading day. Subsequent partial executions of the order would be published with the same
// Order ID but different Trade ID.
class OrderExecutionMessage : public Data {
  public:
    // The code that selects this message
    static constexpr DataCode message_type = MessageType::OrderExecutionMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 37;

    OrderExecutionMessage() = default;
    OrderExecutionMessage(std::chrono::nanoseconds nanoseconds, std::uint32_t symbol_id, std::uint64_t order_id, std::uint64_t trade_id, Decimal price, std::uint32_t size, const OrderExecutionFlags& order_execution_flags);

    // Nanoseconds: Nanosecond part of Matching Engine time.
    std::chrono::nanoseconds nanoseconds() const;
    void set_nanoseconds(std::chrono::nanoseconds value);

    // Symbol Id: Symbol ID mapped to a given symbol. It is assigned per trading session and is
    // valid for that session.
    std::uint32_t symbol_id() const;
    void set_symbol_id(std::uint32_t value);

    // Order Id: Matching engine assigned Order ID.
    std::uint64_t order_id() const;
    void set_order_id(std::uint64_t value);

    // Trade Id: Unique ID assigned by the Matching Engine.
    std::uint64_t trade_id() const;
    void set_trade_id(std::uint64_t value);

    // Price: Displayed price.
    Decimal price() const;
    void set_price(Decimal value);

    // Size: Number of displayed shares of the order.
    std::uint32_t size() const;
    void set_size(std::uint32_t value);

    // Order Execution Flags: Order Execution flags. Bit 0 indicates SIP reportability; bit 1
    // indicates Traded Against Retail; bits 2-7 are reserved.
    const OrderExecutionFlags& order_execution_flags() const;
    OrderExecutionFlags& order_execution_flags();
    void set_order_execution_flags(const OrderExecutionFlags& value);

    // Data
    DataCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(DataVisitor& visitor) const override;
    std::unique_ptr<Data> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const Data& other) const override;

    bool operator==(const OrderExecutionMessage& other) const;
    bool operator!=(const OrderExecutionMessage& other) const;

  private:
    std::chrono::nanoseconds nanoseconds_{};
    std::uint32_t symbol_id_{};
    std::uint64_t order_id_{};
    std::uint64_t trade_id_{};
    Decimal price_{ 0, -6 };
    std::uint32_t size_{};
    OrderExecutionFlags order_execution_flags_{};
};

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
