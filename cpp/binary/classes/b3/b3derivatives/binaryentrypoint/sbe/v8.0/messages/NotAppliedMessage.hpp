#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../messages/Message.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

class Visitor;

// NotAppliedMessage
class NotAppliedMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::NotAppliedMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 8;

    NotAppliedMessage() = default;
    NotAppliedMessage(std::uint32_t from_seq_no, std::uint32_t count);

    // From Seq No: fromSeqNo
    std::uint32_t from_seq_no() const;
    void set_from_seq_no(std::uint32_t value);

    // Count: count
    std::uint32_t count() const;
    void set_count(std::uint32_t value);

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

    bool operator==(const NotAppliedMessage& other) const;
    bool operator!=(const NotAppliedMessage& other) const;

  private:
    std::uint32_t from_seq_no_{};
    std::uint32_t count_{};
};

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0
