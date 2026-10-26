#pragma once

#include <cstddef>
#include <cstdint>

namespace iex::iexequities::tops::snap::v1_6 {

// Sequence at which the snapshot was created
struct SnapshotSequenceNumber {

    static constexpr const char* name = "Snapshot Sequence Number";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr SnapshotSequenceNumber()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SnapshotSequenceNumber(const std::uint64_t value)
     : value{ value } {}

    // get value of SnapshotSequenceNumber field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
