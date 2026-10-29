#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../messages/Message.hpp"
#include "../structs/SemanticVersion.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

class Visitor;

// NegotiateResponseMessage
class NegotiateResponseMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::NegotiateResponseMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 28;

    NegotiateResponseMessage() = default;
    NegotiateResponseMessage(std::uint32_t session_id, std::uint64_t session_ver_id, std::chrono::nanoseconds request_timestamp, std::uint32_t entering_firm, const SemanticVersion& semantic_version);

    // Session Id: sessionID
    std::uint32_t session_id() const;
    void set_session_id(std::uint32_t value);

    // Session Ver Id: sessionVerID
    std::uint64_t session_ver_id() const;
    void set_session_ver_id(std::uint64_t value);

    // Request Timestamp: requestTimestamp
    std::chrono::nanoseconds request_timestamp() const;
    void set_request_timestamp(std::chrono::nanoseconds value);

    // Entering Firm: enteringFirm
    std::uint32_t entering_firm() const;
    void set_entering_firm(std::uint32_t value);

    // Semantic Version: NegotiateResponseMessage
    const SemanticVersion& semantic_version() const;
    SemanticVersion& semantic_version();
    void set_semantic_version(const SemanticVersion& value);

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

    bool operator==(const NegotiateResponseMessage& other) const;
    bool operator!=(const NegotiateResponseMessage& other) const;

  private:
    std::uint32_t session_id_{};
    std::uint64_t session_ver_id_{};
    std::chrono::nanoseconds request_timestamp_{};
    std::uint32_t entering_firm_{};
    SemanticVersion semantic_version_{};
};

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
