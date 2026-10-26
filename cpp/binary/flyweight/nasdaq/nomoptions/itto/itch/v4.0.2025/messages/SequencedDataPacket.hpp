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
#include "../messages/OptionsDirectoryMessage.hpp"
#include "../messages/TradingActionMessage.hpp"
#include "../messages/SecurityOpenMessage.hpp"
#include "../messages/AddOrderMessageShortMessageForm.hpp"
#include "../messages/AddOrderMessageLongFormMessage.hpp"
#include "../messages/AddQuoteMessageShortFormMessage.hpp"
#include "../messages/AddQuoteMessageLongFormMessage.hpp"
#include "../messages/SingleSideExecutedMessage.hpp"
#include "../messages/SingleSideExecutedWithPriceMessage.hpp"
#include "../messages/OrderCancelMessage.hpp"
#include "../messages/SingleSideReplaceMessageShortForm.hpp"
#include "../messages/SingleSideReplaceMessageLongForm.hpp"
#include "../messages/SingleSideDeleteMessage.hpp"
#include "../messages/SingleSideChangeMessage.hpp"
#include "../messages/QuoteReplaceMessageShortForm.hpp"
#include "../messages/QuoteReplaceMessageLongForm.hpp"
#include "../messages/QuoteDeleteMessage.hpp"
#include "../messages/OptionsTradeMessagesNonAuction.hpp"
#include "../messages/OptionsCrossTradeMessage.hpp"
#include "../messages/BrokenTradeOrderExecutedMessage.hpp"
#include "../messages/NoiiMessage.hpp"
#include "../messages/EndOfReplaySequenceMessage.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

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
            case SequencedMessageType::OptionsDirectoryMessage: {
                wire::require(OptionsDirectoryMessage::name, OptionsDirectoryMessage::minimum_size, bytes.size());
                const OptionsDirectoryMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case SequencedMessageType::TradingActionMessage: {
                wire::require(TradingActionMessage::name, TradingActionMessage::minimum_size, bytes.size());
                const TradingActionMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case SequencedMessageType::SecurityOpenMessage: {
                wire::require(SecurityOpenMessage::name, SecurityOpenMessage::minimum_size, bytes.size());
                const SecurityOpenMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case SequencedMessageType::AddOrderMessageShortMessageForm: {
                wire::require(AddOrderMessageShortMessageForm::name, AddOrderMessageShortMessageForm::minimum_size, bytes.size());
                const AddOrderMessageShortMessageForm message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case SequencedMessageType::AddOrderMessageLongFormMessage: {
                wire::require(AddOrderMessageLongFormMessage::name, AddOrderMessageLongFormMessage::minimum_size, bytes.size());
                const AddOrderMessageLongFormMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case SequencedMessageType::AddQuoteMessageShortFormMessage: {
                wire::require(AddQuoteMessageShortFormMessage::name, AddQuoteMessageShortFormMessage::minimum_size, bytes.size());
                const AddQuoteMessageShortFormMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case SequencedMessageType::AddQuoteMessageLongFormMessage: {
                wire::require(AddQuoteMessageLongFormMessage::name, AddQuoteMessageLongFormMessage::minimum_size, bytes.size());
                const AddQuoteMessageLongFormMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case SequencedMessageType::SingleSideExecutedMessage: {
                wire::require(SingleSideExecutedMessage::name, SingleSideExecutedMessage::minimum_size, bytes.size());
                const SingleSideExecutedMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case SequencedMessageType::SingleSideExecutedWithPriceMessage: {
                wire::require(SingleSideExecutedWithPriceMessage::name, SingleSideExecutedWithPriceMessage::minimum_size, bytes.size());
                const SingleSideExecutedWithPriceMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case SequencedMessageType::OrderCancelMessage: {
                wire::require(OrderCancelMessage::name, OrderCancelMessage::minimum_size, bytes.size());
                const OrderCancelMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case SequencedMessageType::SingleSideReplaceMessageShortForm: {
                wire::require(SingleSideReplaceMessageShortForm::name, SingleSideReplaceMessageShortForm::minimum_size, bytes.size());
                const SingleSideReplaceMessageShortForm message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case SequencedMessageType::SingleSideReplaceMessageLongForm: {
                wire::require(SingleSideReplaceMessageLongForm::name, SingleSideReplaceMessageLongForm::minimum_size, bytes.size());
                const SingleSideReplaceMessageLongForm message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case SequencedMessageType::SingleSideDeleteMessage: {
                wire::require(SingleSideDeleteMessage::name, SingleSideDeleteMessage::minimum_size, bytes.size());
                const SingleSideDeleteMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case SequencedMessageType::SingleSideChangeMessage: {
                wire::require(SingleSideChangeMessage::name, SingleSideChangeMessage::minimum_size, bytes.size());
                const SingleSideChangeMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case SequencedMessageType::QuoteReplaceMessageShortForm: {
                wire::require(QuoteReplaceMessageShortForm::name, QuoteReplaceMessageShortForm::minimum_size, bytes.size());
                const QuoteReplaceMessageShortForm message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case SequencedMessageType::QuoteReplaceMessageLongForm: {
                wire::require(QuoteReplaceMessageLongForm::name, QuoteReplaceMessageLongForm::minimum_size, bytes.size());
                const QuoteReplaceMessageLongForm message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case SequencedMessageType::QuoteDeleteMessage: {
                wire::require(QuoteDeleteMessage::name, QuoteDeleteMessage::minimum_size, bytes.size());
                const QuoteDeleteMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case SequencedMessageType::OptionsTradeMessagesNonAuction: {
                wire::require(OptionsTradeMessagesNonAuction::name, OptionsTradeMessagesNonAuction::minimum_size, bytes.size());
                const OptionsTradeMessagesNonAuction message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case SequencedMessageType::OptionsCrossTradeMessage: {
                wire::require(OptionsCrossTradeMessage::name, OptionsCrossTradeMessage::minimum_size, bytes.size());
                const OptionsCrossTradeMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case SequencedMessageType::BrokenTradeOrderExecutedMessage: {
                wire::require(BrokenTradeOrderExecutedMessage::name, BrokenTradeOrderExecutedMessage::minimum_size, bytes.size());
                const BrokenTradeOrderExecutedMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case SequencedMessageType::NoiiMessage: {
                wire::require(NoiiMessage::name, NoiiMessage::minimum_size, bytes.size());
                const NoiiMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case SequencedMessageType::EndOfReplaySequenceMessage: {
                wire::require(EndOfReplaySequenceMessage::name, EndOfReplaySequenceMessage::minimum_size, bytes.size());
                const EndOfReplaySequenceMessage message{ bytes };
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
            case SequencedMessageType::OptionsDirectoryMessage: return OptionsDirectoryMessage{ bytes }.encoded_size();
            case SequencedMessageType::TradingActionMessage: return TradingActionMessage{ bytes }.encoded_size();
            case SequencedMessageType::SecurityOpenMessage: return SecurityOpenMessage{ bytes }.encoded_size();
            case SequencedMessageType::AddOrderMessageShortMessageForm: return AddOrderMessageShortMessageForm{ bytes }.encoded_size();
            case SequencedMessageType::AddOrderMessageLongFormMessage: return AddOrderMessageLongFormMessage{ bytes }.encoded_size();
            case SequencedMessageType::AddQuoteMessageShortFormMessage: return AddQuoteMessageShortFormMessage{ bytes }.encoded_size();
            case SequencedMessageType::AddQuoteMessageLongFormMessage: return AddQuoteMessageLongFormMessage{ bytes }.encoded_size();
            case SequencedMessageType::SingleSideExecutedMessage: return SingleSideExecutedMessage{ bytes }.encoded_size();
            case SequencedMessageType::SingleSideExecutedWithPriceMessage: return SingleSideExecutedWithPriceMessage{ bytes }.encoded_size();
            case SequencedMessageType::OrderCancelMessage: return OrderCancelMessage{ bytes }.encoded_size();
            case SequencedMessageType::SingleSideReplaceMessageShortForm: return SingleSideReplaceMessageShortForm{ bytes }.encoded_size();
            case SequencedMessageType::SingleSideReplaceMessageLongForm: return SingleSideReplaceMessageLongForm{ bytes }.encoded_size();
            case SequencedMessageType::SingleSideDeleteMessage: return SingleSideDeleteMessage{ bytes }.encoded_size();
            case SequencedMessageType::SingleSideChangeMessage: return SingleSideChangeMessage{ bytes }.encoded_size();
            case SequencedMessageType::QuoteReplaceMessageShortForm: return QuoteReplaceMessageShortForm{ bytes }.encoded_size();
            case SequencedMessageType::QuoteReplaceMessageLongForm: return QuoteReplaceMessageLongForm{ bytes }.encoded_size();
            case SequencedMessageType::QuoteDeleteMessage: return QuoteDeleteMessage{ bytes }.encoded_size();
            case SequencedMessageType::OptionsTradeMessagesNonAuction: return OptionsTradeMessagesNonAuction{ bytes }.encoded_size();
            case SequencedMessageType::OptionsCrossTradeMessage: return OptionsCrossTradeMessage{ bytes }.encoded_size();
            case SequencedMessageType::BrokenTradeOrderExecutedMessage: return BrokenTradeOrderExecutedMessage{ bytes }.encoded_size();
            case SequencedMessageType::NoiiMessage: return NoiiMessage{ bytes }.encoded_size();
            case SequencedMessageType::EndOfReplaySequenceMessage: return EndOfReplaySequenceMessage{ bytes }.encoded_size();
            default: return bytes.size();
        }
    }

    // the message it selects, printed; a code no message answers to prints its bytes
    void sequenced_message_print(std::ostream& out) const {
        const auto bytes = sequenced_message_bytes();
        switch (sequenced_message_type()) {
            case SequencedMessageType::SystemEventMessage: SystemEventMessage{ bytes }.print(out); return;
            case SequencedMessageType::OptionsDirectoryMessage: OptionsDirectoryMessage{ bytes }.print(out); return;
            case SequencedMessageType::TradingActionMessage: TradingActionMessage{ bytes }.print(out); return;
            case SequencedMessageType::SecurityOpenMessage: SecurityOpenMessage{ bytes }.print(out); return;
            case SequencedMessageType::AddOrderMessageShortMessageForm: AddOrderMessageShortMessageForm{ bytes }.print(out); return;
            case SequencedMessageType::AddOrderMessageLongFormMessage: AddOrderMessageLongFormMessage{ bytes }.print(out); return;
            case SequencedMessageType::AddQuoteMessageShortFormMessage: AddQuoteMessageShortFormMessage{ bytes }.print(out); return;
            case SequencedMessageType::AddQuoteMessageLongFormMessage: AddQuoteMessageLongFormMessage{ bytes }.print(out); return;
            case SequencedMessageType::SingleSideExecutedMessage: SingleSideExecutedMessage{ bytes }.print(out); return;
            case SequencedMessageType::SingleSideExecutedWithPriceMessage: SingleSideExecutedWithPriceMessage{ bytes }.print(out); return;
            case SequencedMessageType::OrderCancelMessage: OrderCancelMessage{ bytes }.print(out); return;
            case SequencedMessageType::SingleSideReplaceMessageShortForm: SingleSideReplaceMessageShortForm{ bytes }.print(out); return;
            case SequencedMessageType::SingleSideReplaceMessageLongForm: SingleSideReplaceMessageLongForm{ bytes }.print(out); return;
            case SequencedMessageType::SingleSideDeleteMessage: SingleSideDeleteMessage{ bytes }.print(out); return;
            case SequencedMessageType::SingleSideChangeMessage: SingleSideChangeMessage{ bytes }.print(out); return;
            case SequencedMessageType::QuoteReplaceMessageShortForm: QuoteReplaceMessageShortForm{ bytes }.print(out); return;
            case SequencedMessageType::QuoteReplaceMessageLongForm: QuoteReplaceMessageLongForm{ bytes }.print(out); return;
            case SequencedMessageType::QuoteDeleteMessage: QuoteDeleteMessage{ bytes }.print(out); return;
            case SequencedMessageType::OptionsTradeMessagesNonAuction: OptionsTradeMessagesNonAuction{ bytes }.print(out); return;
            case SequencedMessageType::OptionsCrossTradeMessage: OptionsCrossTradeMessage{ bytes }.print(out); return;
            case SequencedMessageType::BrokenTradeOrderExecutedMessage: BrokenTradeOrderExecutedMessage{ bytes }.print(out); return;
            case SequencedMessageType::NoiiMessage: NoiiMessage{ bytes }.print(out); return;
            case SequencedMessageType::EndOfReplaySequenceMessage: EndOfReplaySequenceMessage{ bytes }.print(out); return;
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

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
