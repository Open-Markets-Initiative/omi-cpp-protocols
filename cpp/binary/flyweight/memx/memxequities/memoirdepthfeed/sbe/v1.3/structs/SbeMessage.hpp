#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../structs/SbeHeader.hpp"
#include "../enums/TemplateId.hpp"
#include "../messages/InstrumentDirectoryMessage.hpp"
#include "../messages/RegShoRestrictionMessage.hpp"
#include "../messages/SecurityTradingStatusMessage.hpp"
#include "../messages/TradingSessionStatusMessage.hpp"
#include "../messages/OrderAddedMessage.hpp"
#include "../messages/OrderDeletedMessage.hpp"
#include "../messages/OrderReducedMessage.hpp"
#include "../messages/OrderExecutedMessage.hpp"
#include "../messages/TradeMessage.hpp"
#include "../messages/BrokenTradeMessage.hpp"
#include "../messages/CorrectedTradeMessage.hpp"
#include "../messages/ClearBookMessage.hpp"
#include "../messages/SnapshotCompleteMessage.hpp"

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

// Sbe Message
class SbeMessage {
  public:
    static constexpr const char* name = "SbeMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SbeMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SbeMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 6;
    std::size_t encoded_size() const { return payload_end(); }

    SbeHeader sbe_header() const { return SbeHeader{ bytes_.subspan(0) }; }

    // the bytes the message it selects is read from
    std::span<const std::byte> payload_bytes() const {
        wire::require("SbeMessage", 6, bytes_.size());
        return bytes_.subspan(6);
    }

