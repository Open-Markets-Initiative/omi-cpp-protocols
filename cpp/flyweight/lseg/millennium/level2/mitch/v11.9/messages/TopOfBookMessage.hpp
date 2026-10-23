#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

// Used to disseminate top of book changes when the instrument is in a scheduled level 1 only
// auction.
class TopOfBookMessage {
  public:
    static constexpr const char* name = "TopOfBookMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit TopOfBookMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every TopOfBookMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 32;
    static constexpr std::size_t fixed_size = 32;
    std::size_t encoded_size() const { return 32; }

    std::uint32_t nanosecond() const { return wire::read_u32_le(at(0)); }

    std::uint32_t instrument_id() const { return wire::read_u32_le(at(4)); }

    std::int64_t buy_limit_price() const { return wire::read_i64_le(at(8)); }

    std::uint32_t buy_limit_size() const { return wire::read_u32_le(at(16)); }

    std::int64_t sell_limit_price() const { return wire::read_i64_le(at(20)); }

    std::uint32_t sell_limit_size() const { return wire::read_u32_le(at(28)); }

    void print(std::ostream& out) const {
        out << "TopOfBookMessage{";
        out << "nanosecond=";
        out << nanosecond();
        out << ", instrument_id=";
        out << instrument_id();
        out << ", buy_limit_price=";
        out << buy_limit_price();
        out << ", buy_limit_size=";
        out << buy_limit_size();
        out << ", sell_limit_price=";
        out << sell_limit_price();
        out << ", sell_limit_size=";
        out << sell_limit_size();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const TopOfBookMessage& value) {
    value.print(out);
    return out;
}

} // namespace lseg::millennium::level2::mitch::v11_9
