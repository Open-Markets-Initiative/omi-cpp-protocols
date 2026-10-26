#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../bitfields/ModifyOrderFlags.hpp"
#include "../common/Decimal.hpp"
#include "../messages/Data.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

class DataVisitor;

// This message format is used to publish price/size changes for an existing displayed order on
// MIAX Pearl Equities book.
class ModifyOrderMessage : public Data {
  public:
    // The code that selects this message
    static constexpr DataCode message_type = MessageType::ModifyOrderMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 29;

    ModifyOrderMessage() = default;
    ModifyOrderMessage(std::chrono::nanoseconds nanoseconds, std::uint32_t symbol_id, std::uint64_t order_id, Decimal price, std::uint32_t size, const ModifyOrderFlags& modify_order_flags);

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

    // Price: Displayed price.
    Decimal price() const;
    void set_price(Decimal value);

    // Size: Number of displayed shares of the order.
    std::uint32_t size() const;
    void set_size(std::uint32_t value);

    // Modify Order Flags: Modify Order flags. Bit 0 indicates Order Position; bits 1-7 are
    // undefined.
    const ModifyOrderFlags& modify_order_flags() const;
    ModifyOrderFlags& modify_order_flags();
    void set_modify_order_flags(const ModifyOrderFlags& value);

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

    bool operator==(const ModifyOrderMessage& other) const;
    bool operator!=(const ModifyOrderMessage& other) const;

  private:
    std::chrono::nanoseconds nanoseconds_{};
    std::uint32_t symbol_id_{};
    std::uint64_t order_id_{};
    Decimal price_{ 0, -6 };
    std::uint32_t size_{};
    ModifyOrderFlags modify_order_flags_{};
};

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
