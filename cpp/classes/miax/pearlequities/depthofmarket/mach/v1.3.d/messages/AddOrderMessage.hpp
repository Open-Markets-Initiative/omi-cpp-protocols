#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/OrderSide.hpp"
#include "../messages/Data.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

class DataVisitor;

// This is the message format that will be used when a displayed order is received and added to
// MIAX Pearl Equities book. It includes an Order ID that is unique to the order across the
// exchange and across trading days.
class AddOrderMessage : public Data {
  public:
    // The code that selects this message
    static constexpr DataCode message_type = MessageType::AddOrderMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 33;

    AddOrderMessage() = default;
    AddOrderMessage(std::chrono::nanoseconds nanoseconds, std::uint32_t symbol_id, std::uint64_t order_id, OrderSide order_side, Decimal price, std::uint32_t size, const std::string& attributable_id);

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

    // Order Side: Side of order. B - Buy, S - Sell.
    OrderSide order_side() const;
    void set_order_side(OrderSide value);

    // Price: Displayed price.
    Decimal price() const;
    void set_price(Decimal value);

    // Size: Number of displayed shares of the order.
    std::uint32_t size() const;
    void set_size(std::uint32_t value);

    // Attributable Id: MPID of the firm if attributed; "RTAL" if attributed as such;
    // space-filled if no attribution specified.
    const std::string& attributable_id() const;
    std::string& attributable_id();
    void set_attributable_id(const std::string& value);

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

    bool operator==(const AddOrderMessage& other) const;
    bool operator!=(const AddOrderMessage& other) const;

  private:
    std::chrono::nanoseconds nanoseconds_{};
    std::uint32_t symbol_id_{};
    std::uint64_t order_id_{};
    OrderSide order_side_{};
    Decimal price_{ 0, -6 };
    std::uint32_t size_{};
    std::string attributable_id_{};
};

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
