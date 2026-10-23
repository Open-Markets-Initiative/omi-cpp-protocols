#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../messages/Message.hpp"

namespace lseg::lse::level2mbo::gtp::v26_2 {

class Visitor;

// Used to indicate individual orders of an MBO snapshot.
class AddOrderShortMboMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::AddOrderShortMboMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 43;

    AddOrderShortMboMessage() = default;
    AddOrderShortMboMessage(std::uint64_t order_id, Decimal size, Decimal price, const std::array<std::byte, 8>& reserved_8, const std::string& participant);

    // Order Id: Unique identifier of the order.
    std::uint64_t order_id() const;
    void set_order_id(std::uint64_t value);

    // Size: Displayed size of the order.
    Decimal size() const;
    void set_size(Decimal value);

    // Price: Limit price of the order.
    Decimal price() const;
    void set_price(Decimal value);

    // Reserved 8: Reserved for future use.
    const std::array<std::byte, 8>& reserved_8() const;
    std::array<std::byte, 8>& reserved_8();
    void set_reserved_8(const std::array<std::byte, 8>& value);

    // Participant: Identity of trading participant that submitted the order.
    const std::string& participant() const;
    std::string& participant();
    void set_participant(const std::string& value);

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

    bool operator==(const AddOrderShortMboMessage& other) const;
    bool operator!=(const AddOrderShortMboMessage& other) const;

  private:
    std::uint64_t order_id_{};
    Decimal size_{ 0, -8 };
    Decimal price_{ 0, -8 };
    std::array<std::byte, 8> reserved_8_{};
    std::string participant_{};
};

} // namespace lseg::lse::level2mbo::gtp::v26_2
