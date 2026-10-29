#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../enums/TerminationCode.hpp"
#include "../messages/Message.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

class Visitor;

// TerminateMessage
class TerminateMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::TerminateMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 13;

    TerminateMessage() = default;
    TerminateMessage(std::uint32_t session_id, std::uint64_t session_ver_id, TerminationCode termination_code);

    // Session Id: sessionID
    std::uint32_t session_id() const;
    void set_session_id(std::uint32_t value);

    // Session Ver Id: sessionVerID
    std::uint64_t session_ver_id() const;
    void set_session_ver_id(std::uint64_t value);

    // Termination Code: terminationCode
    TerminationCode termination_code() const;
    void set_termination_code(TerminationCode value);

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

    bool operator==(const TerminateMessage& other) const;
    bool operator!=(const TerminateMessage& other) const;

  private:
    std::uint32_t session_id_{};
    std::uint64_t session_ver_id_{};
    TerminationCode termination_code_{};
};

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0
