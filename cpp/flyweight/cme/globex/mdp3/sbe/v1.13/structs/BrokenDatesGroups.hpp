#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../structs/GroupSize.hpp"
#include "../groups/BrokenDatesGroup.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

// NoBrokenDates Block
class BrokenDatesGroups {
  public:
    static constexpr const char* name = "BrokenDatesGroups";

    // the bytes it reads, which it does not own: they must outlive it
    explicit BrokenDatesGroups(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every BrokenDatesGroups has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 3;
    std::size_t encoded_size() const { return broken_dates_group_end(); }

    GroupSize group_size() const { return GroupSize{ bytes_.subspan(0) }; }

    view::entries<BrokenDatesGroup> broken_dates_group() const { return view::entries<BrokenDatesGroup>{ bytes_.subspan(3), wire::count(group_size().num_in_group()), wire::count(group_size().block_length()) }; }

    void print(std::ostream& out) const {
        out << "BrokenDatesGroups{";
        out << "group_size=";
        group_size().print(out);
        out << ", broken_dates_group=";
        print::sequence(out, broken_dates_group());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t broken_dates_group_end() const { return 3 + broken_dates_group().encoded_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const BrokenDatesGroups& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_13
