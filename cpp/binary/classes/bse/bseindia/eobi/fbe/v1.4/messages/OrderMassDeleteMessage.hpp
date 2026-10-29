#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../messages/Message.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

class Visitor;

// Published when the order book is expected to be emptied.
class OrderMassDeleteMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::OrderMassDeleteMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 16;

    OrderMassDeleteMessage() = default;
    OrderMassDeleteMessage(std::int64_t security_id, std::chrono::nanoseconds transact_time);

    // Security Id: Unique instrument identifier.
    std::int64_t security_id() const;
    void set_security_id(std::int64_t value);

    // Transact Time: Transaction timestamp.
    std::chrono::nanoseconds transact_time() const;
    void set_transact_time(std::chrono::nanoseconds value);

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

    bool operator==(const OrderMassDeleteMessage& other) const;
    bool operator!=(const OrderMassDeleteMessage& other) const;

  private:
    std::int64_t security_id_{};
    std::chrono::nanoseconds transact_time_{};
};

} // namespace bse::bseindia::eobi::fbe::v1_4
