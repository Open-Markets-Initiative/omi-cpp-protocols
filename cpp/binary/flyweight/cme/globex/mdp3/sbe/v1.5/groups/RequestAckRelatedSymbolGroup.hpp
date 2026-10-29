#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace cme::globex::mdp3::sbe::v1_5 {

// Number of securities acknowledged
class RequestAckRelatedSymbolGroup {
  public:
    static constexpr const char* name = "RequestAckRelatedSymbolGroup";

    // the bytes it reads, which it does not own: they must outlive it
    explicit RequestAckRelatedSymbolGroup(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every RequestAckRelatedSymbolGroup has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 4;
    static constexpr std::size_t fixed_size = 4;
    std::size_t encoded_size() const { return 4; }

    std::int32_t security_id() const { return wire::read_i32_le(at(0)); }

    void print(std::ostream& out) const {
        out << "RequestAckRelatedSymbolGroup{";
        out << "security_id=";
        out << security_id();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const RequestAckRelatedSymbolGroup& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_5
