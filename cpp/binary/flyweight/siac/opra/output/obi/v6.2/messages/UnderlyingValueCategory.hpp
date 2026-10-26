#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/UnderlyingValueMessageType.hpp"
#include "../messages/UnderlyingValueLastSaleMessage.hpp"
#include "../messages/UnderlyingValueBidAndOfferMessage.hpp"

namespace siac::opra::output::obi::v6_2 {

// Underlying Value Message
class UnderlyingValueCategory {
  public:
    static constexpr const char* name = "UnderlyingValueCategory";

    // the bytes it reads, which it does not own: they must outlive it
    explicit UnderlyingValueCategory(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every UnderlyingValueCategory has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 1;
    std::size_t encoded_size() const { return underlying_value_message_payload_end(); }

    UnderlyingValueMessageType underlying_value_message_type() const { return static_cast<UnderlyingValueMessageType>(wire::read_char(at(0))); }

    // the bytes the message it selects is read from
    std::span<const std::byte> underlying_value_message_payload_bytes() const {
        wire::require("UnderlyingValueCategory", 1, bytes_.size());
        return bytes_.subspan(1);
    }

    // the message its underlying_value_message_type selects, handed to the handler as its view
    template <typename Handler>
    void underlying_value_message_payload(Handler& handler) const {
        const auto bytes = underlying_value_message_payload_bytes();
        switch (underlying_value_message_type()) {
            case UnderlyingValueMessageType::IndexBasedOnLastSale: {
                wire::require(UnderlyingValueLastSaleMessage::name, UnderlyingValueLastSaleMessage::minimum_size, bytes.size());
                const UnderlyingValueLastSaleMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case UnderlyingValueMessageType::IndexBasedOnBidAndOffer: {
                wire::require(UnderlyingValueBidAndOfferMessage::name, UnderlyingValueBidAndOfferMessage::minimum_size, bytes.size());
                const UnderlyingValueBidAndOfferMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            default:
                if constexpr (requires { handler.on_unknown(underlying_value_message_type(), bytes); }) { handler.on_unknown(underlying_value_message_type(), bytes); }
                return;
        }
    }

    // the bytes the message it selects takes
    std::size_t underlying_value_message_payload_size() const {
        const auto bytes = underlying_value_message_payload_bytes();
        switch (underlying_value_message_type()) {
            case UnderlyingValueMessageType::IndexBasedOnLastSale: return UnderlyingValueLastSaleMessage{ bytes }.encoded_size();
            case UnderlyingValueMessageType::IndexBasedOnBidAndOffer: return UnderlyingValueBidAndOfferMessage{ bytes }.encoded_size();
            default: return bytes.size();
        }
    }

    // the message it selects, printed; a code no message answers to prints its bytes
    void underlying_value_message_payload_print(std::ostream& out) const {
        const auto bytes = underlying_value_message_payload_bytes();
        switch (underlying_value_message_type()) {
            case UnderlyingValueMessageType::IndexBasedOnLastSale: UnderlyingValueLastSaleMessage{ bytes }.print(out); return;
            case UnderlyingValueMessageType::IndexBasedOnBidAndOffer: UnderlyingValueBidAndOfferMessage{ bytes }.print(out); return;
            default:
                out << "UnknownUnderlyingValueMessagePayload{type=" << underlying_value_message_type() << ", body=";
                print::hex(out, bytes.data(), bytes.size());
                out << '}';
                return;
        }
    }

    void print(std::ostream& out) const {
        out << "UnderlyingValueCategory{";
        out << "underlying_value_message_type=";
        out << underlying_value_message_type();
        out << ", underlying_value_message_payload=";
        underlying_value_message_payload_print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t underlying_value_message_payload_end() const { return 1 + underlying_value_message_payload_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const UnderlyingValueCategory& value) {
    value.print(out);
    return out;
}

} // namespace siac::opra::output::obi::v6_2
