#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/UnsequencedMessageType.hpp"
#include "../messages/RefreshRequestMessage.hpp"
#include "../messages/RefreshResponseMessage.hpp"
#include "../messages/EndOfRefreshNotificationMessage.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

// Each unsequenced data packet carries one unsequenced message from the higher-lever protocol
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
            case UnsequencedMessageType::RefreshRequestMessage: {
                wire::require(RefreshRequestMessage::name, RefreshRequestMessage::minimum_size, bytes.size());
                const RefreshRequestMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case UnsequencedMessageType::RefreshResponseMessage: {
                wire::require(RefreshResponseMessage::name, RefreshResponseMessage::minimum_size, bytes.size());
                const RefreshResponseMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case UnsequencedMessageType::EndOfRefreshNotificationMessage: {
                wire::require(EndOfRefreshNotificationMessage::name, EndOfRefreshNotificationMessage::minimum_size, bytes.size());
                const EndOfRefreshNotificationMessage message{ bytes };
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
            case UnsequencedMessageType::RefreshRequestMessage: return RefreshRequestMessage{ bytes }.encoded_size();
            case UnsequencedMessageType::RefreshResponseMessage: return RefreshResponseMessage{ bytes }.encoded_size();
            case UnsequencedMessageType::EndOfRefreshNotificationMessage: return EndOfRefreshNotificationMessage{ bytes }.encoded_size();
            default: return bytes.size();
        }
    }

    // the message it selects, printed; a code no message answers to prints its bytes
    void unsequenced_message_print(std::ostream& out) const {
        const auto bytes = unsequenced_message_bytes();
        switch (unsequenced_message_type()) {
            case UnsequencedMessageType::RefreshRequestMessage: RefreshRequestMessage{ bytes }.print(out); return;
            case UnsequencedMessageType::RefreshResponseMessage: RefreshResponseMessage{ bytes }.print(out); return;
            case UnsequencedMessageType::EndOfRefreshNotificationMessage: EndOfRefreshNotificationMessage{ bytes }.print(out); return;
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

} // namespace miax::miaxoptions::topofmarket::mach::v2_5
