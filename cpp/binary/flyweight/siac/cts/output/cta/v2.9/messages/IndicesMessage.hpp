#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/IndicesMessageType.hpp"
#include "../messages/IndexMessage.hpp"
#include "../messages/BidAndOfferIndexMessage.hpp"

namespace siac::cts::output::cta::v2_9 {

// Index Messages Header
class IndicesMessage {
  public:
    static constexpr const char* name = "IndicesMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit IndicesMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every IndicesMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 1;
    std::size_t encoded_size() const { return indices_message_payload_end(); }

    IndicesMessageType indices_message_type() const { return static_cast<IndicesMessageType>(wire::read_char(at(0))); }

    // the bytes the message it selects is read from
    std::span<const std::byte> indices_message_payload_bytes() const {
        wire::require("IndicesMessage", 1, bytes_.size());
        return bytes_.subspan(1);
    }

    // the message its indices_message_type selects, handed to the handler as its view
    template <typename Handler>
    void indices_message_payload(Handler& handler) const {
        const auto bytes = indices_message_payload_bytes();
        switch (indices_message_type()) {
            case IndicesMessageType::IndexMessage: {
                wire::require(IndexMessage::name, IndexMessage::minimum_size, bytes.size());
                const IndexMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case IndicesMessageType::BidAndOfferIndexMessage: {
                wire::require(BidAndOfferIndexMessage::name, BidAndOfferIndexMessage::minimum_size, bytes.size());
                const BidAndOfferIndexMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            default:
                if constexpr (requires { handler.on_unknown(indices_message_type(), bytes); }) { handler.on_unknown(indices_message_type(), bytes); }
                return;
        }
    }

    // the bytes the message it selects takes
    std::size_t indices_message_payload_size() const {
        const auto bytes = indices_message_payload_bytes();
        switch (indices_message_type()) {
            case IndicesMessageType::IndexMessage: return IndexMessage{ bytes }.encoded_size();
            case IndicesMessageType::BidAndOfferIndexMessage: return BidAndOfferIndexMessage{ bytes }.encoded_size();
            default: return bytes.size();
        }
    }

    // the message it selects, printed; a code no message answers to prints its bytes
    void indices_message_payload_print(std::ostream& out) const {
        const auto bytes = indices_message_payload_bytes();
        switch (indices_message_type()) {
            case IndicesMessageType::IndexMessage: IndexMessage{ bytes }.print(out); return;
            case IndicesMessageType::BidAndOfferIndexMessage: BidAndOfferIndexMessage{ bytes }.print(out); return;
            default:
                out << "UnknownIndicesMessagePayload{type=" << indices_message_type() << ", body=";
                print::hex(out, bytes.data(), bytes.size());
                out << '}';
                return;
        }
    }

    void print(std::ostream& out) const {
        out << "IndicesMessage{";
        out << "indices_message_type=";
        out << indices_message_type();
        out << ", indices_message_payload=";
        indices_message_payload_print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t indices_message_payload_end() const { return 1 + indices_message_payload_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const IndicesMessage& value) {
    value.print(out);
    return out;
}

} // namespace siac::cts::output::cta::v2_9
