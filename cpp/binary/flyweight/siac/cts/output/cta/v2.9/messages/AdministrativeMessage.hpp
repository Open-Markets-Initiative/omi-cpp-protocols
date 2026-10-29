#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/AdministrativeMessageType.hpp"
#include "../messages/StartOfEndOfDayMessage.hpp"
#include "../messages/EndOfEndOfDayMessage.hpp"
#include "../messages/StartOfStartOfDayMessage.hpp"
#include "../messages/EndOfStartOfDayMessage.hpp"

namespace siac::cts::output::cta::v2_9 {

// Administrative Message Header
class AdministrativeMessage {
  public:
    static constexpr const char* name = "AdministrativeMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit AdministrativeMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every AdministrativeMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 1;
    std::size_t encoded_size() const { return administrative_message_payload_end(); }

    AdministrativeMessageType administrative_message_type() const { return static_cast<AdministrativeMessageType>(wire::read_char(at(0))); }

    // the bytes the message it selects is read from
    std::span<const std::byte> administrative_message_payload_bytes() const {
        wire::require("AdministrativeMessage", 1, bytes_.size());
        return bytes_.subspan(1);
    }

    // the message its administrative_message_type selects, handed to the handler as its view
    template <typename Handler>
    void administrative_message_payload(Handler& handler) const {
        const auto bytes = administrative_message_payload_bytes();
        switch (administrative_message_type()) {
            case AdministrativeMessageType::StartOfEndOfDayMessage: {
                wire::require(StartOfEndOfDayMessage::name, StartOfEndOfDayMessage::minimum_size, bytes.size());
                const StartOfEndOfDayMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case AdministrativeMessageType::EndOfEndOfDayMessage: {
                wire::require(EndOfEndOfDayMessage::name, EndOfEndOfDayMessage::minimum_size, bytes.size());
                const EndOfEndOfDayMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case AdministrativeMessageType::StartOfStartOfDayMessage: {
                wire::require(StartOfStartOfDayMessage::name, StartOfStartOfDayMessage::minimum_size, bytes.size());
                const StartOfStartOfDayMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case AdministrativeMessageType::EndOfStartOfDayMessage: {
                wire::require(EndOfStartOfDayMessage::name, EndOfStartOfDayMessage::minimum_size, bytes.size());
                const EndOfStartOfDayMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            default:
                if constexpr (requires { handler.on_unknown(administrative_message_type(), bytes); }) { handler.on_unknown(administrative_message_type(), bytes); }
                return;
        }
    }

    // the bytes the message it selects takes
    std::size_t administrative_message_payload_size() const {
        const auto bytes = administrative_message_payload_bytes();
        switch (administrative_message_type()) {
            case AdministrativeMessageType::StartOfEndOfDayMessage: return StartOfEndOfDayMessage{ bytes }.encoded_size();
            case AdministrativeMessageType::EndOfEndOfDayMessage: return EndOfEndOfDayMessage{ bytes }.encoded_size();
            case AdministrativeMessageType::StartOfStartOfDayMessage: return StartOfStartOfDayMessage{ bytes }.encoded_size();
            case AdministrativeMessageType::EndOfStartOfDayMessage: return EndOfStartOfDayMessage{ bytes }.encoded_size();
            default: return bytes.size();
        }
    }

    // the message it selects, printed; a code no message answers to prints its bytes
    void administrative_message_payload_print(std::ostream& out) const {
        const auto bytes = administrative_message_payload_bytes();
        switch (administrative_message_type()) {
            case AdministrativeMessageType::StartOfEndOfDayMessage: StartOfEndOfDayMessage{ bytes }.print(out); return;
            case AdministrativeMessageType::EndOfEndOfDayMessage: EndOfEndOfDayMessage{ bytes }.print(out); return;
            case AdministrativeMessageType::StartOfStartOfDayMessage: StartOfStartOfDayMessage{ bytes }.print(out); return;
            case AdministrativeMessageType::EndOfStartOfDayMessage: EndOfStartOfDayMessage{ bytes }.print(out); return;
            default:
                out << "UnknownAdministrativeMessagePayload{type=" << administrative_message_type() << ", body=";
                print::hex(out, bytes.data(), bytes.size());
                out << '}';
                return;
        }
    }

    void print(std::ostream& out) const {
        out << "AdministrativeMessage{";
        out << "administrative_message_type=";
        out << administrative_message_type();
        out << ", administrative_message_payload=";
        administrative_message_payload_print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t administrative_message_payload_end() const { return 1 + administrative_message_payload_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const AdministrativeMessage& value) {
    value.print(out);
    return out;
}

} // namespace siac::cts::output::cta::v2_9
