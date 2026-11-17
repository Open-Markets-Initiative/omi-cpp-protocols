// Databento.MarketData.Normalized.Dbn.v1: structs/File.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../structs/Metadata.hpp"

namespace databento::marketdata::normalized::dbn::v1 {

// A DBN file: the metadata, then records to its end
class File {
  public:
    static constexpr const char* name = "File";

    // the bytes it reads, which it does not own: they must outlive it
    explicit File(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every File has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 0;
    std::size_t encoded_size() const { return metadata_end(); }

    Metadata metadata() const { return Metadata{ bytes_.subspan(0) }; }

    void print(std::ostream& out) const {
        out << "File{";
        out << "metadata=";
        metadata().print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t metadata_end() const { return 0 + metadata().encoded_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const File& value) {
    value.print(out);
    return out;
}

} // namespace databento::marketdata::normalized::dbn::v1
