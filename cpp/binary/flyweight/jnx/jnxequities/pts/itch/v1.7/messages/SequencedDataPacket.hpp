#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/SequencedMessageType.hpp"
#include "../messages/SecondsMessage.hpp"
#include "../messages/SystemEventMessage.hpp"
#include "../messages/PriceTickSizeMessage.hpp"
#include "../messages/OrderbookDirectoryMessage.hpp"
#include "../messages/TradingStateMessage.hpp"
#include "../messages/ShortSellingPriceRestrictionStateMessage.hpp"
#include "../messages/OrderAddedWithoutAttributesMessage.hpp"
#include "../messages/OrderAddedWithAttributesMessage.hpp"
#include "../messages/OrderExecutedMessage.hpp"
#include "../messages/OrderDeletedMessage.hpp"
#include "../messages/OrderReplacedMessage.hpp"

namespace jnx::jnxequities::pts::itch::v1_7 {

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
            case SequencedMessageType::TimestampSecondsMessage: {
                wire::require(SecondsMessage::name, SecondsMessage::minimum_size, bytes.size());
                const SecondsMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case SequencedMessageType::SystemEventMessage: {
                wire::require(SystemEventMessage::name, SystemEventMessage::minimum_size, bytes.size());
                const SystemEventMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case SequencedMessageType::PriceTickSizeMessage: {
                wire::require(PriceTickSizeMessage::name, PriceTickSizeMessage::minimum_size, bytes.size());
                const PriceTickSizeMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case SequencedMessageType::OrderbookDirectoryMessage: {
                wire::require(OrderbookDirectoryMessage::name, OrderbookDirectoryMessage::minimum_size, bytes.size());
                const OrderbookDirectoryMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case SequencedMessageType::TradingStateMessage: {
                wire::require(TradingStateMessage::name, TradingStateMessage::minimum_size, bytes.size());
                const TradingStateMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case SequencedMessageType::ShortSellingPriceRestrictionStateMessage: {
                wire::require(ShortSellingPriceRestrictionStateMessage::name, ShortSellingPriceRestrictionStateMessage::minimum_size, bytes.size());
                const ShortSellingPriceRestrictionStateMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case SequencedMessageType::OrderAddedWithoutAttributesMessage: {
                wire::require(OrderAddedWithoutAttributesMessage::name, OrderAddedWithoutAttributesMessage::minimum_size, bytes.size());
                const OrderAddedWithoutAttributesMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case SequencedMessageType::OrderAddedWithAttributesMessage: {
                wire::require(OrderAddedWithAttributesMessage::name, OrderAddedWithAttributesMessage::minimum_size, bytes.size());
                const OrderAddedWithAttributesMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case SequencedMessageType::OrderExecutedMessage: {
                wire::require(OrderExecutedMessage::name, OrderExecutedMessage::minimum_size, bytes.size());
                const OrderExecutedMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case SequencedMessageType::OrderDeletedMessage: {
                wire::require(OrderDeletedMessage::name, OrderDeletedMessage::minimum_size, bytes.size());
                const OrderDeletedMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case SequencedMessageType::OrderReplacedMessage: {
                wire::require(OrderReplacedMessage::name, OrderReplacedMessage::minimum_size, bytes.size());
                const OrderReplacedMessage message{ bytes };
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
            case SequencedMessageType::TimestampSecondsMessage: return SecondsMessage{ bytes }.encoded_size();
            case SequencedMessageType::SystemEventMessage: return SystemEventMessage{ bytes }.encoded_size();
            case SequencedMessageType::PriceTickSizeMessage: return PriceTickSizeMessage{ bytes }.encoded_size();
            case SequencedMessageType::OrderbookDirectoryMessage: return OrderbookDirectoryMessage{ bytes }.encoded_size();
            case SequencedMessageType::TradingStateMessage: return TradingStateMessage{ bytes }.encoded_size();
            case SequencedMessageType::ShortSellingPriceRestrictionStateMessage: return ShortSellingPriceRestrictionStateMessage{ bytes }.encoded_size();
            case SequencedMessageType::OrderAddedWithoutAttributesMessage: return OrderAddedWithoutAttributesMessage{ bytes }.encoded_size();
            case SequencedMessageType::OrderAddedWithAttributesMessage: return OrderAddedWithAttributesMessage{ bytes }.encoded_size();
            case SequencedMessageType::OrderExecutedMessage: return OrderExecutedMessage{ bytes }.encoded_size();
            case SequencedMessageType::OrderDeletedMessage: return OrderDeletedMessage{ bytes }.encoded_size();
            case SequencedMessageType::OrderReplacedMessage: return OrderReplacedMessage{ bytes }.encoded_size();
            default: return bytes.size();
        }
    }

    // the message it selects, printed; a code no message answers to prints its bytes
    void sequenced_message_print(std::ostream& out) const {
        const auto bytes = sequenced_message_bytes();
        switch (sequenced_message_type()) {
            case SequencedMessageType::TimestampSecondsMessage: SecondsMessage{ bytes }.print(out); return;
            case SequencedMessageType::SystemEventMessage: SystemEventMessage{ bytes }.print(out); return;
            case SequencedMessageType::PriceTickSizeMessage: PriceTickSizeMessage{ bytes }.print(out); return;
            case SequencedMessageType::OrderbookDirectoryMessage: OrderbookDirectoryMessage{ bytes }.print(out); return;
            case SequencedMessageType::TradingStateMessage: TradingStateMessage{ bytes }.print(out); return;
            case SequencedMessageType::ShortSellingPriceRestrictionStateMessage: ShortSellingPriceRestrictionStateMessage{ bytes }.print(out); return;
            case SequencedMessageType::OrderAddedWithoutAttributesMessage: OrderAddedWithoutAttributesMessage{ bytes }.print(out); return;
            case SequencedMessageType::OrderAddedWithAttributesMessage: OrderAddedWithAttributesMessage{ bytes }.print(out); return;
            case SequencedMessageType::OrderExecutedMessage: OrderExecutedMessage{ bytes }.print(out); return;
            case SequencedMessageType::OrderDeletedMessage: OrderDeletedMessage{ bytes }.print(out); return;
            case SequencedMessageType::OrderReplacedMessage: OrderReplacedMessage{ bytes }.print(out); return;
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

} // namespace jnx::jnxequities::pts::itch::v1_7
