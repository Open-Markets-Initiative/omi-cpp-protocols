#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

// Future Leg
class FutureLeg {
  public:
    static constexpr const char* name = "FutureLeg";

    // the bytes it reads, which it does not own: they must outlive it
    explicit FutureLeg(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every FutureLeg has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 10;
    static constexpr std::size_t fixed_size = 10;
    std::size_t encoded_size() const { return 10; }

    std::int32_t leg_ratio() const { return wire::read_i32_le(at(0)); }

    std::string_view leg_symbol() const { return view::text(at(4), 6, ' '); }

    void print(std::ostream& out) const {
        out << "FutureLeg{";
        out << "leg_ratio=";
        out << leg_ratio();
        out << ", leg_symbol=";
        print::text(out, leg_symbol());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const FutureLeg& value) {
    value.print(out);
    return out;
}

} // namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22
