#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../messages/Message.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

class Visitor;

// Published whenever there is a change in the limit price protection range of the instrument.
class LppRangeMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::LppRangeMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 24;

    LppRangeMessage() = default;
    LppRangeMessage(std::int64_t security_id, Decimal upper_exec_limit, Decimal lower_exec_limit);

    // Security Id: Unique instrument identifier.
    std::int64_t security_id() const;
    void set_security_id(std::int64_t value);

    // Upper Exec Limit: Upper Limit Execution Price
    Decimal upper_exec_limit() const;
    void set_upper_exec_limit(Decimal value);

    // Lower Exec Limit: Lower Limit Execution Price
    Decimal lower_exec_limit() const;
    void set_lower_exec_limit(Decimal value);

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

    bool operator==(const LppRangeMessage& other) const;
    bool operator!=(const LppRangeMessage& other) const;

  private:
    std::int64_t security_id_{};
    Decimal upper_exec_limit_{ 0, -6 };
    Decimal lower_exec_limit_{ 0, -6 };
};

} // namespace bse::bseindia::eobi::fbe::v1_4
