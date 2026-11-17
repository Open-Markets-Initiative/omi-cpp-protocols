// Miax.OnyxFutures.TopOfMarket.Mach.v1.0.b: messages/ApplicationMessage.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/MessageType.hpp"
#include "../messages/SimpleInstrumentDefinitionMessage.hpp"
#include "../messages/ComplexInstrumentDefinitionMessage.hpp"
#include "../messages/SystemStateMessage.hpp"
#include "../messages/InstrumentTradingStatusNotificationMessage.hpp"
#include "../messages/BestBidAndOfferMessage.hpp"
#include "../messages/LastSaleMessage.hpp"
#include "../messages/TradeCancelMessage.hpp"

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

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
            case MessageType::SimpleInstrumentDefinitionMessage: {
                wire::require(SimpleInstrumentDefinitionMessage::name, SimpleInstrumentDefinitionMessage::minimum_size, bytes.size());
                const SimpleInstrumentDefinitionMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case MessageType::ComplexInstrumentDefinitionMessage: {
                wire::require(ComplexInstrumentDefinitionMessage::name, ComplexInstrumentDefinitionMessage::minimum_size, bytes.size());
                const ComplexInstrumentDefinitionMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case MessageType::SystemStateMessage: {
                wire::require(SystemStateMessage::name, SystemStateMessage::minimum_size, bytes.size());
                const SystemStateMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case MessageType::InstrumentTradingStatusNotificationMessage: {
                wire::require(InstrumentTradingStatusNotificationMessage::name, InstrumentTradingStatusNotificationMessage::minimum_size, bytes.size());
                const InstrumentTradingStatusNotificationMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case MessageType::BestBidAndOfferMessage: {
                wire::require(BestBidAndOfferMessage::name, BestBidAndOfferMessage::minimum_size, bytes.size());
                const BestBidAndOfferMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case MessageType::LastSaleMessage: {
                wire::require(LastSaleMessage::name, LastSaleMessage::minimum_size, bytes.size());
                const LastSaleMessage message{ bytes };
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
            case MessageType::SimpleInstrumentDefinitionMessage: return SimpleInstrumentDefinitionMessage{ bytes }.encoded_size();
            case MessageType::ComplexInstrumentDefinitionMessage: return ComplexInstrumentDefinitionMessage{ bytes }.encoded_size();
            case MessageType::SystemStateMessage: return SystemStateMessage{ bytes }.encoded_size();
            case MessageType::InstrumentTradingStatusNotificationMessage: return InstrumentTradingStatusNotificationMessage{ bytes }.encoded_size();
            case MessageType::BestBidAndOfferMessage: return BestBidAndOfferMessage{ bytes }.encoded_size();
            case MessageType::LastSaleMessage: return LastSaleMessage{ bytes }.encoded_size();
            case MessageType::TradeCancelMessage: return TradeCancelMessage{ bytes }.encoded_size();
            default: return bytes.size();
        }
    }

    // the message it selects, printed; a code no message answers to prints its bytes
    void data_print(std::ostream& out) const {
        const auto bytes = data_bytes();
        switch (message_type()) {
            case MessageType::SimpleInstrumentDefinitionMessage: SimpleInstrumentDefinitionMessage{ bytes }.print(out); return;
            case MessageType::ComplexInstrumentDefinitionMessage: ComplexInstrumentDefinitionMessage{ bytes }.print(out); return;
            case MessageType::SystemStateMessage: SystemStateMessage{ bytes }.print(out); return;
            case MessageType::InstrumentTradingStatusNotificationMessage: InstrumentTradingStatusNotificationMessage{ bytes }.print(out); return;
            case MessageType::BestBidAndOfferMessage: BestBidAndOfferMessage{ bytes }.print(out); return;
            case MessageType::LastSaleMessage: LastSaleMessage{ bytes }.print(out); return;
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

} // namespace miax::onyxfutures::topofmarket::mach::v1_0_b
