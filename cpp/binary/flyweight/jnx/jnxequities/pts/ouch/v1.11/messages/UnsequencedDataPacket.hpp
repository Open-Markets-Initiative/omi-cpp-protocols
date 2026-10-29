#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/UnsequencedMessageType.hpp"
#include "../messages/EnterOrderMessage.hpp"
#include "../messages/ReplaceOrderMessage.hpp"
#include "../messages/CancelOrderMessage.hpp"

namespace jnx::jnxequities::pts::ouch::v1_11 {

// The Unsequenced Data Packets act as an envelope to carry the actual data messages that are
// transferred from the client to the server
class UnsequencedDataPacket {
  public:
    static constexpr const char* name = "UnsequencedDataPacket";

    // the bytes it reads, which it does not own: they must outlive it
    explicit UnsequencedDataPacket(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every UnsequencedDataPacket has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 1;
    std::size_t encoded_size() const { return unsequenced_message_end(); }

    UnsequencedMessageType unsequenced_message_type() const { return static_cast<UnsequencedMessageType>(wire::read_char(at(0))); }

    // the bytes the message it selects is read from
    std::span<const std::byte> unsequenced_message_bytes() const {
        wire::require("UnsequencedDataPacket", 1, bytes_.size());
        return bytes_.subspan(1);
    }

    // the message its unsequenced_message_type selects, handed to the handler as its view
    template <typename Handler>
    void unsequenced_message(Handler& handler) const {
        const auto bytes = unsequenced_message_bytes();
        switch (unsequenced_message_type()) {
            case UnsequencedMessageType::EnterOrderMessage: {
                wire::require(EnterOrderMessage::name, EnterOrderMessage::minimum_size, bytes.size());
                const EnterOrderMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case UnsequencedMessageType::ReplaceOrderMessage: {
                wire::require(ReplaceOrderMessage::name, ReplaceOrderMessage::minimum_size, bytes.size());
                const ReplaceOrderMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case UnsequencedMessageType::CancelOrderMessage: {
                wire::require(CancelOrderMessage::name, CancelOrderMessage::minimum_size, bytes.size());
                const CancelOrderMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            default:
                if constexpr (requires { handler.on_unknown(unsequenced_message_type(), bytes); }) { handler.on_unknown(unsequenced_message_type(), bytes); }
                return;
        }
    }

    // the bytes the message it selects takes
    std::size_t unsequenced_message_size() const {
        const auto bytes = unsequenced_message_bytes();
        switch (unsequenced_message_type()) {
            case UnsequencedMessageType::EnterOrderMessage: return EnterOrderMessage{ bytes }.encoded_size();
            case UnsequencedMessageType::ReplaceOrderMessage: return ReplaceOrderMessage{ bytes }.encoded_size();
            case UnsequencedMessageType::CancelOrderMessage: return CancelOrderMessage{ bytes }.encoded_size();
            default: return bytes.size();
        }
    }

    // the message it selects, printed; a code no message answers to prints its bytes
    void unsequenced_message_print(std::ostream& out) const {
        const auto bytes = unsequenced_message_bytes();
        switch (unsequenced_message_type()) {
            case UnsequencedMessageType::EnterOrderMessage: EnterOrderMessage{ bytes }.print(out); return;
            case UnsequencedMessageType::ReplaceOrderMessage: ReplaceOrderMessage{ bytes }.print(out); return;
            case UnsequencedMessageType::CancelOrderMessage: CancelOrderMessage{ bytes }.print(out); return;
            default:
                out << "UnknownUnsequencedMessage{type=" << unsequenced_message_type() << ", body=";
                print::hex(out, bytes.data(), bytes.size());
                out << '}';
                return;
        }
    }

    void print(std::ostream& out) const {
        out << "UnsequencedDataPacket{";
        out << "unsequenced_message_type=";
        out << unsequenced_message_type();
        out << ", unsequenced_message=";
        unsequenced_message_print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t unsequenced_message_end() const { return 1 + unsequenced_message_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const UnsequencedDataPacket& value) {
    value.print(out);
    return out;
}

} // namespace jnx::jnxequities::pts::ouch::v1_11
