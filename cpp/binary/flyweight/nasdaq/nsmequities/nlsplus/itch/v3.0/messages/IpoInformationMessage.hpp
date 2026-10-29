#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/SecurityClass.hpp"
#include "../enums/ReferenceForNetChange.hpp"
#include "../common/Decimal.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

// Denotes the reference price to be used for intraday net change calculations for an issue.
class IpoInformationMessage {
  public:
    static constexpr const char* name = "IpoInformationMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit IpoInformationMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every IpoInformationMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 14;
    static constexpr std::size_t fixed_size = 14;
    std::size_t encoded_size() const { return 14; }

    std::string_view issue_symbol() const { return view::text(at(0), 8, ' '); }

    SecurityClass security_class() const { return static_cast<SecurityClass>(wire::read_char(at(8))); }

    ReferenceForNetChange reference_for_net_change() const { return static_cast<ReferenceForNetChange>(wire::read_char(at(9))); }

    Decimal reference_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u32_be(at(10))), -4); }

    void print(std::ostream& out) const {
        out << "IpoInformationMessage{";
        out << "issue_symbol=";
        print::text(out, issue_symbol());
        out << ", security_class=";
        out << security_class();
        out << ", reference_for_net_change=";
        out << reference_for_net_change();
        out << ", reference_price=";
        out << reference_price();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const IpoInformationMessage& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
