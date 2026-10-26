#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/OpenInterestMessageType.hpp"
#include "../messages/OpenInterestMessage.hpp"

namespace siac::opra::output::obi::v6_2 {

// Open Interest Message
class OpenInterestCategory {
  public:
    static constexpr const char* name = "OpenInterestCategory";

    // the bytes it reads, which it does not own: they must outlive it
    explicit OpenInterestCategory(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every OpenInterestCategory has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 1;
    std::size_t encoded_size() const { return open_interest_message_payload_end(); }

    OpenInterestMessageType open_interest_message_type() const { return static_cast<OpenInterestMessageType>(wire::read_char(at(0))); }

    // the bytes the message it selects is read from
    std::span<const std::byte> open_interest_message_payload_bytes() const {
        wire::require("OpenInterestCategory", 1, bytes_.size());
        return bytes_.subspan(1);
    }

    // the message its open_interest_message_type selects, handed to the handler as its view
    template <typename Handler>
    void open_interest_message_payload(Handler& handler) const {
        const auto bytes = open_interest_message_payload_bytes();
        switch (open_interest_message_type()) {
            case OpenInterestMessageType::OpenInterest: {
                wire::require(OpenInterestMessage::name, OpenInterestMessage::minimum_size, bytes.size());
                const OpenInterestMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            default:
                if constexpr (requires { handler.on_unknown(open_interest_message_type(), bytes); }) { handler.on_unknown(open_interest_message_type(), bytes); }
                return;
        }
    }

    // the bytes the message it selects takes
    std::size_t open_interest_message_payload_size() const {
        const auto bytes = open_interest_message_payload_bytes();
        switch (open_interest_message_type()) {
            case OpenInterestMessageType::OpenInterest: return OpenInterestMessage{ bytes }.encoded_size();
            default: return bytes.size();
        }
    }

    // the message it selects, printed; a code no message answers to prints its bytes
    void open_interest_message_payload_print(std::ostream& out) const {
        const auto bytes = open_interest_message_payload_bytes();
        switch (open_interest_message_type()) {
            case OpenInterestMessageType::OpenInterest: OpenInterestMessage{ bytes }.print(out); return;
            default:
                out << "UnknownOpenInterestMessagePayload{type=" << open_interest_message_type() << ", body=";
                print::hex(out, bytes.data(), bytes.size());
                out << '}';
                return;
        }
    }

    void print(std::ostream& out) const {
        out << "OpenInterestCategory{";
        out << "open_interest_message_type=";
        out << open_interest_message_type();
        out << ", open_interest_message_payload=";
        open_interest_message_payload_print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t open_interest_message_payload_end() const { return 1 + open_interest_message_payload_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const OpenInterestCategory& value) {
    value.print(out);
    return out;
}

} // namespace siac::opra::output::obi::v6_2
