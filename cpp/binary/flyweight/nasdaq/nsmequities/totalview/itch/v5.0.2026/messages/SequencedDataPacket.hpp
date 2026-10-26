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
#include "../messages/StockDirectoryMessage.hpp"
#include "../messages/StockTradingActionMessage.hpp"
#include "../messages/RegShoShortSalePriceTestRestrictedIndicatorMessage.hpp"
#include "../messages/MarketParticipantPositionMessage.hpp"
#include "../messages/MwcbDeclineLevelMessage.hpp"
#include "../messages/MwcbStatusLevelMessage.hpp"
#include "../messages/IpoQuotingPeriodUpdate.hpp"
#include "../messages/LuldAuctionCollarMessage.hpp"
#include "../messages/OperationalHaltMessage.hpp"
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
#include "../messages/RetailPriceImprovementIndicatorMessage.hpp"
#include "../messages/DirectListingWithCapitalRaisePriceDiscoveryMessage.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2026 {

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
            case SequencedMessageType::StockDirectoryMessage: {
                wire::require(StockDirectoryMessage::name, StockDirectoryMessage::minimum_size, bytes.size());
                const StockDirectoryMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case SequencedMessageType::StockTradingActionMessage: {
                wire::require(StockTradingActionMessage::name, StockTradingActionMessage::minimum_size, bytes.size());
                const StockTradingActionMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case SequencedMessageType::RegShoShortSalePriceTestRestrictedIndicatorMessage: {
                wire::require(RegShoShortSalePriceTestRestrictedIndicatorMessage::name, RegShoShortSalePriceTestRestrictedIndicatorMessage::minimum_size, bytes.size());
                const RegShoShortSalePriceTestRestrictedIndicatorMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case SequencedMessageType::MarketParticipantPositionMessage: {
                wire::require(MarketParticipantPositionMessage::name, MarketParticipantPositionMessage::minimum_size, bytes.size());
                const MarketParticipantPositionMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case SequencedMessageType::MwcbDeclineLevelMessage: {
                wire::require(MwcbDeclineLevelMessage::name, MwcbDeclineLevelMessage::minimum_size, bytes.size());
                const MwcbDeclineLevelMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case SequencedMessageType::MwcbStatusLevelMessage: {
                wire::require(MwcbStatusLevelMessage::name, MwcbStatusLevelMessage::minimum_size, bytes.size());
                const MwcbStatusLevelMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case SequencedMessageType::IpoQuotingPeriodUpdate: {
                wire::require(IpoQuotingPeriodUpdate::name, IpoQuotingPeriodUpdate::minimum_size, bytes.size());
                const IpoQuotingPeriodUpdate message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case SequencedMessageType::LuldAuctionCollarMessage: {
                wire::require(LuldAuctionCollarMessage::name, LuldAuctionCollarMessage::minimum_size, bytes.size());
                const LuldAuctionCollarMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case SequencedMessageType::OperationalHaltMessage: {
                wire::require(OperationalHaltMessage::name, OperationalHaltMessage::minimum_size, bytes.size());
                const OperationalHaltMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case SequencedMessageType::AddOrderNoMpidAttributionMessage: {
                wire::require(AddOrderNoMpidAttributionMessage::name, AddOrderNoMpidAttributionMessage::minimum_size, bytes.size());
                const AddOrderNoMpidAttributionMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case SequencedMessageType::AddOrderWithMpidAttributionMessage: {
                wire::require(AddOrderWithMpidAttributionMessage::name, AddOrderWithMpidAttributionMessage::minimum_size, bytes.size());
                const AddOrderWithMpidAttributionMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case SequencedMessageType::OrderExecutedMessage: {
                wire::require(OrderExecutedMessage::name, OrderExecutedMessage::minimum_size, bytes.size());
                const OrderExecutedMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case SequencedMessageType::OrderExecutedWithPriceMessage: {
                wire::require(OrderExecutedWithPriceMessage::name, OrderExecutedWithPriceMessage::minimum_size, bytes.size());
                const OrderExecutedWithPriceMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case SequencedMessageType::OrderCancelMessage: {
                wire::require(OrderCancelMessage::name, OrderCancelMessage::minimum_size, bytes.size());
                const OrderCancelMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case SequencedMessageType::OrderDeleteMessage: {
                wire::require(OrderDeleteMessage::name, OrderDeleteMessage::minimum_size, bytes.size());
                const OrderDeleteMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case SequencedMessageType::OrderReplaceMessage: {
                wire::require(OrderReplaceMessage::name, OrderReplaceMessage::minimum_size, bytes.size());
                const OrderReplaceMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case SequencedMessageType::NonCrossTradeMessage: {
                wire::require(NonCrossTradeMessage::name, NonCrossTradeMessage::minimum_size, bytes.size());
                const NonCrossTradeMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case SequencedMessageType::CrossTradeMessage: {
                wire::require(CrossTradeMessage::name, CrossTradeMessage::minimum_size, bytes.size());
                const CrossTradeMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case SequencedMessageType::BrokenTradeMessage: {
                wire::require(BrokenTradeMessage::name, BrokenTradeMessage::minimum_size, bytes.size());
                const BrokenTradeMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case SequencedMessageType::NetOrderImbalanceIndicatorMessage: {
                wire::require(NetOrderImbalanceIndicatorMessage::name, NetOrderImbalanceIndicatorMessage::minimum_size, bytes.size());
                const NetOrderImbalanceIndicatorMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case SequencedMessageType::RetailPriceImprovementIndicatorMessage: {
                wire::require(RetailPriceImprovementIndicatorMessage::name, RetailPriceImprovementIndicatorMessage::minimum_size, bytes.size());
                const RetailPriceImprovementIndicatorMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case SequencedMessageType::DirectListingWithCapitalRaisePriceDiscoveryMessage: {
                wire::require(DirectListingWithCapitalRaisePriceDiscoveryMessage::name, DirectListingWithCapitalRaisePriceDiscoveryMessage::minimum_size, bytes.size());
                const DirectListingWithCapitalRaisePriceDiscoveryMessage message{ bytes };
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
            case SequencedMessageType::StockDirectoryMessage: return StockDirectoryMessage{ bytes }.encoded_size();
            case SequencedMessageType::StockTradingActionMessage: return StockTradingActionMessage{ bytes }.encoded_size();
            case SequencedMessageType::RegShoShortSalePriceTestRestrictedIndicatorMessage: return RegShoShortSalePriceTestRestrictedIndicatorMessage{ bytes }.encoded_size();
            case SequencedMessageType::MarketParticipantPositionMessage: return MarketParticipantPositionMessage{ bytes }.encoded_size();
            case SequencedMessageType::MwcbDeclineLevelMessage: return MwcbDeclineLevelMessage{ bytes }.encoded_size();
            case SequencedMessageType::MwcbStatusLevelMessage: return MwcbStatusLevelMessage{ bytes }.encoded_size();
            case SequencedMessageType::IpoQuotingPeriodUpdate: return IpoQuotingPeriodUpdate{ bytes }.encoded_size();
            case SequencedMessageType::LuldAuctionCollarMessage: return LuldAuctionCollarMessage{ bytes }.encoded_size();
            case SequencedMessageType::OperationalHaltMessage: return OperationalHaltMessage{ bytes }.encoded_size();
            case SequencedMessageType::AddOrderNoMpidAttributionMessage: return AddOrderNoMpidAttributionMessage{ bytes }.encoded_size();
            case SequencedMessageType::AddOrderWithMpidAttributionMessage: return AddOrderWithMpidAttributionMessage{ bytes }.encoded_size();
            case SequencedMessageType::OrderExecutedMessage: return OrderExecutedMessage{ bytes }.encoded_size();
            case SequencedMessageType::OrderExecutedWithPriceMessage: return OrderExecutedWithPriceMessage{ bytes }.encoded_size();
            case SequencedMessageType::OrderCancelMessage: return OrderCancelMessage{ bytes }.encoded_size();
            case SequencedMessageType::OrderDeleteMessage: return OrderDeleteMessage{ bytes }.encoded_size();
            case SequencedMessageType::OrderReplaceMessage: return OrderReplaceMessage{ bytes }.encoded_size();
            case SequencedMessageType::NonCrossTradeMessage: return NonCrossTradeMessage{ bytes }.encoded_size();
            case SequencedMessageType::CrossTradeMessage: return CrossTradeMessage{ bytes }.encoded_size();
            case SequencedMessageType::BrokenTradeMessage: return BrokenTradeMessage{ bytes }.encoded_size();
            case SequencedMessageType::NetOrderImbalanceIndicatorMessage: return NetOrderImbalanceIndicatorMessage{ bytes }.encoded_size();
            case SequencedMessageType::RetailPriceImprovementIndicatorMessage: return RetailPriceImprovementIndicatorMessage{ bytes }.encoded_size();
            case SequencedMessageType::DirectListingWithCapitalRaisePriceDiscoveryMessage: return DirectListingWithCapitalRaisePriceDiscoveryMessage{ bytes }.encoded_size();
            default: return bytes.size();
        }
    }

    // the message it selects, printed; a code no message answers to prints its bytes
    void sequenced_message_print(std::ostream& out) const {
        const auto bytes = sequenced_message_bytes();
        switch (sequenced_message_type()) {
            case SequencedMessageType::SystemEventMessage: SystemEventMessage{ bytes }.print(out); return;
            case SequencedMessageType::StockDirectoryMessage: StockDirectoryMessage{ bytes }.print(out); return;
            case SequencedMessageType::StockTradingActionMessage: StockTradingActionMessage{ bytes }.print(out); return;
            case SequencedMessageType::RegShoShortSalePriceTestRestrictedIndicatorMessage: RegShoShortSalePriceTestRestrictedIndicatorMessage{ bytes }.print(out); return;
            case SequencedMessageType::MarketParticipantPositionMessage: MarketParticipantPositionMessage{ bytes }.print(out); return;
            case SequencedMessageType::MwcbDeclineLevelMessage: MwcbDeclineLevelMessage{ bytes }.print(out); return;
            case SequencedMessageType::MwcbStatusLevelMessage: MwcbStatusLevelMessage{ bytes }.print(out); return;
            case SequencedMessageType::IpoQuotingPeriodUpdate: IpoQuotingPeriodUpdate{ bytes }.print(out); return;
            case SequencedMessageType::LuldAuctionCollarMessage: LuldAuctionCollarMessage{ bytes }.print(out); return;
            case SequencedMessageType::OperationalHaltMessage: OperationalHaltMessage{ bytes }.print(out); return;
            case SequencedMessageType::AddOrderNoMpidAttributionMessage: AddOrderNoMpidAttributionMessage{ bytes }.print(out); return;
            case SequencedMessageType::AddOrderWithMpidAttributionMessage: AddOrderWithMpidAttributionMessage{ bytes }.print(out); return;
            case SequencedMessageType::OrderExecutedMessage: OrderExecutedMessage{ bytes }.print(out); return;
            case SequencedMessageType::OrderExecutedWithPriceMessage: OrderExecutedWithPriceMessage{ bytes }.print(out); return;
            case SequencedMessageType::OrderCancelMessage: OrderCancelMessage{ bytes }.print(out); return;
            case SequencedMessageType::OrderDeleteMessage: OrderDeleteMessage{ bytes }.print(out); return;
            case SequencedMessageType::OrderReplaceMessage: OrderReplaceMessage{ bytes }.print(out); return;
            case SequencedMessageType::NonCrossTradeMessage: NonCrossTradeMessage{ bytes }.print(out); return;
            case SequencedMessageType::CrossTradeMessage: CrossTradeMessage{ bytes }.print(out); return;
            case SequencedMessageType::BrokenTradeMessage: BrokenTradeMessage{ bytes }.print(out); return;
            case SequencedMessageType::NetOrderImbalanceIndicatorMessage: NetOrderImbalanceIndicatorMessage{ bytes }.print(out); return;
            case SequencedMessageType::RetailPriceImprovementIndicatorMessage: RetailPriceImprovementIndicatorMessage{ bytes }.print(out); return;
            case SequencedMessageType::DirectListingWithCapitalRaisePriceDiscoveryMessage: DirectListingWithCapitalRaisePriceDiscoveryMessage{ bytes }.print(out); return;
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

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2026
