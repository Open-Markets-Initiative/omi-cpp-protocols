#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/BreachedLevel.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

// Informs the market that a market wide circuit breaker decline level has been breached.
class MwcbStatusMessage {
  public:
    static constexpr const char* name = "MwcbStatusMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit MwcbStatusMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every MwcbStatusMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 1;
    static constexpr std::size_t fixed_size = 1;
    std::size_t encoded_size() const { return 1; }

    BreachedLevel breached_level() const { return static_cast<BreachedLevel>(wire::read_char(at(0))); }

    void print(std::ostream& out) const {
        out << "MwcbStatusMessage{";
        out << "breached_level=";
        out << breached_level();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const MwcbStatusMessage& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
