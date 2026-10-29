#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../enums/SpinType.hpp"
#include "../messages/Message.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

class Visitor;

// This message appears on all quote channels and indicates the end of a spin message cycle.
class EndOfSpinMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::EndOfSpinMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 21;

    EndOfSpinMessage() = default;
    EndOfSpinMessage(std::uint32_t channel_seq_num, SpinType spin_type, std::uint32_t spin_msg_ct, std::uint64_t spin_end_time_milli, std::uint32_t spin_last_seq_num);

    // Channel Seq Num: Monotonically increasing message sequence number at the channel level.
    std::uint32_t channel_seq_num() const;
    void set_channel_seq_num(std::uint32_t value);

    // Spin Type: Spin type
    SpinType spin_type() const;
    void set_spin_type(SpinType value);

    // Spin Msg Ct: Total number of messages in the spin.
    std::uint32_t spin_msg_ct() const;
    void set_spin_msg_ct(std::uint32_t value);

    // Spin End Time Milli: Milliseconds since UTC epoch.
    std::uint64_t spin_end_time_milli() const;
    void set_spin_end_time_milli(std::uint64_t value);

    // Spin Last Seq Num: Last sequence number applied to this spin.
    std::uint32_t spin_last_seq_num() const;
    void set_spin_last_seq_num(std::uint32_t value);

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

    bool operator==(const EndOfSpinMessage& other) const;
    bool operator!=(const EndOfSpinMessage& other) const;

  private:
    std::uint32_t channel_seq_num_{};
    SpinType spin_type_{};
    std::uint32_t spin_msg_ct_{};
    std::uint64_t spin_end_time_milli_{};
    std::uint32_t spin_last_seq_num_{};
};

} // namespace otcmarkets::linkats::multicast::link::v4_3
