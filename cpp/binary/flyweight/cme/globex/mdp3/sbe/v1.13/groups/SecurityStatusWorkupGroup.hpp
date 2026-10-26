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
#include "../enums/AggressorIndicator.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

// Number of OrderID entries
class SecurityStatusWorkupGroup {
  public:
    static constexpr const char* name = "SecurityStatusWorkupGroup";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SecurityStatusWorkupGroup(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SecurityStatusWorkupGroup has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 10;
    static constexpr std::size_t fixed_size = 10;
    std::size_t encoded_size() const { return 10; }

    std::uint64_t order_id() const { return wire::read_u64_le(at(0)); }

    Side side() const { return static_cast<Side>(wire::read_u8(at(8))); }

    std::optional<AggressorIndicator> aggressor_indicator() const { return wire::nullable_enum<AggressorIndicator>(wire::read_u8(at(9)), static_cast<std::uint8_t>(255ULL)); }

    void print(std::ostream& out) const {
        out << "SecurityStatusWorkupGroup{";
        out << "order_id=";
        out << order_id();
        out << ", side=";
        out << side();
        out << ", aggressor_indicator=";
        print::optional(out, aggressor_indicator());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const SecurityStatusWorkupGroup& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_13
