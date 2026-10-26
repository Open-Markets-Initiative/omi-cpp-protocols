#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../bitfields/AllowedBookTypes.hpp"
#include "../enums/SourceVenue.hpp"
#include "../common/Decimal.hpp"

namespace lseg::lse::level2mbo::gtp::v26_2 {

// Used to disseminate a common and limited set of data for all configured instrument types,
// except strategy instruments, on the real-time channels.
class InstrumentDirectoryMessage {
  public:
    static constexpr const char* name = "InstrumentDirectoryMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit InstrumentDirectoryMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every InstrumentDirectoryMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 138;
    static constexpr std::size_t fixed_size = 138;
    std::size_t encoded_size() const { return 138; }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(at(0)))); }

    std::uint64_t instrument() const { return wire::read_u64_le(at(8)); }

    std::string_view isin() const { return view::text(at(16), 12, ' '); }

    AllowedBookTypes allowed_book_types() const { return AllowedBookTypes{ bytes_.subspan(28) }; }

    SourceVenue source_venue() const { return static_cast<SourceVenue>(wire::read_u16_le(at(29))); }

    std::string_view venue_instrument_id() const { return view::text(at(31), 11, ' '); }

    std::string_view tick_id() const { return view::text(at(42), 2, ' '); }

    std::span<const std::byte, 8> reserved_8() const { return bytes_.subspan(44).template first<8>(); }

    Decimal dynamic_circuit_breaker_tolerances() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_le(at(52))), -8); }

    Decimal static_circuit_breaker_tolerances() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_le(at(60))), -8); }

    std::string_view segment() const { return view::text(at(68), 6, ' '); }

    std::span<const std::byte, 12> reserved_12() const { return bytes_.subspan(74).template first<12>(); }

    std::span<const std::byte, 11> reserved_11() const { return bytes_.subspan(86).template first<11>(); }

    std::string_view currency() const { return view::text(at(97), 3, ' '); }

    char partition_id() const { return wire::read_char(at(100)); }

    std::span<const std::byte, 4> reserved_4() const { return bytes_.subspan(101).template first<4>(); }

    Decimal average_daily_turnover_adt() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_le(at(105))), -4); }

    std::span<const std::byte, 8> second_reserved_8() const { return bytes_.subspan(113).template first<8>(); }

    std::span<const std::byte, 1> reserved_1() const { return bytes_.subspan(121).template first<1>(); }

    std::span<const std::byte, 8> third_reserved_8() const { return bytes_.subspan(122).template first<8>(); }

    std::span<const std::byte, 8> fourth_reserved_8() const { return bytes_.subspan(130).template first<8>(); }

    void print(std::ostream& out) const {
        out << "InstrumentDirectoryMessage{";
        out << "timestamp=";
        out << timestamp().count();
        out << ", instrument=";
        out << instrument();
        out << ", isin=";
        print::text(out, isin());
        out << ", allowed_book_types=";
        allowed_book_types().print(out);
        out << ", source_venue=";
        out << source_venue();
        out << ", venue_instrument_id=";
        print::text(out, venue_instrument_id());
        out << ", tick_id=";
        print::text(out, tick_id());
        out << ", reserved_8=";
        print::hex(out, reserved_8().data(), reserved_8().size());
        out << ", dynamic_circuit_breaker_tolerances=";
        out << dynamic_circuit_breaker_tolerances();
        out << ", static_circuit_breaker_tolerances=";
        out << static_circuit_breaker_tolerances();
        out << ", segment=";
        print::text(out, segment());
        out << ", reserved_12=";
        print::hex(out, reserved_12().data(), reserved_12().size());
        out << ", reserved_11=";
        print::hex(out, reserved_11().data(), reserved_11().size());
        out << ", currency=";
        print::text(out, currency());
        out << ", partition_id=";
        print::character(out, partition_id());
        out << ", reserved_4=";
        print::hex(out, reserved_4().data(), reserved_4().size());
        out << ", average_daily_turnover_adt=";
        out << average_daily_turnover_adt();
        out << ", second_reserved_8=";
        print::hex(out, second_reserved_8().data(), second_reserved_8().size());
        out << ", reserved_1=";
        print::hex(out, reserved_1().data(), reserved_1().size());
        out << ", third_reserved_8=";
        print::hex(out, third_reserved_8().data(), third_reserved_8().size());
        out << ", fourth_reserved_8=";
        print::hex(out, fourth_reserved_8().data(), fourth_reserved_8().size());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const InstrumentDirectoryMessage& value) {
    value.print(out);
    return out;
}

} // namespace lseg::lse::level2mbo::gtp::v26_2
