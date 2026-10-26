#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/SummaryMessageType.hpp"
#include "../messages/ConsolidatedStartOfDaySummaryMessage.hpp"
#include "../messages/ParticipantStartOfDaySummaryMessage.hpp"
#include "../messages/ConsolidatedEndOfDaySummaryMessage.hpp"
#include "../messages/FractionalConsolidatedEndOfDaySummaryMessage.hpp"
#include "../messages/ParticipantEndOfDaySummaryMessage.hpp"
#include "../messages/FractionalParticipantEndOfDaySummaryMessage.hpp"

namespace siac::cts::output::cta::v2_11_b {

// Summary Category Summary Messages Are Used To Provide Cta Eligible Equity Local Issue And
// Bond Summary Information By Security
class SummaryMessage {
  public:
    static constexpr const char* name = "SummaryMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SummaryMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SummaryMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 1;
    std::size_t encoded_size() const { return summary_message_payload_end(); }

    SummaryMessageType summary_message_type() const { return static_cast<SummaryMessageType>(wire::read_char(at(0))); }

    // the bytes the message it selects is read from
    std::span<const std::byte> summary_message_payload_bytes() const {
        wire::require("SummaryMessage", 1, bytes_.size());
        return bytes_.subspan(1);
    }

    // the message its summary_message_type selects, handed to the handler as its view
    template <typename Handler>
    void summary_message_payload(Handler& handler) const {
        const auto bytes = summary_message_payload_bytes();
        switch (summary_message_type()) {
            case SummaryMessageType::ConsolidatedStartOfDaySummary: {
                wire::require(ConsolidatedStartOfDaySummaryMessage::name, ConsolidatedStartOfDaySummaryMessage::minimum_size, bytes.size());
                const ConsolidatedStartOfDaySummaryMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case SummaryMessageType::ParticipantStartOfDaySummary: {
                wire::require(ParticipantStartOfDaySummaryMessage::name, ParticipantStartOfDaySummaryMessage::minimum_size, bytes.size());
                const ParticipantStartOfDaySummaryMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case SummaryMessageType::ConsolidatedEndOfDaySummary: {
                wire::require(ConsolidatedEndOfDaySummaryMessage::name, ConsolidatedEndOfDaySummaryMessage::minimum_size, bytes.size());
                const ConsolidatedEndOfDaySummaryMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case SummaryMessageType::FractionalConsolidatedEndOfDaySummary: {
                wire::require(FractionalConsolidatedEndOfDaySummaryMessage::name, FractionalConsolidatedEndOfDaySummaryMessage::minimum_size, bytes.size());
                const FractionalConsolidatedEndOfDaySummaryMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case SummaryMessageType::ParticipantEndOfDaySummary: {
                wire::require(ParticipantEndOfDaySummaryMessage::name, ParticipantEndOfDaySummaryMessage::minimum_size, bytes.size());
                const ParticipantEndOfDaySummaryMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case SummaryMessageType::FractionalParticipantEndOfDaySummary: {
                wire::require(FractionalParticipantEndOfDaySummaryMessage::name, FractionalParticipantEndOfDaySummaryMessage::minimum_size, bytes.size());
                const FractionalParticipantEndOfDaySummaryMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            default:
                if constexpr (requires { handler.on_unknown(summary_message_type(), bytes); }) { handler.on_unknown(summary_message_type(), bytes); }
                return;
        }
    }

    // the bytes the message it selects takes
    std::size_t summary_message_payload_size() const {
        const auto bytes = summary_message_payload_bytes();
        switch (summary_message_type()) {
            case SummaryMessageType::ConsolidatedStartOfDaySummary: return ConsolidatedStartOfDaySummaryMessage{ bytes }.encoded_size();
            case SummaryMessageType::ParticipantStartOfDaySummary: return ParticipantStartOfDaySummaryMessage{ bytes }.encoded_size();
            case SummaryMessageType::ConsolidatedEndOfDaySummary: return ConsolidatedEndOfDaySummaryMessage{ bytes }.encoded_size();
            case SummaryMessageType::FractionalConsolidatedEndOfDaySummary: return FractionalConsolidatedEndOfDaySummaryMessage{ bytes }.encoded_size();
            case SummaryMessageType::ParticipantEndOfDaySummary: return ParticipantEndOfDaySummaryMessage{ bytes }.encoded_size();
            case SummaryMessageType::FractionalParticipantEndOfDaySummary: return FractionalParticipantEndOfDaySummaryMessage{ bytes }.encoded_size();
            default: return bytes.size();
        }
    }

    // the message it selects, printed; a code no message answers to prints its bytes
    void summary_message_payload_print(std::ostream& out) const {
        const auto bytes = summary_message_payload_bytes();
        switch (summary_message_type()) {
            case SummaryMessageType::ConsolidatedStartOfDaySummary: ConsolidatedStartOfDaySummaryMessage{ bytes }.print(out); return;
            case SummaryMessageType::ParticipantStartOfDaySummary: ParticipantStartOfDaySummaryMessage{ bytes }.print(out); return;
            case SummaryMessageType::ConsolidatedEndOfDaySummary: ConsolidatedEndOfDaySummaryMessage{ bytes }.print(out); return;
            case SummaryMessageType::FractionalConsolidatedEndOfDaySummary: FractionalConsolidatedEndOfDaySummaryMessage{ bytes }.print(out); return;
            case SummaryMessageType::ParticipantEndOfDaySummary: ParticipantEndOfDaySummaryMessage{ bytes }.print(out); return;
            case SummaryMessageType::FractionalParticipantEndOfDaySummary: FractionalParticipantEndOfDaySummaryMessage{ bytes }.print(out); return;
            default:
                out << "UnknownSummaryMessagePayload{type=" << summary_message_type() << ", body=";
                print::hex(out, bytes.data(), bytes.size());
                out << '}';
                return;
        }
    }

    void print(std::ostream& out) const {
        out << "SummaryMessage{";
        out << "summary_message_type=";
        out << summary_message_type();
        out << ", summary_message_payload=";
        summary_message_payload_print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t summary_message_payload_end() const { return 1 + summary_message_payload_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const SummaryMessage& value) {
    value.print(out);
    return out;
}

} // namespace siac::cts::output::cta::v2_11_b
