#pragma once

#include <cstddef>
#include <memory>
#include <ostream>
#include <string_view>

#include "../enums/CommunicationStartEndFlag.hpp"
#include "../enums/TestModeFlag.hpp"
#include "../messages/Message.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

class Visitor;

// Provides information about communication control. Delivered when communication starts and
// ends, and in between at minute intervals.
class CommunicationControlMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::CommunicationControlMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 2;

    CommunicationControlMessage() = default;
    CommunicationControlMessage(TestModeFlag test_mode_flag, CommunicationStartEndFlag communication_start_end_flag);

    // Test Mode Flag: Indicates production or test
    TestModeFlag test_mode_flag() const;
    void set_test_mode_flag(TestModeFlag value);

    // Communication Start End Flag: Indicates the start or end of communication
    CommunicationStartEndFlag communication_start_end_flag() const;
    void set_communication_start_end_flag(CommunicationStartEndFlag value);

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

    bool operator==(const CommunicationControlMessage& other) const;
    bool operator!=(const CommunicationControlMessage& other) const;

  private:
    TestModeFlag test_mode_flag_{};
    CommunicationStartEndFlag communication_start_end_flag_{};
};

} // namespace jpx::tseequities::marketbyorder::flex::v1_1
