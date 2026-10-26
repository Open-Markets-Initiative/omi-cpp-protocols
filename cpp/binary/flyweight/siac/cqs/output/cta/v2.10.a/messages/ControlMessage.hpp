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
#include "../messages/FinraCloseMessage.hpp"
#include "../messages/ResetBlockSequenceNumberMessage.hpp"
#include "../messages/FinraOpenMessage.hpp"
#include "../messages/DisasterRecoveryDataCenterActivationMessage.hpp"
#include "../messages/LineIntegrityMessage.hpp"
#include "../messages/EndOfDayMessage.hpp"

namespace siac::cqs::output::cta::v2_10_a {

// Control Category
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
            case ControlMessageType::StartOfDay: {
                wire::require(StartOfDayMessage::name, StartOfDayMessage::minimum_size, bytes.size());
                const StartOfDayMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case ControlMessageType::FinraClose: {
                wire::require(FinraCloseMessage::name, FinraCloseMessage::minimum_size, bytes.size());
                const FinraCloseMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case ControlMessageType::ResetBlockSequenceNumber: {
                wire::require(ResetBlockSequenceNumberMessage::name, ResetBlockSequenceNumberMessage::minimum_size, bytes.size());
                const ResetBlockSequenceNumberMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case ControlMessageType::FinraOpen: {
                wire::require(FinraOpenMessage::name, FinraOpenMessage::minimum_size, bytes.size());
                const FinraOpenMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case ControlMessageType::DisasterRecoveryDataCenterActivation: {
                wire::require(DisasterRecoveryDataCenterActivationMessage::name, DisasterRecoveryDataCenterActivationMessage::minimum_size, bytes.size());
                const DisasterRecoveryDataCenterActivationMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case ControlMessageType::LineIntegrity: {
                wire::require(LineIntegrityMessage::name, LineIntegrityMessage::minimum_size, bytes.size());
                const LineIntegrityMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case ControlMessageType::EndOfDay: {
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
            case ControlMessageType::StartOfDay: return StartOfDayMessage{ bytes }.encoded_size();
            case ControlMessageType::FinraClose: return FinraCloseMessage{ bytes }.encoded_size();
            case ControlMessageType::ResetBlockSequenceNumber: return ResetBlockSequenceNumberMessage{ bytes }.encoded_size();
            case ControlMessageType::FinraOpen: return FinraOpenMessage{ bytes }.encoded_size();
            case ControlMessageType::DisasterRecoveryDataCenterActivation: return DisasterRecoveryDataCenterActivationMessage{ bytes }.encoded_size();
            case ControlMessageType::LineIntegrity: return LineIntegrityMessage{ bytes }.encoded_size();
            case ControlMessageType::EndOfDay: return EndOfDayMessage{ bytes }.encoded_size();
            default: return bytes.size();
        }
    }

    // the message it selects, printed; a code no message answers to prints its bytes
    void control_message_payload_print(std::ostream& out) const {
        const auto bytes = control_message_payload_bytes();
        switch (control_message_type()) {
            case ControlMessageType::StartOfDay: StartOfDayMessage{ bytes }.print(out); return;
            case ControlMessageType::FinraClose: FinraCloseMessage{ bytes }.print(out); return;
            case ControlMessageType::ResetBlockSequenceNumber: ResetBlockSequenceNumberMessage{ bytes }.print(out); return;
            case ControlMessageType::FinraOpen: FinraOpenMessage{ bytes }.print(out); return;
            case ControlMessageType::DisasterRecoveryDataCenterActivation: DisasterRecoveryDataCenterActivationMessage{ bytes }.print(out); return;
            case ControlMessageType::LineIntegrity: LineIntegrityMessage{ bytes }.print(out); return;
            case ControlMessageType::EndOfDay: EndOfDayMessage{ bytes }.print(out); return;
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

} // namespace siac::cqs::output::cta::v2_10_a
