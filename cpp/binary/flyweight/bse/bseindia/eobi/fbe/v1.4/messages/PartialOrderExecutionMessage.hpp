#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/Side.hpp"
#include "../common/Decimal.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

// Published whenever a visible order is partially executed at its displayed price.
class PartialOrderExecutionMessage {
  public:
    static constexpr const char* name = "PartialOrderExecutionMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit PartialOrderExecutionMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every PartialOrderExecutionMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 56;
    static constexpr std::size_t fixed_size = 56;
    std::size_t encoded_size() const { return 56; }

    Side side() const { return static_cast<Side>(wire::read_u8(at(0))); }

    std::span<const std::byte, 7> pad_7() const { return bytes_.subspan(1).template first<7>(); }

    Decimal price() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_le(at(8))), -6); }

    std::chrono::nanoseconds trd_reg_ts_time_priority() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(at(16)))); }

    std::int64_t security_id() const { return wire::read_i64_le(at(24)); }

    std::uint32_t trd_match_id() const { return wire::read_u32_le(at(32)); }

    std::span<const std::byte, 4> pad_4() const { return bytes_.subspan(36).template first<4>(); }

    std::int64_t last_qty() const { return wire::read_i64_le(at(40)); }

    Decimal last_px() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_le(at(48))), -6); }

    void print(std::ostream& out) const {
        out << "PartialOrderExecutionMessage{";
        out << "side=";
        out << side();
        out << ", pad_7=";
        print::hex(out, pad_7().data(), pad_7().size());
        out << ", price=";
        out << price();
        out << ", trd_reg_ts_time_priority=";
        out << trd_reg_ts_time_priority().count();
        out << ", security_id=";
        out << security_id();
        out << ", trd_match_id=";
        out << trd_match_id();
        out << ", pad_4=";
        print::hex(out, pad_4().data(), pad_4().size());
        out << ", last_qty=";
        out << last_qty();
        out << ", last_px=";
        out << last_px();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const PartialOrderExecutionMessage& value) {
    value.print(out);
    return out;
}

} // namespace bse::bseindia::eobi::fbe::v1_4
