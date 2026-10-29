#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/ControlMessageType.hpp"
#include "../messages/StartOfDayMessage.hpp"
#include "../messages/ResetBlockSequenceNumberMessage.hpp"
#include "../messages/DisasterRecoveryDataCenterActivationMessage.hpp"
#include "../messages/LineIntegrityMessage.hpp"
#include "../messages/EndOfDayMessage.hpp"

namespace siac::cts::output::cta::v2_10 {

// Control Message Header
class ControlMessage {
  public:
    static constexpr const char* name = "ControlMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit ControlMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every ControlMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 1;
    std::size_t encoded_size() const { return control_message_payload_end(); }

    ControlMessageType control_message_type() const { return static_cast<ControlMessageType>(wire::read_char(at(0))); }

    // the bytes the message it selects is read from
    std::span<const std::byte> control_message_payload_bytes() const {
        wire::require("ControlMessage", 1, bytes_.size());
        return bytes_.subspan(1);
    }

    // the message its control_message_type selects, handed to the handler as its view
    template <typename Handler>
    void control_message_payload(Handler& handler) const {
        const auto bytes = control_message_payload_bytes();
        switch (control_message_type()) {
            case ControlMessageType::StartOfDayMessage: {
                wire::require(StartOfDayMessage::name, StartOfDayMessage::minimum_size, bytes.size());
                const StartOfDayMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case ControlMessageType::ResetBlockSequenceNumberMessage: {
                wire::require(ResetBlockSequenceNumberMessage::name, ResetBlockSequenceNumberMessage::minimum_size, bytes.size());
                const ResetBlockSequenceNumberMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case ControlMessageType::DisasterRecoveryDataCenterActivationMessage: {
                wire::require(DisasterRecoveryDataCenterActivationMessage::name, DisasterRecoveryDataCenterActivationMessage::minimum_size, bytes.size());
                const DisasterRecoveryDataCenterActivationMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case ControlMessageType::LineIntegrityMessage: {
                wire::require(LineIntegrityMessage::name, LineIntegrityMessage::minimum_size, bytes.size());
                const LineIntegrityMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case ControlMessageType::EndOfDayMessage: {
                wire::require(EndOfDayMessage::name, EndOfDayMessage::minimum_size, bytes.size());
                const EndOfDayMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            default:
                if constexpr (requires { handler.on_unknown(control_message_type(), bytes); }) { handler.on_unknown(control_message_type(), bytes); }
                return;
        }
    }

    // the bytes the message it selects takes
    std::size_t control_message_payload_size() const {
        const auto bytes = control_message_payload_bytes();
        switch (control_message_type()) {
            case ControlMessageType::StartOfDayMessage: return StartOfDayMessage{ bytes }.encoded_size();
            case ControlMessageType::ResetBlockSequenceNumberMessage: return ResetBlockSequenceNumberMessage{ bytes }.encoded_size();
            case ControlMessageType::DisasterRecoveryDataCenterActivationMessage: return DisasterRecoveryDataCenterActivationMessage{ bytes }.encoded_size();
            case ControlMessageType::LineIntegrityMessage: return LineIntegrityMessage{ bytes }.encoded_size();
            case ControlMessageType::EndOfDayMessage: return EndOfDayMessage{ bytes }.encoded_size();
            default: return bytes.size();
        }
    }

    // the message it selects, printed; a code no message answers to prints its bytes
    void control_message_payload_print(std::ostream& out) const {
        const auto bytes = control_message_payload_bytes();
        switch (control_message_type()) {
            case ControlMessageType::StartOfDayMessage: StartOfDayMessage{ bytes }.print(out); return;
            case ControlMessageType::ResetBlockSequenceNumberMessage: ResetBlockSequenceNumberMessage{ bytes }.print(out); return;
            case ControlMessageType::DisasterRecoveryDataCenterActivationMessage: DisasterRecoveryDataCenterActivationMessage{ bytes }.print(out); return;
            case ControlMessageType::LineIntegrityMessage: LineIntegrityMessage{ bytes }.print(out); return;
            case ControlMessageType::EndOfDayMessage: EndOfDayMessage{ bytes }.print(out); return;
            default:
                out << "UnknownControlMessagePayload{type=" << control_message_type() << ", body=";
                print::hex(out, bytes.data(), bytes.size());
                out << '}';
                return;
        }
    }

    void print(std::ostream& out) const {
        out << "ControlMessage{";
        out << "control_message_type=";
        out << control_message_type();
        out << ", control_message_payload=";
        control_message_payload_print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t control_message_payload_end() const { return 1 + control_message_payload_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const ControlMessage& value) {
    value.print(out);
    return out;
}

} // namespace siac::cts::output::cta::v2_10
