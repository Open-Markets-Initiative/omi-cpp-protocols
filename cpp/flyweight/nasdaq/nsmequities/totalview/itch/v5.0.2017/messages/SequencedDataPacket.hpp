#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../messages/SystemEventMessage.hpp"
#include "../messages/StockDirectoryMessage.hpp"
#include "../messages/StockTradingActionMessage.hpp"
#include "../messages/RegShoShortSalePriceTestRestrictedIndicatorMessage.hpp"
#include "../messages/MarketParticipantPositionMessage.hpp"
#include "../messages/MwcbDeclineLevelMessage.hpp"
#include "../messages/MwcbStatusLevelMessage.hpp"
#include "../messages/IpoQuotingPeriodUpdate.hpp"
#include "../messages/LuldAuctionCollarMessage.hpp"
#include "../messages/AddOrderNoMpidAttributionMessage.hpp"
#include "../messages/AddOrderWithMpidAttributionMessage.hpp"
#include "../messages/OrderExecutedMessage.hpp"
#include "../messages/OrderExecutedWithPriceMessage.hpp"
#include "../messages/OrderCancelMessage.hpp"
#include "../messages/OrderDeleteMessage.hpp"
#include "../messages/OrderReplaceMessage.hpp"
#include "../messages/NonCrossTradeMessage.hpp"
#include "../messages/CrossTradeMessage.hpp"
#include "../messages/BrokenTradeMessage.hpp"
#include "../messages/NetOrderImbalanceIndicatorMessage.hpp"
#include "../messages/RetailInterestMessage.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2017 {

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

    char sequenced_message_type() const { return wire::read_char(at(0)); }

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
            case 'S': {
                wire::require(SystemEventMessage::name, SystemEventMessage::minimum_size, bytes.size());
                const SystemEventMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case 'R': {
                wire::require(StockDirectoryMessage::name, StockDirectoryMessage::minimum_size, bytes.size());
                const StockDirectoryMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case 'H': {
                wire::require(StockTradingActionMessage::name, StockTradingActionMessage::minimum_size, bytes.size());
                const StockTradingActionMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case 'Y': {
                wire::require(RegShoShortSalePriceTestRestrictedIndicatorMessage::name, RegShoShortSalePriceTestRestrictedIndicatorMessage::minimum_size, bytes.size());
                const RegShoShortSalePriceTestRestrictedIndicatorMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case 'L': {
                wire::require(MarketParticipantPositionMessage::name, MarketParticipantPositionMessage::minimum_size, bytes.size());
                const MarketParticipantPositionMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case 'V': {
                wire::require(MwcbDeclineLevelMessage::name, MwcbDeclineLevelMessage::minimum_size, bytes.size());
                const MwcbDeclineLevelMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case 'W': {
                wire::require(MwcbStatusLevelMessage::name, MwcbStatusLevelMessage::minimum_size, bytes.size());
                const MwcbStatusLevelMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case 'K': {
                wire::require(IpoQuotingPeriodUpdate::name, IpoQuotingPeriodUpdate::minimum_size, bytes.size());
                const IpoQuotingPeriodUpdate message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case 'J': {
                wire::require(LuldAuctionCollarMessage::name, LuldAuctionCollarMessage::minimum_size, bytes.size());
                const LuldAuctionCollarMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case 'A': {
                wire::require(AddOrderNoMpidAttributionMessage::name, AddOrderNoMpidAttributionMessage::minimum_size, bytes.size());
                const AddOrderNoMpidAttributionMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case 'F': {
                wire::require(AddOrderWithMpidAttributionMessage::name, AddOrderWithMpidAttributionMessage::minimum_size, bytes.size());
                const AddOrderWithMpidAttributionMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case 'E': {
                wire::require(OrderExecutedMessage::name, OrderExecutedMessage::minimum_size, bytes.size());
                const OrderExecutedMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case 'C': {
                wire::require(OrderExecutedWithPriceMessage::name, OrderExecutedWithPriceMessage::minimum_size, bytes.size());
                const OrderExecutedWithPriceMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case 'X': {
                wire::require(OrderCancelMessage::name, OrderCancelMessage::minimum_size, bytes.size());
                const OrderCancelMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case 'D': {
                wire::require(OrderDeleteMessage::name, OrderDeleteMessage::minimum_size, bytes.size());
                const OrderDeleteMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case 'U': {
                wire::require(OrderReplaceMessage::name, OrderReplaceMessage::minimum_size, bytes.size());
                const OrderReplaceMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case 'P': {
                wire::require(NonCrossTradeMessage::name, NonCrossTradeMessage::minimum_size, bytes.size());
                const NonCrossTradeMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case 'Q': {
                wire::require(CrossTradeMessage::name, CrossTradeMessage::minimum_size, bytes.size());
                const CrossTradeMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case 'B': {
                wire::require(BrokenTradeMessage::name, BrokenTradeMessage::minimum_size, bytes.size());
                const BrokenTradeMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case 'I': {
                wire::require(NetOrderImbalanceIndicatorMessage::name, NetOrderImbalanceIndicatorMessage::minimum_size, bytes.size());
                const NetOrderImbalanceIndicatorMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case 'N': {
                wire::require(RetailInterestMessage::name, RetailInterestMessage::minimum_size, bytes.size());
                const RetailInterestMessage message{ bytes };
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
            case 'S': return SystemEventMessage{ bytes }.encoded_size();
            case 'R': return StockDirectoryMessage{ bytes }.encoded_size();
            case 'H': return StockTradingActionMessage{ bytes }.encoded_size();
            case 'Y': return RegShoShortSalePriceTestRestrictedIndicatorMessage{ bytes }.encoded_size();
            case 'L': return MarketParticipantPositionMessage{ bytes }.encoded_size();
            case 'V': return MwcbDeclineLevelMessage{ bytes }.encoded_size();
            case 'W': return MwcbStatusLevelMessage{ bytes }.encoded_size();
            case 'K': return IpoQuotingPeriodUpdate{ bytes }.encoded_size();
            case 'J': return LuldAuctionCollarMessage{ bytes }.encoded_size();
            case 'A': return AddOrderNoMpidAttributionMessage{ bytes }.encoded_size();
            case 'F': return AddOrderWithMpidAttributionMessage{ bytes }.encoded_size();
            case 'E': return OrderExecutedMessage{ bytes }.encoded_size();
            case 'C': return OrderExecutedWithPriceMessage{ bytes }.encoded_size();
            case 'X': return OrderCancelMessage{ bytes }.encoded_size();
            case 'D': return OrderDeleteMessage{ bytes }.encoded_size();
            case 'U': return OrderReplaceMessage{ bytes }.encoded_size();
            case 'P': return NonCrossTradeMessage{ bytes }.encoded_size();
            case 'Q': return CrossTradeMessage{ bytes }.encoded_size();
            case 'B': return BrokenTradeMessage{ bytes }.encoded_size();
            case 'I': return NetOrderImbalanceIndicatorMessage{ bytes }.encoded_size();
            case 'N': return RetailInterestMessage{ bytes }.encoded_size();
            default: return bytes.size();
        }
    }

    // the message it selects, printed; a code no message answers to prints its bytes
    void sequenced_message_print(std::ostream& out) const {
        const auto bytes = sequenced_message_bytes();
        switch (sequenced_message_type()) {
            case 'S': SystemEventMessage{ bytes }.print(out); return;
            case 'R': StockDirectoryMessage{ bytes }.print(out); return;
            case 'H': StockTradingActionMessage{ bytes }.print(out); return;
            case 'Y': RegShoShortSalePriceTestRestrictedIndicatorMessage{ bytes }.print(out); return;
            case 'L': MarketParticipantPositionMessage{ bytes }.print(out); return;
            case 'V': MwcbDeclineLevelMessage{ bytes }.print(out); return;
            case 'W': MwcbStatusLevelMessage{ bytes }.print(out); return;
            case 'K': IpoQuotingPeriodUpdate{ bytes }.print(out); return;
            case 'J': LuldAuctionCollarMessage{ bytes }.print(out); return;
            case 'A': AddOrderNoMpidAttributionMessage{ bytes }.print(out); return;
            case 'F': AddOrderWithMpidAttributionMessage{ bytes }.print(out); return;
            case 'E': OrderExecutedMessage{ bytes }.print(out); return;
            case 'C': OrderExecutedWithPriceMessage{ bytes }.print(out); return;
            case 'X': OrderCancelMessage{ bytes }.print(out); return;
            case 'D': OrderDeleteMessage{ bytes }.print(out); return;
            case 'U': OrderReplaceMessage{ bytes }.print(out); return;
            case 'P': NonCrossTradeMessage{ bytes }.print(out); return;
            case 'Q': CrossTradeMessage{ bytes }.print(out); return;
            case 'B': BrokenTradeMessage{ bytes }.print(out); return;
            case 'I': NetOrderImbalanceIndicatorMessage{ bytes }.print(out); return;
            case 'N': RetailInterestMessage{ bytes }.print(out); return;
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
        print::character(out, sequenced_message_type());
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

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2017
