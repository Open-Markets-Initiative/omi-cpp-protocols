#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace cme::globex::mdp3::sbe::v1_5 {

// Number of repeating FeedType entries
class FeedTypesGroup {
  public:
    static constexpr const char* name = "FeedTypesGroup";

    // the bytes it reads, which it does not own: they must outlive it
    explicit FeedTypesGroup(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every FeedTypesGroup has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 4;
    static constexpr std::size_t fixed_size = 4;
    std::size_t encoded_size() const { return 4; }

    std::string_view md_feed_type() const { return view::text(at(0), 3, '\0'); }

    std::int8_t market_depth() const { return wire::read_i8(at(3)); }

    void print(std::ostream& out) const {
        out << "FeedTypesGroup{";
        out << "md_feed_type=";
        print::text(out, md_feed_type());
        out << ", market_depth=";
        out << static_cast<int>(market_depth());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const FeedTypesGroup& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_5
