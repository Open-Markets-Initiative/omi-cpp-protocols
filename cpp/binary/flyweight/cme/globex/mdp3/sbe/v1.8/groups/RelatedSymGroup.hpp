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

namespace cme::globex::mdp3::sbe::v1_8 {

// Indicates the number of repeating symbols specified
class RelatedSymGroup {
  public:
    static constexpr const char* name = "RelatedSymGroup";

    // the bytes it reads, which it does not own: they must outlive it
    explicit RelatedSymGroup(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every RelatedSymGroup has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 32;
    static constexpr std::size_t fixed_size = 32;
    std::size_t encoded_size() const { return 32; }

    std::string_view symbol() const { return view::text(at(0), 20, '\0'); }

    std::int32_t security_id() const { return wire::read_i32_le(at(20)); }

    std::optional<std::int32_t> order_qty() const { return wire::nullable(wire::read_i32_le(at(24)), static_cast<std::int32_t>(2147483647LL)); }

    std::int8_t quote_type() const { return wire::read_i8(at(28)); }

    std::optional<std::int8_t> side() const { return wire::nullable(wire::read_i8(at(29)), static_cast<std::int8_t>(127LL)); }

    std::span<const std::byte, 2> padding_2() const { return bytes_.subspan(30).template first<2>(); }

    void print(std::ostream& out) const {
        out << "RelatedSymGroup{";
        out << "symbol=";
        print::text(out, symbol());
        out << ", security_id=";
        out << security_id();
        out << ", order_qty=";
        print::optional(out, order_qty());
        out << ", quote_type=";
        out << static_cast<int>(quote_type());
        out << ", side=";
        print::optional(out, side());
        out << ", padding_2=";
        print::hex(out, padding_2().data(), padding_2().size());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const RelatedSymGroup& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_8
