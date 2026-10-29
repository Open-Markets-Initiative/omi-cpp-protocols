#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/SequencedMessageType.hpp"
#include "../messages/SystemEventMessage.hpp"
#include "../messages/OrderAcceptedMessage.hpp"
#include "../messages/OrderReplacedMessage.hpp"
#include "../messages/OrderCanceledMessage.hpp"
#include "../messages/OrderAiqCanceledMessage.hpp"
#include "../messages/OrderExecutedMessage.hpp"
#include "../messages/OrderRejectedMessage.hpp"

namespace jnx::jnxequities::pts::ouch::v1_11 {

// The Sequenced Data Packets act as an envelope to carry the actual sequenced data messages
// that are transferred from the server to the client. Each Sequenced Data Packet carries one
// message from the higher-lever protocol
class SequencedDataPacket {
  public:
    static constexpr const char* name = "SequencedDataPacket";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SequencedDataPacket(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SequencedDataPacket has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 1;
    std::size_t encoded_size() const { return sequenced_message_end(); }

    SequencedMessageType sequenced_message_type() const { return static_cast<SequencedMessageType>(wire::read_char(at(0))); }

    // the bytes the message it selects is read from
    std::span<const std::byte> sequenced_message_bytes() const {
        wire::require("SequencedDataPacket", 1, bytes_.size());
        return bytes_.subspan(1);
    }

    // the message its sequenced_message_type selects, handed to the handler as its view
    template <typename Handler>
    void sequenced_message(Handler& handler) const {
        const auto bytes = sequenced_message_bytes();
        switch (sequenced_message_type()) {
            case SequencedMessageType::SystemEventMessage: {
                wire::require(SystemEventMessage::name, SystemEventMessage::minimum_size, bytes.size());
                const SystemEventMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case SequencedMessageType::OrderAcceptedMessage: {
                wire::require(OrderAcceptedMessage::name, OrderAcceptedMessage::minimum_size, bytes.size());
                const OrderAcceptedMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case SequencedMessageType::OrderReplacedMessage: {
                wire::require(OrderReplacedMessage::name, OrderReplacedMessage::minimum_size, bytes.size());
                const OrderReplacedMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case SequencedMessageType::OrderCanceledMessage: {
                wire::require(OrderCanceledMessage::name, OrderCanceledMessage::minimum_size, bytes.size());
                const OrderCanceledMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case SequencedMessageType::OrderAiqCanceledMessage: {
                wire::require(OrderAiqCanceledMessage::name, OrderAiqCanceledMessage::minimum_size, bytes.size());
                const OrderAiqCanceledMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case SequencedMessageType::OrderExecutedMessage: {
                wire::require(OrderExecutedMessage::name, OrderExecutedMessage::minimum_size, bytes.size());
                const OrderExecutedMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case SequencedMessageType::OrderRejectedMessage: {
                wire::require(OrderRejectedMessage::name, OrderRejectedMessage::minimum_size, bytes.size());
                const OrderRejectedMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            default:
                if constexpr (requires { handler.on_unknown(sequenced_message_type(), bytes); }) { handler.on_unknown(sequenced_message_type(), bytes); }
                return;
        }
    }

    // the bytes the message it selects takes
    std::size_t sequenced_message_size() const {
        const auto bytes = sequenced_message_bytes();
        switch (sequenced_message_type()) {
            case SequencedMessageType::SystemEventMessage: return SystemEventMessage{ bytes }.encoded_size();
            case SequencedMessageType::OrderAcceptedMessage: return OrderAcceptedMessage{ bytes }.encoded_size();
            case SequencedMessageType::OrderReplacedMessage: return OrderReplacedMessage{ bytes }.encoded_size();
            case SequencedMessageType::OrderCanceledMessage: return OrderCanceledMessage{ bytes }.encoded_size();
            case SequencedMessageType::OrderAiqCanceledMessage: return OrderAiqCanceledMessage{ bytes }.encoded_size();
            case SequencedMessageType::OrderExecutedMessage: return OrderExecutedMessage{ bytes }.encoded_size();
            case SequencedMessageType::OrderRejectedMessage: return OrderRejectedMessage{ bytes }.encoded_size();
            default: return bytes.size();
        }
    }

    // the message it selects, printed; a code no message answers to prints its bytes
    void sequenced_message_print(std::ostream& out) const {
        const auto bytes = sequenced_message_bytes();
        switch (sequenced_message_type()) {
            case SequencedMessageType::SystemEventMessage: SystemEventMessage{ bytes }.print(out); return;
            case SequencedMessageType::OrderAcceptedMessage: OrderAcceptedMessage{ bytes }.print(out); return;
            case SequencedMessageType::OrderReplacedMessage: OrderReplacedMessage{ bytes }.print(out); return;
            case SequencedMessageType::OrderCanceledMessage: OrderCanceledMessage{ bytes }.print(out); return;
            case SequencedMessageType::OrderAiqCanceledMessage: OrderAiqCanceledMessage{ bytes }.print(out); return;
            case SequencedMessageType::OrderExecutedMessage: OrderExecutedMessage{ bytes }.print(out); return;
            case SequencedMessageType::OrderRejectedMessage: OrderRejectedMessage{ bytes }.print(out); return;
            default:
                out << "UnknownSequencedMessage{type=" << sequenced_message_type() << ", body=";
                print::hex(out, bytes.data(), bytes.size());
                out << '}';
                return;
        }
    }

    void print(std::ostream& out) const {
        out << "SequencedDataPacket{";
        out << "sequenced_message_type=";
        out << sequenced_message_type();
        out << ", sequenced_message=";
        sequenced_message_print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t sequenced_message_end() const { return 1 + sequenced_message_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const SequencedDataPacket& value) {
    value.print(out);
    return out;
}

} // namespace jnx::jnxequities::pts::ouch::v1_11
