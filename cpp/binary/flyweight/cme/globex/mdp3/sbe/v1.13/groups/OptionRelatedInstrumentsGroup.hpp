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

// Number of related instruments group
class OptionRelatedInstrumentsGroup {
  public:
    static constexpr const char* name = "OptionRelatedInstrumentsGroup";

    // the bytes it reads, which it does not own: they must outlive it
    explicit OptionRelatedInstrumentsGroup(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every OptionRelatedInstrumentsGroup has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 24;
    static constexpr std::size_t fixed_size = 24;
    std::size_t encoded_size() const { return 24; }

    std::int32_t related_security_id() const { return wire::read_i32_le(at(0)); }

    std::string_view related_symbol() const { return view::text(at(4), 20, '\0'); }

    void print(std::ostream& out) const {
        out << "OptionRelatedInstrumentsGroup{";
        out << "related_security_id=";
        out << related_security_id();
        out << ", related_symbol=";
        print::text(out, related_symbol());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const OptionRelatedInstrumentsGroup& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_13
