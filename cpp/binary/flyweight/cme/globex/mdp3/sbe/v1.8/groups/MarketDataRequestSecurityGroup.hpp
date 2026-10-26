#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace cme::globex::mdp3::sbe::v1_8 {

// Number of SecurityGroups specified in subscription request. Should be equal 0, when
// subscription is requested for all groups on the segment or individual Security IDs are
// listed in the criteria for subscription
class MarketDataRequestSecurityGroup {
  public:
    static constexpr const char* name = "MarketDataRequestSecurityGroup";

    // the bytes it reads, which it does not own: they must outlive it
    explicit MarketDataRequestSecurityGroup(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every MarketDataRequestSecurityGroup has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 6;
    static constexpr std::size_t fixed_size = 6;
    std::size_t encoded_size() const { return 6; }

    std::string_view security_group() const { return view::text(at(0), 6, '\0'); }

    void print(std::ostream& out) const {
        out << "MarketDataRequestSecurityGroup{";
        out << "security_group=";
        print::text(out, security_group());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const MarketDataRequestSecurityGroup& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_8
