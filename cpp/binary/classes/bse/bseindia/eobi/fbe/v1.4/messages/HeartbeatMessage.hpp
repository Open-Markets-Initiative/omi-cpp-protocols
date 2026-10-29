#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../messages/Message.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

class Visitor;

// Published regularly when there is no activity on the snapshot or the incremental channel.
class HeartbeatMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::HeartbeatMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 8;

    HeartbeatMessage() = default;
    HeartbeatMessage(std::uint32_t last_msg_seq_num_processed, const std::array<std::byte, 4>& pad_4);

    // Last Msg Seq Num Processed: Last Message Sequence number that was processed.
    std::uint32_t last_msg_seq_num_processed() const;
    void set_last_msg_seq_num_processed(std::uint32_t value);

    // Pad 4: not used
    const std::array<std::byte, 4>& pad_4() const;
    std::array<std::byte, 4>& pad_4();
    void set_pad_4(const std::array<std::byte, 4>& value);

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

    bool operator==(const HeartbeatMessage& other) const;
    bool operator!=(const HeartbeatMessage& other) const;

  private:
    std::uint32_t last_msg_seq_num_processed_{};
    std::array<std::byte, 4> pad_4_{};
};

} // namespace bse::bseindia::eobi::fbe::v1_4
