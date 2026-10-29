#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/ParticipantId.hpp"
#include "../structs/Timestamp1.hpp"

namespace siac::cts::output::cta::v1_91 {

// The Disaster Recovery Data Center Activation message is transmitted to signify that the
// Consolidated Quotation System (CQS) has switched processing from the Primary Data Center to
// the Disaster Recovery Data Center
class DisasterRecoveryDataCenterActivationMessage {
  public:
    static constexpr const char* name = "DisasterRecoveryDataCenterActivationMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit DisasterRecoveryDataCenterActivationMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every DisasterRecoveryDataCenterActivationMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 22;
    static constexpr std::size_t fixed_size = 22;
    std::size_t encoded_size() const { return 22; }

    ParticipantId participant_id() const { return static_cast<ParticipantId>(wire::read_char(at(0))); }

    Timestamp1 timestamp_1() const { return Timestamp1{ bytes_.subspan(1) }; }

    std::uint8_t message_id() const { return wire::read_u8(at(9)); }

    std::uint32_t transaction_id() const { return wire::read_u32_be(at(10)); }

    std::int64_t participant_reference_number() const { return wire::read_i64_be(at(14)); }

    void print(std::ostream& out) const {
        out << "DisasterRecoveryDataCenterActivationMessage{";
        out << "participant_id=";
        out << participant_id();
        out << ", timestamp_1=";
        timestamp_1().print(out);
        out << ", message_id=";
        out << static_cast<int>(message_id());
        out << ", transaction_id=";
        out << transaction_id();
        out << ", participant_reference_number=";
        out << participant_reference_number();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const DisasterRecoveryDataCenterActivationMessage& value) {
    value.print(out);
    return out;
}

} // namespace siac::cts::output::cta::v1_91
