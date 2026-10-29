#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/ParticipantId.hpp"
#include "../structs/Timestamp1.hpp"

namespace siac::cts::output::cta::v1_91 {

// The Administrative Unformatted (free form text) Category A message is designed to facilitate
// non-computerized miscellaneous information messages to CQS
class AdministrativeUnformattedMessage {
  public:
    static constexpr const char* name = "AdministrativeUnformattedMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit AdministrativeUnformattedMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every AdministrativeUnformattedMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 26;
    static constexpr std::size_t fixed_size = 26;
    std::size_t encoded_size() const { return 26; }

    ParticipantId participant_id() const { return static_cast<ParticipantId>(wire::read_char(at(0))); }

    Timestamp1 timestamp_1() const { return Timestamp1{ bytes_.subspan(1) }; }

    std::uint8_t message_id() const { return wire::read_u8(at(9)); }

    std::uint32_t transaction_id() const { return wire::read_u32_be(at(10)); }

    std::int64_t participant_reference_number() const { return wire::read_i64_be(at(14)); }

    std::string_view text() const { return view::text(at(22), 4, ' '); }

    void print(std::ostream& out) const {
        out << "AdministrativeUnformattedMessage{";
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
        out << ", text=";
        print::text(out, text());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const AdministrativeUnformattedMessage& value) {
    value.print(out);
    return out;
}

} // namespace siac::cts::output::cta::v1_91
