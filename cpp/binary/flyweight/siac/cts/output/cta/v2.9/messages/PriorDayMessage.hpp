#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/PriorDayMessageType.hpp"
#include "../messages/PriorDayTradeCorrectionMessage.hpp"
#include "../messages/PriorDayTradeMessage.hpp"
#include "../messages/PriorDayTradeCancelErrorMessage.hpp"

namespace siac::cts::output::cta::v2_9 {

// Prior Day Messages
class PriorDayMessage {
  public:
    static constexpr const char* name = "PriorDayMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit PriorDayMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every PriorDayMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 1;
    std::size_t encoded_size() const { return prior_day_message_payload_end(); }

    PriorDayMessageType prior_day_message_type() const { return static_cast<PriorDayMessageType>(wire::read_char(at(0))); }

    // the bytes the message it selects is read from
    std::span<const std::byte> prior_day_message_payload_bytes() const {
        wire::require("PriorDayMessage", 1, bytes_.size());
        return bytes_.subspan(1);
    }

    // the message its prior_day_message_type selects, handed to the handler as its view
    template <typename Handler>
    void prior_day_message_payload(Handler& handler) const {
        const auto bytes = prior_day_message_payload_bytes();
        switch (prior_day_message_type()) {
            case PriorDayMessageType::PriorDayTradeCorrectionMessage: {
                wire::require(PriorDayTradeCorrectionMessage::name, PriorDayTradeCorrectionMessage::minimum_size, bytes.size());
                const PriorDayTradeCorrectionMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case PriorDayMessageType::PriorDayTradeMessage: {
                wire::require(PriorDayTradeMessage::name, PriorDayTradeMessage::minimum_size, bytes.size());
                const PriorDayTradeMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case PriorDayMessageType::PriorDayTradeCancelErrorMessage: {
                wire::require(PriorDayTradeCancelErrorMessage::name, PriorDayTradeCancelErrorMessage::minimum_size, bytes.size());
                const PriorDayTradeCancelErrorMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            default:
                if constexpr (requires { handler.on_unknown(prior_day_message_type(), bytes); }) { handler.on_unknown(prior_day_message_type(), bytes); }
                return;
        }
    }

    // the bytes the message it selects takes
    std::size_t prior_day_message_payload_size() const {
        const auto bytes = prior_day_message_payload_bytes();
        switch (prior_day_message_type()) {
            case PriorDayMessageType::PriorDayTradeCorrectionMessage: return PriorDayTradeCorrectionMessage{ bytes }.encoded_size();
            case PriorDayMessageType::PriorDayTradeMessage: return PriorDayTradeMessage{ bytes }.encoded_size();
            case PriorDayMessageType::PriorDayTradeCancelErrorMessage: return PriorDayTradeCancelErrorMessage{ bytes }.encoded_size();
            default: return bytes.size();
        }
    }

    // the message it selects, printed; a code no message answers to prints its bytes
    void prior_day_message_payload_print(std::ostream& out) const {
        const auto bytes = prior_day_message_payload_bytes();
        switch (prior_day_message_type()) {
            case PriorDayMessageType::PriorDayTradeCorrectionMessage: PriorDayTradeCorrectionMessage{ bytes }.print(out); return;
            case PriorDayMessageType::PriorDayTradeMessage: PriorDayTradeMessage{ bytes }.print(out); return;
            case PriorDayMessageType::PriorDayTradeCancelErrorMessage: PriorDayTradeCancelErrorMessage{ bytes }.print(out); return;
            default:
                out << "UnknownPriorDayMessagePayload{type=" << prior_day_message_type() << ", body=";
                print::hex(out, bytes.data(), bytes.size());
                out << '}';
                return;
        }
    }

    void print(std::ostream& out) const {
        out << "PriorDayMessage{";
        out << "prior_day_message_type=";
        out << prior_day_message_type();
        out << ", prior_day_message_payload=";
        prior_day_message_payload_print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t prior_day_message_payload_end() const { return 1 + prior_day_message_payload_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const PriorDayMessage& value) {
    value.print(out);
    return out;
}

} // namespace siac::cts::output::cta::v2_9
