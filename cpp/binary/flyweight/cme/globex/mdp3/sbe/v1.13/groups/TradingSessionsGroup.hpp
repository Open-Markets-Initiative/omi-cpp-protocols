#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

// Number of scheduled Trading Dates
class TradingSessionsGroup {
  public:
    static constexpr const char* name = "TradingSessionsGroup";

    // the bytes it reads, which it does not own: they must outlive it
    explicit TradingSessionsGroup(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every TradingSessionsGroup has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 18;
    static constexpr std::size_t fixed_size = 18;
    std::size_t encoded_size() const { return 18; }

    std::optional<std::uint16_t> trade_date() const { return wire::nullable(wire::read_u16_le(at(0)), static_cast<std::uint16_t>(65535ULL)); }

    std::optional<std::uint16_t> settl_date() const { return wire::nullable(wire::read_u16_le(at(2)), static_cast<std::uint16_t>(65535ULL)); }

    std::optional<std::uint16_t> maturity_date() const { return wire::nullable(wire::read_u16_le(at(4)), static_cast<std::uint16_t>(65535ULL)); }

    std::string_view security_alt_id() const { return view::text(at(6), 12, '\0'); }

    void print(std::ostream& out) const {
        out << "TradingSessionsGroup{";
        out << "trade_date=";
        print::optional(out, trade_date());
        out << ", settl_date=";
        print::optional(out, settl_date());
        out << ", maturity_date=";
        print::optional(out, maturity_date());
        out << ", security_alt_id=";
        print::text(out, security_alt_id());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const TradingSessionsGroup& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_13
