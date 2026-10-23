#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/ShortEquityAndIndexQuoteMessageType.hpp"
#include "../messages/ShortEquityAndIndexQuoteMessage.hpp"

namespace siac::opra::output::obi::v6_2 {

// Short Equity And Index Quote Message
class ShortEquityAndIndexQuoteCategory {
  public:
    static constexpr const char* name = "ShortEquityAndIndexQuoteCategory";

    // the bytes it reads, which it does not own: they must outlive it
    explicit ShortEquityAndIndexQuoteCategory(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every ShortEquityAndIndexQuoteCategory has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 1;
    std::size_t encoded_size() const { return short_equity_and_index_quote_message_payload_end(); }

    ShortEquityAndIndexQuoteMessageType short_equity_and_index_quote_message_type() const { return static_cast<ShortEquityAndIndexQuoteMessageType>(wire::read_char(at(0))); }

    // the bytes the message it selects is read from
    std::span<const std::byte> short_equity_and_index_quote_message_payload_bytes() const {
        wire::require("ShortEquityAndIndexQuoteCategory", 1, bytes_.size());
        return bytes_.subspan(1);
    }

    // the message its short_equity_and_index_quote_message_type selects, handed to the handler as its view
    template <typename Handler>
    void short_equity_and_index_quote_message_payload(Handler& handler) const {
        const auto bytes = short_equity_and_index_quote_message_payload_bytes();
        switch (short_equity_and_index_quote_message_type()) {
            case ShortEquityAndIndexQuoteMessageType::RegularTrading: {
                wire::require(ShortEquityAndIndexQuoteMessage::name, ShortEquityAndIndexQuoteMessage::minimum_size, bytes.size());
                const ShortEquityAndIndexQuoteMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            default:
                if constexpr (requires { handler.on_unknown(short_equity_and_index_quote_message_type(), bytes); }) { handler.on_unknown(short_equity_and_index_quote_message_type(), bytes); }
                return;
        }
    }

    // the bytes the message it selects takes
    std::size_t short_equity_and_index_quote_message_payload_size() const {
        const auto bytes = short_equity_and_index_quote_message_payload_bytes();
        switch (short_equity_and_index_quote_message_type()) {
            case ShortEquityAndIndexQuoteMessageType::RegularTrading: return ShortEquityAndIndexQuoteMessage{ bytes }.encoded_size();
            default: return bytes.size();
        }
    }

    // the message it selects, printed; a code no message answers to prints its bytes
    void short_equity_and_index_quote_message_payload_print(std::ostream& out) const {
        const auto bytes = short_equity_and_index_quote_message_payload_bytes();
        switch (short_equity_and_index_quote_message_type()) {
            case ShortEquityAndIndexQuoteMessageType::RegularTrading: ShortEquityAndIndexQuoteMessage{ bytes }.print(out); return;
            default:
                out << "UnknownShortEquityAndIndexQuoteMessagePayload{type=" << short_equity_and_index_quote_message_type() << ", body=";
                print::hex(out, bytes.data(), bytes.size());
                out << '}';
                return;
        }
    }

    void print(std::ostream& out) const {
        out << "ShortEquityAndIndexQuoteCategory{";
        out << "short_equity_and_index_quote_message_type=";
        out << short_equity_and_index_quote_message_type();
        out << ", short_equity_and_index_quote_message_payload=";
        short_equity_and_index_quote_message_payload_print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t short_equity_and_index_quote_message_payload_end() const { return 1 + short_equity_and_index_quote_message_payload_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const ShortEquityAndIndexQuoteCategory& value) {
    value.print(out);
    return out;
}

} // namespace siac::opra::output::obi::v6_2
