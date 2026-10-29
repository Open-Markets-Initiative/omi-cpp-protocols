#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../structs/Symbol.hpp"
#include "../groups/IndexValueMdEntry.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

// Index value messages contain the values associated with a calculated index. They are
// transmitted when an index is calculated.
class IndexValueMessage {
  public:
    static constexpr const char* name = "IndexValueMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit IndexValueMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every IndexValueMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 1;
    std::size_t encoded_size() const { return index_value_md_entry_end(); }

    Symbol symbol() const { return Symbol{ bytes_.subspan(0) }; }

    std::uint8_t no_entries() const {
        wire::require("IndexValueMessage", symbol_end() + 1, bytes_.size());
        return wire::read_u8(at(symbol_end()));
    }

    view::entries<IndexValueMdEntry> index_value_md_entry() const { return view::entries<IndexValueMdEntry>{ bytes_.subspan(no_entries_end()), wire::count(no_entries()) }; }

    void print(std::ostream& out) const {
        out << "IndexValueMessage{";
        out << "symbol=";
        symbol().print(out);
        out << ", no_entries=";
        out << static_cast<int>(no_entries());
        out << ", index_value_md_entry=";
        print::sequence(out, index_value_md_entry());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t symbol_end() const { return 0 + symbol().encoded_size(); }
    std::size_t no_entries_end() const { return symbol_end() + 1; }
    std::size_t index_value_md_entry_end() const { return no_entries_end() + index_value_md_entry().encoded_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const IndexValueMessage& value) {
    value.print(out);
    return out;
}

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
