#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../messages/Data.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

class DataVisitor;

// This message format is used to indicate that a displayed order has been removed from the
// MIAX Pearl Equities book.
class DeleteOrderMessage : public Data {
  public:
    // The code that selects this message
    static constexpr DataCode message_type = MessageType::DeleteOrderMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 16;

    DeleteOrderMessage() = default;
    DeleteOrderMessage(std::chrono::nanoseconds nanoseconds, std::uint32_t symbol_id, std::uint64_t order_id);

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

    bool operator==(const DeleteOrderMessage& other) const;
    bool operator!=(const DeleteOrderMessage& other) const;

  private:
    std::chrono::nanoseconds nanoseconds_{};
    std::uint32_t symbol_id_{};
    std::uint64_t order_id_{};
};

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