    // the message its template_id selects, handed to the handler as its view
    template <typename Handler>
    void payload(Handler& handler) const {
        const auto bytes = payload_bytes();
        switch (sbe_header().template_id()) {
            case TemplateId::InstrumentDirectoryMessage: {
                wire::require(InstrumentDirectoryMessage::name, InstrumentDirectoryMessage::minimum_size, bytes.size());
                const InstrumentDirectoryMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case TemplateId::RegShoRestrictionMessage: {
                wire::require(RegShoRestrictionMessage::name, RegShoRestrictionMessage::minimum_size, bytes.size());
                const RegShoRestrictionMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case TemplateId::SecurityTradingStatusMessage: {
                wire::require(SecurityTradingStatusMessage::name, SecurityTradingStatusMessage::minimum_size, bytes.size());
                const SecurityTradingStatusMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case TemplateId::TradingSessionStatusMessage: {
                wire::require(TradingSessionStatusMessage::name, TradingSessionStatusMessage::minimum_size, bytes.size());
                const TradingSessionStatusMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case TemplateId::OrderAddedMessage: {
                wire::require(OrderAddedMessage::name, OrderAddedMessage::minimum_size, bytes.size());
                const OrderAddedMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case TemplateId::OrderDeletedMessage: {
                wire::require(OrderDeletedMessage::name, OrderDeletedMessage::minimum_size, bytes.size());
                const OrderDeletedMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case TemplateId::OrderReducedMessage: {
                wire::require(OrderReducedMessage::name, OrderReducedMessage::minimum_size, bytes.size());
                const OrderReducedMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case TemplateId::OrderExecutedMessage: {
                wire::require(OrderExecutedMessage::name, OrderExecutedMessage::minimum_size, bytes.size());
                const OrderExecutedMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case TemplateId::TradeMessage: {
                wire::require(TradeMessage::name, TradeMessage::minimum_size, bytes.size());
                const TradeMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case TemplateId::BrokenTradeMessage: {
                wire::require(BrokenTradeMessage::name, BrokenTradeMessage::minimum_size, bytes.size());
                const BrokenTradeMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case TemplateId::CorrectedTradeMessage: {
                wire::require(CorrectedTradeMessage::name, CorrectedTradeMessage::minimum_size, bytes.size());
                const CorrectedTradeMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case TemplateId::ClearBookMessage: {
                wire::require(ClearBookMessage::name, ClearBookMessage::minimum_size, bytes.size());
                const ClearBookMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case TemplateId::SnapshotCompleteMessage: {
                wire::require(SnapshotCompleteMessage::name, SnapshotCompleteMessage::minimum_size, bytes.size());
                const SnapshotCompleteMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            default:
                if constexpr (requires { handler.on_unknown(sbe_header().template_id(), bytes); }) { handler.on_unknown(sbe_header().template_id(), bytes); }
                return;
        }
    }

    // the bytes the message it selects takes
    std::size_t payload_size() const {
        const auto bytes = payload_bytes();
        switch (sbe_header().template_id()) {
            case TemplateId::InstrumentDirectoryMessage: return InstrumentDirectoryMessage{ bytes }.encoded_size();
            case TemplateId::RegShoRestrictionMessage: return RegShoRestrictionMessage{ bytes }.encoded_size();
            case TemplateId::SecurityTradingStatusMessage: return SecurityTradingStatusMessage{ bytes }.encoded_size();
            case TemplateId::TradingSessionStatusMessage: return TradingSessionStatusMessage{ bytes }.encoded_size();
            case TemplateId::OrderAddedMessage: return OrderAddedMessage{ bytes }.encoded_size();
            case TemplateId::OrderDeletedMessage: return OrderDeletedMessage{ bytes }.encoded_size();
            case TemplateId::OrderReducedMessage: return OrderReducedMessage{ bytes }.encoded_size();
            case TemplateId::OrderExecutedMessage: return OrderExecutedMessage{ bytes }.encoded_size();
            case TemplateId::TradeMessage: return TradeMessage{ bytes }.encoded_size();
            case TemplateId::BrokenTradeMessage: return BrokenTradeMessage{ bytes }.encoded_size();
            case TemplateId::CorrectedTradeMessage: return CorrectedTradeMessage{ bytes }.encoded_size();
            case TemplateId::ClearBookMessage: return ClearBookMessage{ bytes }.encoded_size();
            case TemplateId::SnapshotCompleteMessage: return SnapshotCompleteMessage{ bytes }.encoded_size();
            default: return bytes.size();
        }
    }

    // the message it selects, printed; a code no message answers to prints its bytes
    void payload_print(std::ostream& out) const {
        const auto bytes = payload_bytes();
        switch (sbe_header().template_id()) {
            case TemplateId::InstrumentDirectoryMessage: InstrumentDirectoryMessage{ bytes }.print(out); return;
            case TemplateId::RegShoRestrictionMessage: RegShoRestrictionMessage{ bytes }.print(out); return;
            case TemplateId::SecurityTradingStatusMessage: SecurityTradingStatusMessage{ bytes }.print(out); return;
            case TemplateId::TradingSessionStatusMessage: TradingSessionStatusMessage{ bytes }.print(out); return;
            case TemplateId::OrderAddedMessage: OrderAddedMessage{ bytes }.print(out); return;
            case TemplateId::OrderDeletedMessage: OrderDeletedMessage{ bytes }.print(out); return;
            case TemplateId::OrderReducedMessage: OrderReducedMessage{ bytes }.print(out); return;
            case TemplateId::OrderExecutedMessage: OrderExecutedMessage{ bytes }.print(out); return;
            case TemplateId::TradeMessage: TradeMessage{ bytes }.print(out); return;
            case TemplateId::BrokenTradeMessage: BrokenTradeMessage{ bytes }.print(out); return;
            case TemplateId::CorrectedTradeMessage: CorrectedTradeMessage{ bytes }.print(out); return;
            case TemplateId::ClearBookMessage: ClearBookMessage{ bytes }.print(out); return;
            case TemplateId::SnapshotCompleteMessage: SnapshotCompleteMessage{ bytes }.print(out); return;
            default:
                out << "UnknownPayload{type=" << sbe_header().template_id() << ", body=";
                print::hex(out, bytes.data(), bytes.size());
                out << '}';
                return;
        }
    }

    void print(std::ostream& out) const {
        out << "SbeMessage{";
        out << "sbe_header=";
        sbe_header().print(out);
        out << ", payload=";
        payload_print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t payload_end() const { return 6 + payload_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const SbeMessage& value) {
    value.print(out);
    return out;
}

} // namespace memx::memxequities::memoirdepthfeed::sbe::v1_3
