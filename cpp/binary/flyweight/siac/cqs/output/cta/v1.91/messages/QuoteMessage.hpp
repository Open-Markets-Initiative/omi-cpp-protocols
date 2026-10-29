#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/QuoteMessageType.hpp"
#include "../messages/AuctionStatusMessage.hpp"
#include "../messages/LongQuoteMessage.hpp"
#include "../messages/ShortQuoteMessage.hpp"
#include "../messages/SpecialLongQuoteMessage.hpp"

namespace siac::cqs::output::cta::v1_91 {

// Quote Messages
class QuoteMessage {
  public:
    static constexpr const char* name = "QuoteMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit QuoteMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every QuoteMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 1;
    std::size_t encoded_size() const { return quote_message_payload_end(); }

    QuoteMessageType quote_message_type() const { return static_cast<QuoteMessageType>(wire::read_char(at(0))); }

    // the bytes the message it selects is read from
    std::span<const std::byte> quote_message_payload_bytes() const {
        wire::require("QuoteMessage", 1, bytes_.size());
        return bytes_.subspan(1);
    }

    // the message its quote_message_type selects, handed to the handler as its view
    template <typename Handler>
    void quote_message_payload(Handler& handler) const {
        const auto bytes = quote_message_payload_bytes();
        switch (quote_message_type()) {
            case QuoteMessageType::AuctionStatusMessage: {
                wire::require(AuctionStatusMessage::name, AuctionStatusMessage::minimum_size, bytes.size());
                const AuctionStatusMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case QuoteMessageType::LongQuoteMessage: {
                wire::require(LongQuoteMessage::name, LongQuoteMessage::minimum_size, bytes.size());
                const LongQuoteMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case QuoteMessageType::ShortQuoteMessage: {
                wire::require(ShortQuoteMessage::name, ShortQuoteMessage::minimum_size, bytes.size());
                const ShortQuoteMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case QuoteMessageType::SpecialLongQuoteMessage: {
                wire::require(SpecialLongQuoteMessage::name, SpecialLongQuoteMessage::minimum_size, bytes.size());
                const SpecialLongQuoteMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            default:
                if constexpr (requires { handler.on_unknown(quote_message_type(), bytes); }) { handler.on_unknown(quote_message_type(), bytes); }
                return;
        }
    }

    // the bytes the message it selects takes
    std::size_t quote_message_payload_size() const {
        const auto bytes = quote_message_payload_bytes();
        switch (quote_message_type()) {
            case QuoteMessageType::AuctionStatusMessage: return AuctionStatusMessage{ bytes }.encoded_size();
            case QuoteMessageType::LongQuoteMessage: return LongQuoteMessage{ bytes }.encoded_size();
            case QuoteMessageType::ShortQuoteMessage: return ShortQuoteMessage{ bytes }.encoded_size();
            case QuoteMessageType::SpecialLongQuoteMessage: return SpecialLongQuoteMessage{ bytes }.encoded_size();
            default: return bytes.size();
        }
    }

    // the message it selects, printed; a code no message answers to prints its bytes
    void quote_message_payload_print(std::ostream& out) const {
        const auto bytes = quote_message_payload_bytes();
        switch (quote_message_type()) {
            case QuoteMessageType::AuctionStatusMessage: AuctionStatusMessage{ bytes }.print(out); return;
            case QuoteMessageType::LongQuoteMessage: LongQuoteMessage{ bytes }.print(out); return;
            case QuoteMessageType::ShortQuoteMessage: ShortQuoteMessage{ bytes }.print(out); return;
            case QuoteMessageType::SpecialLongQuoteMessage: SpecialLongQuoteMessage{ bytes }.print(out); return;
            default:
                out << "UnknownQuoteMessagePayload{type=" << quote_message_type() << ", body=";
                print::hex(out, bytes.data(), bytes.size());
                out << '}';
                return;
        }
    }

    void print(std::ostream& out) const {
        out << "QuoteMessage{";
        out << "quote_message_type=";
        out << quote_message_type();
        out << ", quote_message_payload=";
        quote_message_payload_print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t quote_message_payload_end() const { return 1 + quote_message_payload_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const QuoteMessage& value) {
    value.print(out);
    return out;
}

} // namespace siac::cqs::output::cta::v1_91
