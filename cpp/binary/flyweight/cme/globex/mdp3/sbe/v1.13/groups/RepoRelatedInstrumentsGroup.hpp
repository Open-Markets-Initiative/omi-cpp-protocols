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

// Number of related instruments group
class RepoRelatedInstrumentsGroup {
  public:
    static constexpr const char* name = "RepoRelatedInstrumentsGroup";

    // the bytes it reads, which it does not own: they must outlive it
    explicit RepoRelatedInstrumentsGroup(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every RepoRelatedInstrumentsGroup has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 32;
    static constexpr std::size_t fixed_size = 32;
    std::size_t encoded_size() const { return 32; }

    std::int32_t related_security_id() const { return wire::read_i32_le(at(0)); }

    std::string_view related_symbol() const { return view::text(at(4), 20, '\0'); }

    std::optional<std::uint64_t> related_instrument_guid() const { return wire::nullable(wire::read_u64_le(at(24)), static_cast<std::uint64_t>(18446744073709551615ULL)); }

    void print(std::ostream& out) const {
        out << "RepoRelatedInstrumentsGroup{";
        out << "related_security_id=";
        out << related_security_id();
        out << ", related_symbol=";
        print::text(out, related_symbol());
        out << ", related_instrument_guid=";
        print::optional(out, related_instrument_guid());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const RepoRelatedInstrumentsGroup& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_13
