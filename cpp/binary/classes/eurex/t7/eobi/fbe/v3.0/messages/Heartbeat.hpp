#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <ostream>
#include <string_view>

#include "../messages/Message.hpp"

namespace eurex::t7::eobi::fbe::v3_0 {

class Visitor;

// Heartbeat
class Heartbeat : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::Heartbeat;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 8;

    Heartbeat() = default;
    Heartbeat(std::optional<std::uint32_t> last_msg_seq_num_processed, const std::array<std::byte, 4>& pad4);

    // Last Msg Seq Num Processed:
    std::optional<std::uint32_t> last_msg_seq_num_processed() const;
    void set_last_msg_seq_num_processed(std::optional<std::uint32_t> value);

    // Pad4:
    const std::array<std::byte, 4>& pad4() const;
    std::array<std::byte, 4>& pad4();
    void set_pad4(const std::array<std::byte, 4>& value);

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

    bool operator==(const Heartbeat& other) const;
    bool operator!=(const Heartbeat& other) const;

  private:
    std::optional<std::uint32_t> last_msg_seq_num_processed_{};
    std::array<std::byte, 4> pad4_{};
};

} // namespace eurex::t7::eobi::fbe::v3_0
