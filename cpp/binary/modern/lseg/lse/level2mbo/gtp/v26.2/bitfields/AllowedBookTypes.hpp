#pragma once

#include <cstddef>
#include <cstdint>

namespace lseg::lse::level2mbo::gtp::v26_2 {

// Defines the order-book types that are allowed for the instrument
struct AllowedBookTypes {

    // underlying type
    using type = std::uint8_t;

    static constexpr const char* name = "Allowed Book Types";
    static constexpr std::size_t size = 1;

    struct mask {
        static const type FirmQuoteBook = 0x02;
        static const type OffBook = 0x04;
        static const type ElectronicOrderBook = 0x08;
        static const type PrivateRfq = 0x10;
    };

    // default constructor
    constexpr AllowedBookTypes()
     : value{ 0 } {}

    // Firm Quote Book
    [[nodiscard]] constexpr bool FirmQuoteBook() const {
        return value & mask::FirmQuoteBook;
    }

    // Off-book
    [[nodiscard]] constexpr bool OffBook() const {
        return value & mask::OffBook;
    }

    // Electronic Order Book
    [[nodiscard]] constexpr bool ElectronicOrderBook() const {
        return value & mask::ElectronicOrderBook;
    }

    // Private RFQ
    [[nodiscard]] constexpr bool PrivateRfq() const {
        return value & mask::PrivateRfq;
    }

    // all bits
    [[nodiscard]] constexpr type get() const {
        return value;
    }

  protected:
    type value;
};
}
