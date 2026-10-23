#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/EquityAndIndexLastSaleMessageType.hpp"
#include "../messages/EquityAndIndexLastSaleMessage.hpp"

namespace siac::opra::output::obi::v6_2 {

// Equity And Index Last Sale Message
class EquityAndIndexLastSaleCategory {
  public:
    static constexpr const char* name = "EquityAndIndexLastSaleCategory";

    // the bytes it reads, which it does not own: they must outlive it
    explicit EquityAndIndexLastSaleCategory(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every EquityAndIndexLastSaleCategory has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 1;
    std::size_t encoded_size() const { return equity_and_index_last_sale_message_payload_end(); }

    EquityAndIndexLastSaleMessageType equity_and_index_last_sale_message_type() const { return static_cast<EquityAndIndexLastSaleMessageType>(wire::read_char(at(0))); }

    // the bytes the message it selects is read from
    std::span<const std::byte> equity_and_index_last_sale_message_payload_bytes() const {
        wire::require("EquityAndIndexLastSaleCategory", 1, bytes_.size());
        return bytes_.subspan(1);
    }

    // the message its equity_and_index_last_sale_message_type selects, handed to the handler as its view
    template <typename Handler>
    void equity_and_index_last_sale_message_payload(Handler& handler) const {
        const auto bytes = equity_and_index_last_sale_message_payload_bytes();
        switch (equity_and_index_last_sale_message_type()) {
            case EquityAndIndexLastSaleMessageType::Canc: {
                wire::require(EquityAndIndexLastSaleMessage::name, EquityAndIndexLastSaleMessage::minimum_size, bytes.size());
                const EquityAndIndexLastSaleMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            default:
                if constexpr (requires { handler.on_unknown(equity_and_index_last_sale_message_type(), bytes); }) { handler.on_unknown(equity_and_index_last_sale_message_type(), bytes); }
                return;
        }
    }

    // the bytes the message it selects takes
    std::size_t equity_and_index_last_sale_message_payload_size() const {
        const auto bytes = equity_and_index_last_sale_message_payload_bytes();
        switch (equity_and_index_last_sale_message_type()) {
            case EquityAndIndexLastSaleMessageType::Canc: return EquityAndIndexLastSaleMessage{ bytes }.encoded_size();
            default: return bytes.size();
        }
    }

    // the message it selects, printed; a code no message answers to prints its bytes
    void equity_and_index_last_sale_message_payload_print(std::ostream& out) const {
        const auto bytes = equity_and_index_last_sale_message_payload_bytes();
        switch (equity_and_index_last_sale_message_type()) {
            case EquityAndIndexLastSaleMessageType::Canc: EquityAndIndexLastSaleMessage{ bytes }.print(out); return;
            default:
                out << "UnknownEquityAndIndexLastSaleMessagePayload{type=" << equity_and_index_last_sale_message_type() << ", body=";
                print::hex(out, bytes.data(), bytes.size());
                out << '}';
                return;
        }
    }

    void print(std::ostream& out) const {
        out << "EquityAndIndexLastSaleCategory{";
        out << "equity_and_index_last_sale_message_type=";
        out << equity_and_index_last_sale_message_type();
        out << ", equity_and_index_last_sale_message_payload=";
        equity_and_index_last_sale_message_payload_print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t equity_and_index_last_sale_message_payload_end() const { return 1 + equity_and_index_last_sale_message_payload_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const EquityAndIndexLastSaleCategory& value) {
    value.print(out);
    return out;
}

} // namespace siac::opra::output::obi::v6_2
