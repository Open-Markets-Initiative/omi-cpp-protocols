#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../structs/GroupSize.hpp"
#include "../groups/OptionRelatedInstrumentsGroup.hpp"

namespace cme::globex::mdp3::sbe::v1_9 {

// NoRelatedInstruments Block
class OptionRelatedInstrumentsGroups {
  public:
    static constexpr const char* name = "OptionRelatedInstrumentsGroups";

    // the bytes it reads, which it does not own: they must outlive it
    explicit OptionRelatedInstrumentsGroups(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every OptionRelatedInstrumentsGroups has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 3;
    std::size_t encoded_size() const { return option_related_instruments_group_end(); }

    GroupSize group_size() const { return GroupSize{ bytes_.subspan(0) }; }

    view::entries<OptionRelatedInstrumentsGroup> option_related_instruments_group() const { return view::entries<OptionRelatedInstrumentsGroup>{ bytes_.subspan(3), wire::count(group_size().num_in_group()), wire::count(group_size().block_length()) }; }

    void print(std::ostream& out) const {
        out << "OptionRelatedInstrumentsGroups{";
        out << "group_size=";
        group_size().print(out);
        out << ", option_related_instruments_group=";
        print::sequence(out, option_related_instruments_group());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t option_related_instruments_group_end() const { return 3 + option_related_instruments_group().encoded_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const OptionRelatedInstrumentsGroups& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_9
