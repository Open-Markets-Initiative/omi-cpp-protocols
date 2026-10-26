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
#include "../enums/InstrumentType.hpp"
#include "../common/Decimal.hpp"
#include "../enums/Tick.hpp"

namespace siac::cts::output::cta::v2_11_b {

// Provides by security, the Participant Open, High, Low, Last, Volume and Tick information for
// CTA eligible securities, Local Issues and Bonds. Volume is represented as a fractional value
class FractionalParticipantEndOfDaySummaryMessage {
  public:
    static constexpr const char* name = "FractionalParticipantEndOfDaySummaryMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit FractionalParticipantEndOfDaySummaryMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every FractionalParticipantEndOfDaySummaryMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 80;
    static constexpr std::size_t fixed_size = 80;
    std::size_t encoded_size() const { return 80; }

    ParticipantId participant_id() const { return static_cast<ParticipantId>(wire::read_char(at(0))); }

    Timestamp1 timestamp_1() const { return Timestamp1{ bytes_.subspan(1) }; }

    std::uint8_t message_id() const { return wire::read_u8(at(9)); }

    std::uint32_t transaction_id() const { return wire::read_u32_be(at(10)); }

    std::int64_t participant_reference_number() const { return wire::read_i64_be(at(14)); }

    std::string_view security_symbol() const { return view::text(at(22), 11, ' '); }

    InstrumentType instrument_type() const { return static_cast<InstrumentType>(wire::read_char(at(33))); }

    char summary_participant_id() const { return wire::read_char(at(34)); }

    std::uint32_t previous_close_price_date() const { return wire::read_u32_be(at(35)); }

    Decimal last_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_be(at(39))), -6); }

    Decimal high_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_be(at(47))), -6); }

    Decimal low_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_be(at(55))), -6); }

    Decimal open_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_be(at(63))), -6); }

    Decimal fractional_total_volume() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_be(at(71))), -6); }

    Tick tick() const { return static_cast<Tick>(wire::read_char(at(79))); }

    void print(std::ostream& out) const {
        out << "FractionalParticipantEndOfDaySummaryMessage{";
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
        out << ", security_symbol=";
        print::text(out, security_symbol());
        out << ", instrument_type=";
        out << instrument_type();
        out << ", summary_participant_id=";
        print::character(out, summary_participant_id());
        out << ", previous_close_price_date=";
        out << previous_close_price_date();
        out << ", last_price=";
        out << last_price();
        out << ", high_price=";
        out << high_price();
        out << ", low_price=";
        out << low_price();
        out << ", open_price=";
        out << open_price();
        out << ", fractional_total_volume=";
        out << fractional_total_volume();
        out << ", tick=";
        out << tick();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const FractionalParticipantEndOfDaySummaryMessage& value) {
    value.print(out);
    return out;
}

} // namespace siac::cts::output::cta::v2_11_b
