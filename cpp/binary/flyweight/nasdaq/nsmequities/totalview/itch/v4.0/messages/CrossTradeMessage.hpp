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
#include "../common/Decimal.hpp"
#include "../enums/CrossType.hpp"

namespace nasdaq::nsmequities::totalview::itch::v4_0 {

// Cross Trade message indicates that NASDAQ has completed its cross process for a specific
// security.
class CrossTradeMessage {
  public:
    static constexpr const char* name = "CrossTradeMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit CrossTradeMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every CrossTradeMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 31;
    static constexpr std::size_t fixed_size = 31;
    std::size_t encoded_size() const { return 31; }

    std::chrono::nanoseconds nanoseconds() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(at(0)))); }

    std::uint64_t cross_shares() const { return wire::read_u64_be(at(4)); }

    std::string_view stock() const { return view::text(at(12), 6, ' '); }

    Decimal cross_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u32_be(at(18))), -4); }

    std::uint64_t match_number() const { return wire::read_u64_be(at(22)); }

    CrossType cross_type() const { return static_cast<CrossType>(wire::read_char(at(30))); }

    void print(std::ostream& out) const {
        out << "CrossTradeMessage{";
        out << "nanoseconds=";
        out << nanoseconds().count();
        out << ", cross_shares=";
        out << cross_shares();
        out << ", stock=";
        print::text(out, stock());
        out << ", cross_price=";
        out << cross_price();
        out << ", match_number=";
        out << match_number();
        out << ", cross_type=";
        out << cross_type();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const CrossTradeMessage& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nsmequities::totalview::itch::v4_0
