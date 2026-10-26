#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/MessageType.hpp"
#include "../messages/SystemTimeMessage.hpp"
#include "../messages/SymbolUpdateMessage.hpp"
#include "../messages/SystemStateMessage.hpp"
#include "../messages/SecurityTradingStatusNotificationMessage.hpp"
#include "../messages/SymbolClearMessage.hpp"
#include "../messages/AddOrderMessage.hpp"
#include "../messages/ModifyOrderMessage.hpp"
#include "../messages/DeleteOrderMessage.hpp"
#include "../messages/OrderExecutionMessage.hpp"
#include "../messages/TradeMessage.hpp"
#include "../messages/TradeCancelMessage.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

class ApplicationMessage {
  public:
    static constexpr const char* name = "ApplicationMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit ApplicationMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every ApplicationMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 1;
    std::size_t encoded_size() const { return data_end(); }

    MessageType message_type() const { return static_cast<MessageType>(wire::read_u8(at(0))); }

    // the bytes the message it selects is read from
    std::span<const std::byte> data_bytes() const {
        wire::require("ApplicationMessage", 1, bytes_.size());
        return bytes_.subspan(1);
    }

    // the message its message_type selects, handed to the handler as its view
    template <typename Handler>
    void data(Handler& handler) const {
        const auto bytes = data_bytes();
        switch (message_type()) {
            case MessageType::SystemTimeMessage: {
                wire::require(SystemTimeMessage::name, SystemTimeMessage::minimum_size, bytes.size());
                const SystemTimeMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case MessageType::SymbolUpdateMessage: {
                wire::require(SymbolUpdateMessage::name, SymbolUpdateMessage::minimum_size, bytes.size());
                const SymbolUpdateMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case MessageType::SystemStateMessage: {
                wire::require(SystemStateMessage::name, SystemStateMessage::minimum_size, bytes.size());
                const SystemStateMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case MessageType::SecurityTradingStatusNotificationMessage: {
                wire::require(SecurityTradingStatusNotificationMessage::name, SecurityTradingStatusNotificationMessage::minimum_size, bytes.size());
                const SecurityTradingStatusNotificationMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case MessageType::SymbolClearMessage: {
                wire::require(SymbolClearMessage::name, SymbolClearMessage::minimum_size, bytes.size());
                const SymbolClearMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case MessageType::AddOrderMessage: {
                wire::require(AddOrderMessage::name, AddOrderMessage::minimum_size, bytes.size());
                const AddOrderMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case MessageType::ModifyOrderMessage: {
                wire::require(ModifyOrderMessage::name, ModifyOrderMessage::minimum_size, bytes.size());
                const ModifyOrderMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case MessageType::DeleteOrderMessage: {
                wire::require(DeleteOrderMessage::name, DeleteOrderMessage::minimum_size, bytes.size());
                const DeleteOrderMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case MessageType::OrderExecutionMessage: {
                wire::require(OrderExecutionMessage::name, OrderExecutionMessage::minimum_size, bytes.size());
                const OrderExecutionMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case MessageType::TradeMessage: {
                wire::require(TradeMessage::name, TradeMessage::minimum_size, bytes.size());
                const TradeMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case MessageType::TradeCancelMessage: {
                wire::require(TradeCancelMessage::name, TradeCancelMessage::minimum_size, bytes.size());
                const TradeCancelMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            default:
                if constexpr (requires { handler.on_unknown(message_type(), bytes); }) { handler.on_unknown(message_type(), bytes); }
                return;
        }
    }

    // the bytes the message it selects takes
    std::size_t data_size() const {
        const auto bytes = data_bytes();
        switch (message_type()) {
            case MessageType::SystemTimeMessage: return SystemTimeMessage{ bytes }.encoded_size();
            case MessageType::SymbolUpdateMessage: return SymbolUpdateMessage{ bytes }.encoded_size();
            case MessageType::SystemStateMessage: return SystemStateMessage{ bytes }.encoded_size();
            case MessageType::SecurityTradingStatusNotificationMessage: return SecurityTradingStatusNotificationMessage{ bytes }.encoded_size();
            case MessageType::SymbolClearMessage: return SymbolClearMessage{ bytes }.encoded_size();
            case MessageType::AddOrderMessage: return AddOrderMessage{ bytes }.encoded_size();
            case MessageType::ModifyOrderMessage: return ModifyOrderMessage{ bytes }.encoded_size();
            case MessageType::DeleteOrderMessage: return DeleteOrderMessage{ bytes }.encoded_size();
            case MessageType::OrderExecutionMessage: return OrderExecutionMessage{ bytes }.encoded_size();
            case MessageType::TradeMessage: return TradeMessage{ bytes }.encoded_size();
            case MessageType::TradeCancelMessage: return TradeCancelMessage{ bytes }.encoded_size();
            default: return bytes.size();
        }
    }

    // the message it selects, printed; a code no message answers to prints its bytes
    void data_print(std::ostream& out) const {
        const auto bytes = data_bytes();
        switch (message_type()) {
            case MessageType::SystemTimeMessage: SystemTimeMessage{ bytes }.print(out); return;
            case MessageType::SymbolUpdateMessage: SymbolUpdateMessage{ bytes }.print(out); return;
            case MessageType::SystemStateMessage: SystemStateMessage{ bytes }.print(out); return;
            case MessageType::SecurityTradingStatusNotificationMessage: SecurityTradingStatusNotificationMessage{ bytes }.print(out); return;
            case MessageType::SymbolClearMessage: SymbolClearMessage{ bytes }.print(out); return;
            case MessageType::AddOrderMessage: AddOrderMessage{ bytes }.print(out); return;
            case MessageType::ModifyOrderMessage: ModifyOrderMessage{ bytes }.print(out); return;
            case MessageType::DeleteOrderMessage: DeleteOrderMessage{ bytes }.print(out); return;
            case MessageType::OrderExecutionMessage: OrderExecutionMessage{ bytes }.print(out); return;
            case MessageType::TradeMessage: TradeMessage{ bytes }.print(out); return;
            case MessageType::TradeCancelMessage: TradeCancelMessage{ bytes }.print(out); return;
            default:
                out << "UnknownData{type=" << message_type() << ", body=";
                print::hex(out, bytes.data(), bytes.size());
                out << '}';
                return;
        }
    }

    void print(std::ostream& out) const {
        out << "ApplicationMessage{";
        out << "message_type=";
        out << message_type();
        out << ", data=";
        data_print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t data_end() const { return 1 + data_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const ApplicationMessage& value) {
    value.print(out);
    return out;
}

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
