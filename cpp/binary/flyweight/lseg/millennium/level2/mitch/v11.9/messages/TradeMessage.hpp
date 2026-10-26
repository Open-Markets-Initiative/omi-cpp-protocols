#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/CrossType.hpp"
#include "../enums/SubBook.hpp"
#include "../bitfields/PtModFlags.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

// Sent if a non-display order is fully or partially filled.
class TradeMessage {
  public:
    static constexpr const char* name = "TradeMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit TradeMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every TradeMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 33;
    static constexpr std::size_t fixed_size = 33;
    std::size_t encoded_size() const { return 33; }

    std::uint32_t nanosecond() const { return wire::read_u32_le(at(0)); }

    std::uint32_t executed_quantity() const { return wire::read_u32_le(at(4)); }

    std::uint32_t instrument_id() const { return wire::read_u32_le(at(8)); }

    std::span<const std::byte, 1> reserved_a() const { return bytes_.subspan(12).template first<1>(); }

    std::span<const std::byte, 1> reserved_b() const { return bytes_.subspan(13).template first<1>(); }

    std::int64_t price() const { return wire::read_i64_le(at(14)); }

    std::uint64_t trade_match_id() const { return wire::read_u64_le(at(22)); }

    std::optional<CrossType> cross_type() const { return wire::nullable_enum<CrossType>(wire::read_u8(at(30)), static_cast<std::uint8_t>(0ULL)); }

    SubBook sub_book() const { return static_cast<SubBook>(wire::read_u8(at(31))); }

    PtModFlags pt_mod_flags() const { return PtModFlags{ bytes_.subspan(32) }; }

    void print(std::ostream& out) const {
        out << "TradeMessage{";
        out << "nanosecond=";
        out << nanosecond();
        out << ", executed_quantity=";
        out << executed_quantity();
        out << ", instrument_id=";
        out << instrument_id();
        out << ", reserved_a=";
        print::hex(out, reserved_a().data(), reserved_a().size());
        out << ", reserved_b=";
        print::hex(out, reserved_b().data(), reserved_b().size());
        out << ", price=";
        out << price();
        out << ", trade_match_id=";
        out << trade_match_id();
        out << ", cross_type=";
        print::optional(out, cross_type());
        out << ", sub_book=";
        out << sub_book();
        out << ", pt_mod_flags=";
        pt_mod_flags().print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const TradeMessage& value) {
    value.print(out);
    return out;
}

} // namespace lseg::millennium::level2::mitch::v11_9
