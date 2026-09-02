#pragma once

#include <cstddef>
#include <cstdint>

namespace iex::iexequities::deepplus::snap::v1_05 {

// Length in bytes of the complete Snapshot Response including the Snapshot Start message, all Snapshot Data messages, and the Snapshot End message
struct SnapshotLength {

    static constexpr const char* name = "Snapshot Length";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr SnapshotLength()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SnapshotLength(const std::uint64_t value)
     : value{ value } {}

    // get value of SnapshotLength field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
