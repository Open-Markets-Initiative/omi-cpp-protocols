#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/MarketCode.hpp"
#include "../enums/OperationalHaltAction.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

// Indicates the current operational status of a security to the trading community. An
// operational halt is specific to the market centre for which it is declared and does not
// interrupt trading of the instrument on any other market place.
class OperationalHaltMessage {
  public:
    static constexpr const char* name = "OperationalHaltMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit OperationalHaltMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every OperationalHaltMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 10;
    static constexpr std::size_t fixed_size = 10;
    std::size_t encoded_size() const { return 10; }

    std::string_view stock() const { return view::text(at(0), 8, ' '); }

    MarketCode market_code() const { return static_cast<MarketCode>(wire::read_char(at(8))); }

    OperationalHaltAction operational_halt_action() const { return static_cast<OperationalHaltAction>(wire::read_char(at(9))); }

    void print(std::ostream& out) const {
        out << "OperationalHaltMessage{";
        out << "stock=";
        print::text(out, stock());
        out << ", market_code=";
        out << market_code();
        out << ", operational_halt_action=";
        out << operational_halt_action();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const OperationalHaltMessage& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
