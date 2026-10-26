#pragma once

#include <cstddef>
#include <memory>
#include <ostream>
#include <string_view>

#include "../enums/SummaryMessageType.hpp"
#include "../messages/Message.hpp"
#include "../messages/SummaryMessagePayload.hpp"

namespace siac::cts::output::cta::v2_11_b {

class Visitor;
class SummaryMessagePayloadVisitor;

// Summary Category Summary Messages Are Used To Provide Cta Eligible Equity Local Issue And
// Bond Summary Information By Security
class SummaryMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageCategory::Summary;

    SummaryMessage() = default;
    SummaryMessage(const SummaryMessage& other);
    SummaryMessage& operator=(const SummaryMessage& other);
    SummaryMessage(SummaryMessage&& other) noexcept = default;
    SummaryMessage& operator=(SummaryMessage&& other) noexcept = default;
    ~SummaryMessage() = default;

    // Summary Message Type: Identifies the type of Summary message
    SummaryMessageType summary_message_type() const;
    void set_summary_message_type(SummaryMessageType value);

    // Summary Message Payload: Branch
    const SummaryMessagePayload* summary_message_payload() const;
    SummaryMessagePayload* summary_message_payload();
    void set_summary_message_payload(std::unique_ptr<SummaryMessagePayload> value);

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

    bool operator==(const SummaryMessage& other) const;
    bool operator!=(const SummaryMessage& other) const;

  private:
    SummaryMessageType summary_message_type_{};
    std::unique_ptr<SummaryMessagePayload> summary_message_payload_{};
};

} // namespace siac::cts::output::cta::v2_11_b
