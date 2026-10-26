#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

// Number of underlying instruments
class OptionUnderlyingsGroup {
  public:
    static constexpr const char* name = "OptionUnderlyingsGroup";

    // the bytes it reads, which it does not own: they must outlive it
    explicit OptionUnderlyingsGroup(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every OptionUnderlyingsGroup has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 24;
    static constexpr std::size_t fixed_size = 24;
    std::size_t encoded_size() const { return 24; }

    std::int32_t underlying_security_id() const { return wire::read_i32_le(at(0)); }

    std::string_view underlying_symbol() const { return view::text(at(4), 20, '\0'); }

    void print(std::ostream& out) const {
        out << "OptionUnderlyingsGroup{";
        out << "underlying_security_id=";
        out << underlying_security_id();
        out << ", underlying_symbol=";
        print::text(out, underlying_symbol());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const OptionUnderlyingsGroup& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_13
