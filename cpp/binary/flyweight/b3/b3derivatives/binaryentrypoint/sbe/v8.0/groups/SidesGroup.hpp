#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/Side.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

// noSides
class SidesGroup {
  public:
    static constexpr const char* name = "SidesGroup";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SidesGroup(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SidesGroup has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 5;
    static constexpr std::size_t fixed_size = 5;
    std::size_t encoded_size() const { return 5; }

    Side side() const { return static_cast<Side>(wire::read_char(at(0))); }

    std::optional<std::uint32_t> account() const { return wire::nullable(wire::read_u32_le(at(1)), static_cast<std::uint32_t>(0ULL)); }

    void print(std::ostream& out) const {
        out << "SidesGroup{";
        out << "side=";
        out << side();
        out << ", account=";
        print::optional(out, account());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const SidesGroup& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0
