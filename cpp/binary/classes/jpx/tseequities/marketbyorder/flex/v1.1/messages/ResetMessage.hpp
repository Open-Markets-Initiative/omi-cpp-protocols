#pragma once

#include <cstddef>
#include <memory>
#include <ostream>
#include <string_view>

#include "../enums/ResetStartEndFlag.hpp"
#include "../messages/Message.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

class Visitor;

// A tag requesting the resetting (i.e. cancellation) of all distributed information. When the
// user receives this tag, the user must clear all valid A tags.
class ResetMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::ResetMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 1;

    ResetMessage() = default;
    ResetMessage(ResetStartEndFlag reset_start_end_flag);

    // Reset Start End Flag: When TSE needs to reset all distributed data, this indicates the
    // start or end of the process
    ResetStartEndFlag reset_start_end_flag() const;
    void set_reset_start_end_flag(ResetStartEndFlag value);

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

    bool operator==(const ResetMessage& other) const;
    bool operator!=(const ResetMessage& other) const;

  private:
    ResetStartEndFlag reset_start_end_flag_{};
};

} // namespace jpx::tseequities::marketbyorder::flex::v1_1
