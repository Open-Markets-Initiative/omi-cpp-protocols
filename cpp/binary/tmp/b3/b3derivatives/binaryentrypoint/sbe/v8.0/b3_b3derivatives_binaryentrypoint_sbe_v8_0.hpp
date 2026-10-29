// B3 B3Derivatives BinaryEntryPoint Sbe 8.0 Template Meta Programming

#pragma once

#include <algorithm>
#include <array>
#include <bit>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <span>
#include <stdexcept>
#include <string>
#include <string_view>
#include <type_traits>

// A member of a struct laid over its bytes: the overload get<Field>() finds it by, and the member
#ifndef BINARYENTRYPOINTFIELD
#define BINARYENTRYPOINTFIELD(type) constexpr const type& ref(const type*) const noexcept { return type##_; } type type##_
#endif

// A repeating group of a message: its entries' type, which the parse hands over one at a time; no bytes
#ifndef BINARYENTRYPOINTSEQUENCE
#define BINARYENTRYPOINTSEQUENCE(type) using type##_sequence = tmp::sequence<type>
#endif

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

/////////////////////////////////////////////////////////////////////
// Wire
/////////////////////////////////////////////////////////////////////

namespace tmp {
    // The types of a struct's members, in wire order: what generic code walks a struct by
    template <typename... Fields>
    struct list {};

    // A repeating group of a message: the type of its entries, each laid over its bytes in turn
    template <typename Entry>
    struct sequence {
        using entry = Entry;
    };

    // An integer as the wire holds it, in the host's order: swapped when the wire's order is not the host's
    template <std::endian Order, typename T>
    constexpr T ordered(T value) noexcept {
        if constexpr (sizeof(T) == 1 || Order == std::endian::native) { return value; }
        else { return std::byteswap(value); }
    }

    // An integer of a width no C++ integer has, assembled from its bytes in the wire's order
    template <std::endian Order, typename T, std::size_t N>
    constexpr T assembled(const std::array<std::byte, N>& bytes) noexcept {
        using U = std::make_unsigned_t<T>;
        U value = 0;
        for (std::size_t index = 0; index < N; ++index) {
            const std::size_t at = Order == std::endian::big ? index : N - 1 - index;
            value = static_cast<U>((value << 8) | std::to_integer<U>(bytes[at]));
        }
        if constexpr (std::is_signed_v<T>) {
            constexpr int spare = static_cast<int>(sizeof(T) - N) * 8;
            return static_cast<T>(static_cast<T>(value << spare) >> spare);
        }
        else { return value; }
    }

    // Text of a fixed width, as the characters before its fill
    template <std::size_t N>
    constexpr std::string_view trimmed(const std::array<char, N>& text, char fill) noexcept {
        std::size_t length = N;
        while (length > 0 && text[length - 1] == fill) { --length; }
        return { text.data(), length };
    }

    // Text of a fixed width justified right, as the characters after its fill
    template <std::size_t N>
    constexpr std::string_view trimmed_front(const std::array<char, N>& text, char fill) noexcept {
        std::size_t start = 0;
        while (start < N && text[start] == fill) { ++start; }
        return { text.data() + start, N - start };
    }

    // The integer the digits of text state, its fill skipped; it ends at anything else
    template <typename T>
    constexpr T number(std::string_view text, char fill) noexcept {
        T value = 0;
        for (const char character : text) {
            if (character == fill) { continue; }
            if (character < '0' || character > '9') { break; }
            value = static_cast<T>(value * 10 + static_cast<T>(character - '0'));
        }
        return value;
    }
} // namespace tmp

/////////////////////////////////////////////////////////////////////
// Types
/////////////////////////////////////////////////////////////////////

// Account
struct account {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Account Type: accountType
struct account_type {
    enum class type : std::uint8_t {
        remove_account_information = 38,
        regular_account = 39,
    };

    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(0);

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Aggressor Indicator: aggressorIndicator
struct aggressor_indicator {
    enum class type : std::uint8_t {
        false_value = 0,
        true_value = 1,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Alloc Account: allocAccount
struct alloc_account {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Alloc Id: allocID
struct alloc_id {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Alloc No Orders Type: allocNoOrdersType
struct alloc_no_orders_type {
    enum class type : char {
        not_specified = '0',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Alloc Qty: allocQty
struct alloc_qty {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Alloc Rej Code: allocRejCode
struct alloc_rej_code {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Alloc Report Id: allocReportID
struct alloc_report_id {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Alloc Report Type: allocReportType
struct alloc_report_type {
    enum class type : char {
        request_to_intermediary = '8',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Alloc Status: allocStatus
struct alloc_status {
    enum class type : char {
        accepted = '0',
        rejected_by_intermediary = '5',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Alloc Trans Type: allocTransType
struct alloc_trans_type {
    enum class type : char {
        new_value = '0',
        cancel = '2',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Alloc Type: allocType
struct alloc_type {
    enum class type : char {
        request_to_intermediary = '8',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Asset
struct asset {
    using type = std::string_view;
    static constexpr std::size_t size = 6;
    static constexpr char fill = '\0';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 6> value_;
};

// Block Length: blockLength
struct block_length {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Business Reject Reason: businessRejectReason
struct business_reject_reason {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Business Reject Ref Id: businessRejectRefID
struct business_reject_ref_id {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Cancel On Disconnect Type: cancelOnDisconnectType
struct cancel_on_disconnect_type {
    enum class type : std::uint8_t {
        do_not_cancel_on_disconnect_or_terminate = 0,
        cancel_on_disconnect_only = 1,
        cancel_on_terminate_only = 2,
        cancel_on_disconnect_or_terminate = 3,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Clearing Business Date: clearingBusinessDate
struct clearing_business_date {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Client App Name Data: Client system information.
struct client_app_name_data {
    using type = std::string_view;
    static constexpr bool dynamic = true;

    constexpr client_app_name_data(const std::byte* data, std::size_t length) noexcept : data_{ data }, length_{ length } {}

    constexpr type value() const noexcept { return { reinterpret_cast<const char*>(data_), length_ }; }
    constexpr operator type() const noexcept { return value(); }
    // the bytes it takes
    constexpr std::size_t length() const noexcept { return length_; }

  protected:
    const std::byte* data_;
    std::size_t length_;
};

// Client App Name Length: Length of client system information.
struct client_app_name_length {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Client App Version Data: Client system information.
struct client_app_version_data {
    using type = std::string_view;
    static constexpr bool dynamic = true;

    constexpr client_app_version_data(const std::byte* data, std::size_t length) noexcept : data_{ data }, length_{ length } {}

    constexpr type value() const noexcept { return { reinterpret_cast<const char*>(data_), length_ }; }
    constexpr operator type() const noexcept { return value(); }
    // the bytes it takes
    constexpr std::size_t length() const noexcept { return length_; }

  protected:
    const std::byte* data_;
    std::size_t length_;
};

// Client App Version Length: Length of client system information.
struct client_app_version_length {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Client Ip Data: Client system information.
struct client_ip_data {
    using type = std::string_view;
    static constexpr bool dynamic = true;

    constexpr client_ip_data(const std::byte* data, std::size_t length) noexcept : data_{ data }, length_{ length } {}

    constexpr type value() const noexcept { return { reinterpret_cast<const char*>(data_), length_ }; }
    constexpr operator type() const noexcept { return value(); }
    // the bytes it takes
    constexpr std::size_t length() const noexcept { return length_; }

  protected:
    const std::byte* data_;
    std::size_t length_;
};

// Client Ip Length: Length of client system information.
struct client_ip_length {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// ClOrdId
struct clordid {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// ClOrdId Optional: clOrdID
struct clordid_optional {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Cod Timeout Window: codTimeoutWindow
struct cod_timeout_window {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Contra Broker: contraBroker
struct contra_broker {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Contrary Instruction Indicator: contraryInstructionIndicator
struct contrary_instruction_indicator {
    enum class type : std::uint8_t {
        false_value = 0,
        true_value = 1,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Count
struct count_type {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Credentials Data: Credentials data in ASCII.
struct credentials_data {
    using type = std::string_view;
    static constexpr bool dynamic = true;

    constexpr credentials_data(const std::byte* data, std::size_t length) noexcept : data_{ data }, length_{ length } {}

    constexpr type value() const noexcept { return { reinterpret_cast<const char*>(data_), length_ }; }
    constexpr operator type() const noexcept { return value(); }
    // the bytes it takes
    constexpr std::size_t length() const noexcept { return length_; }

  protected:
    const std::byte* data_;
    std::size_t length_;
};

// Credentials Length: Length of credentials data.
struct credentials_length {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Crossed Indicator: crossedIndicator
struct crossed_indicator {
    enum class type : std::uint16_t {
        structured_transaction = 1001,
        operational_error = 1002,
        twap_vwap = 1003,
    };

    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0);

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return tmp::ordered<order>(value_); }

  protected:
    std::underlying_type_t<type> value_;
};

// CrossId
struct crossid {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// CrossId Optional: crossID
struct crossid_optional {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Cum Qty: cumQty
struct cum_qty {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Current Session Ver Id: currentSessionVerID
struct current_session_ver_id {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Custodian
struct custodian {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Custody Account: custodyAccount
struct custody_account {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Custody Allocation Type: custodyAllocationType
struct custody_allocation_type {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Cxl Rej Response To: cxlRejResponseTo
struct cxl_rej_response_to {
    enum class type : std::uint8_t {
        new_value = 0,
        cancel = 1,
        replace = 2,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Days To Settlement: daysToSettlement
struct days_to_settlement {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Days To Settlement Optional: daysToSettlement
struct days_to_settlement_optional {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(65535ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Desk Id Data: Trading desk identification in ASCII format.
struct desk_id_data {
    using type = std::string_view;
    static constexpr bool dynamic = true;

    constexpr desk_id_data(const std::byte* data, std::size_t length) noexcept : data_{ data }, length_{ length } {}

    constexpr type value() const noexcept { return { reinterpret_cast<const char*>(data_), length_ }; }
    constexpr operator type() const noexcept { return value(); }
    // the bytes it takes
    constexpr std::size_t length() const noexcept { return length_; }

  protected:
    const std::byte* data_;
    std::size_t length_;
};

// Desk Id Length: Length of trading desk identification.
struct desk_id_length {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Document
struct document {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Encoding Type: Identifier of the encoding used in the message payload
struct encoding_type {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Entering Firm: enteringFirm
struct entering_firm {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Entering Firm Optional: enteringFirm
struct entering_firm_optional {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Entering Trader: enteringTrader
struct entering_trader {
    using type = std::string_view;
    static constexpr std::size_t size = 5;
    static constexpr char fill = '\0';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 5> value_;
};

// Establishment Reject Code: establishmentRejectCode
struct establishment_reject_code {
    enum class type : std::uint8_t {
        unspecified = 0,
        credentials = 1,
        unnegotiated = 2,
        already_established = 3,
        session_blocked = 4,
        invalid_sessionid = 5,
        invalid_sessionverid = 6,
        invalid_timestamp = 7,
        invalid_keepalive_interval = 8,
        invalid_nextseqno = 9,
        establish_attempts_exceeded = 10,
        establish_not_allowed = 20,
        duplicate_session_connection = 21,
        authentication_in_progress = 22,
        protocol_version_not_supported = 23,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Exec Id: execID
struct exec_id {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Exec Ref Id: execRefID
struct exec_ref_id {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Exec Restatement Reason: execRestatementReason
struct exec_restatement_reason {
    enum class type : std::uint8_t {
        market_option = 8,
        cancel_on_hard_disconnection = 100,
        cancel_on_terminate = 101,
        cancel_on_disconnect_and_terminate = 102,
        self_trading_prevention = 103,
        cancel_from_firmsoft = 105,
        cancel_resting_order_on_self_trade = 107,
        market_maker_protection = 200,
        risk_management_cancellation = 201,
        order_mass_action_from_client_request = 202,
        cancel_order_due_to_operational_error = 203,
        order_cancelled_due_to_operational_error = 204,
        cancel_order_firmsoft_due_to_operational_error = 205,
        order_cancelled_firmsoft_due_to_operational_error = 206,
        mass_cancel_order_due_to_operational_error_request = 207,
        mass_cancel_order_due_to_operational_error_effective = 208,
        cancel_on_midpoint_broker_only_removal = 209,
    };

    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(0);

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Exec Type: execType
struct exec_type {
    enum class type : char {
        trade = 'F',
        trade_cancel = 'H',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Execute Underlying Trade: executeUnderlyingTrade
struct execute_underlying_trade {
    enum class type : char {
        no_underlying_trade = '0',
        underlying_opposing_trade = '1',
    };

    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>('0');

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Executing Trader: executingTrader
struct executing_trader {
    using type = std::string_view;
    static constexpr std::size_t size = 5;
    static constexpr char fill = '\0';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 5> value_;
};

// Executing Trader Optional: executingTrader
struct executing_trader_optional {
    using type = std::string_view;
    static constexpr std::size_t size = 5;
    static constexpr char fill = '\0';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 5> value_;
};

// Expire Date: expireDate
struct expire_date {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Fixed Rate: fixedRate
struct fixed_rate {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Fixed Rate Optional: fixedRate
struct fixed_rate_optional {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(-9223372036854775807LL - 1);
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// From Seq No: fromSeqNo
struct from_seq_no {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Individual Alloc Id: individualAllocID
struct individual_alloc_id {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Keep Alive Interval: keepAliveInterval
struct keep_alive_interval {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Last Incoming Seq No: lastIncomingSeqNo
struct last_incoming_seq_no {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Last Incoming Seq No Optional: lastIncomingSeqNo
struct last_incoming_seq_no_optional {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Last Px: lastPx
struct last_px {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Last Qty: lastQty
struct last_qty {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Leaves Qty: leavesQty
struct leaves_qty {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Leg Ratio Qty: The ratio of quantity for this individual leg relative to the entire multileg security.
struct leg_ratio_qty {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -7;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Leg Side: The side of this individual leg (multileg security). See Side (54) field for description and values.
struct leg_side {
    enum class type : char {
        buy = '1',
        sell = '2',
    };

    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>('0');

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Leg Symbol: Multileg instrument's individual security’s Symbol. See Symbol (55) field for description.
struct leg_symbol {
    using type = std::string_view;
    static constexpr std::size_t size = 20;
    static constexpr char fill = '\0';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 20> value_;
};

// Long Qty: longQty
struct long_qty {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Long Qty Optional: Long Quantity.
struct long_qty_optional {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Market Segment Id: marketSegmentID
struct market_segment_id {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Market Segment Id Optional: marketSegmentID
struct market_segment_id_optional {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Market Segment Received Time: marketSegmentReceivedTime
struct market_segment_received_time {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Mass Action Reject Reason: massActionRejectReason
struct mass_action_reject_reason {
    enum class type : std::uint8_t {
        mass_action_not_supported = 0,
        invalid_or_unknown_market_segment = 8,
        other = 99,
    };

    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(255);

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Mass Action Report Id: massActionReportID
struct mass_action_report_id {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Mass Action Report Id Optional: massActionReportID
struct mass_action_report_id_optional {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Mass Action Response: massActionResponse
struct mass_action_response {
    enum class type : char {
        rejected = '0',
        accepted = '1',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Mass Action Scope: massActionScope
struct mass_action_scope {
    enum class type : std::uint8_t {
        all_orders_for_a_trading_session = 6,
    };

    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(0);

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Mass Action Type: massActionType
struct mass_action_type {
    enum class type : std::uint8_t {
        release_orders_from_suspension = 2,
        cancel_orders = 3,
        cancel_and_suspend_orders = 4,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Mass Cancel Restatement Reason: execRestatementReason
struct mass_cancel_restatement_reason {
    enum class type : std::uint8_t {
        order_mass_action_from_client_request = 202,
        mass_cancel_order_due_to_operational_error_request = 207,
    };

    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(0);

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Max Floor: maxFloor
struct max_floor {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Memo Data: Free ASCII format text field defined by client.
struct memo_data {
    using type = std::string_view;
    static constexpr bool dynamic = true;

    constexpr memo_data(const std::byte* data, std::size_t length) noexcept : data_{ data }, length_{ length } {}

    constexpr type value() const noexcept { return { reinterpret_cast<const char*>(data_), length_ }; }
    constexpr operator type() const noexcept { return value(); }
    // the bytes it takes
    constexpr std::size_t length() const noexcept { return length_; }

  protected:
    const std::byte* data_;
    std::size_t length_;
};

// Memo Length: Length of free format text field defined by client.
struct memo_length {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Message Length: Overall message length including framing and SBE headers
struct message_length {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Min Qty: minQty
struct min_qty {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Mm Protection Reset: mmProtectionReset
struct mm_protection_reset {
    enum class type : std::uint8_t {
        false_value = 0,
        true_value = 1,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Msg Seq Num: msgSeqNum
struct msg_seq_num {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Multi Leg Reporting Type: multiLegReportingType
struct multi_leg_reporting_type {
    enum class type : char {
        single_security = '1',
        individualleg_of_multileg_security = '2',
        multileg_security = '3',
    };

    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>('0');

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Negotiation Reject Code: negotiationRejectCode
struct negotiation_reject_code {
    enum class type : std::uint8_t {
        unspecified = 0,
        credentials = 1,
        flowtype_not_supported = 2,
        already_negotiated = 3,
        session_blocked = 4,
        invalid_sessionid = 5,
        invalid_sessionverid = 6,
        invalid_timestamp = 7,
        invalid_firm = 8,
        negotiate_not_allowed = 20,
        duplicate_session_connection = 21,
        authentication_in_progress = 22,
        protocol_version_not_supported = 23,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Next Seq No: nextSeqNo
struct next_seq_no {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Num In Group: numInGroup
struct num_in_group {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Offset 1 Padding 1: 1 bytes padding
struct offset_1_padding_1 {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Offset 100 Padding 4: 4 bytes padding
struct offset_100_padding_4 {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Offset 118 Padding 2: 2 bytes padding
struct offset_118_padding_2 {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Offset 119 Padding 1: 1 bytes padding
struct offset_119_padding_1 {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Offset 18 Padding 2: 2 bytes padding
struct offset_18_padding_2 {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Offset 19 Padding 1: 1 bytes padding
struct offset_19_padding_1 {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Offset 2 Padding 2: 2 bytes padding
struct offset_2_padding_2 {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Offset 21 Padding 1: 1 bytes padding
struct offset_21_padding_1 {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Offset 25 Padding 3: 3 bytes padding
struct offset_25_padding_3 {
    using type = std::uint32_t;
    static constexpr std::size_t size = 3;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::assembled<order, type>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<std::byte, 3> value_;
};

// Offset 31 Padding 1: 1 bytes padding
struct offset_31_padding_1 {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Offset 33 Padding 1: 1 bytes padding
struct offset_33_padding_1 {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Offset 49 Padding 1: 1 bytes padding
struct offset_49_padding_1 {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Offset 54 Padding 2: 2 bytes padding
struct offset_54_padding_2 {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Onbehalf Firm: onbehalfFirm
struct onbehalf_firm {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Ord Rej Reason: ordRejReason
struct ord_rej_reason {
    enum class type : std::uint32_t {
        unable_to_send_fix_from_volatilityupdate_message = 908,
        orders_may_not_be_entered_while_the_market_is_closedpaused = 1003,
        fix_field_missing_or_incorrect = 1007,
        required_field_missing = 1010,
        fix_field_incorrect = 1011,
        price_must_be_greater_than_zero = 1012,
        invalid_order_qualifier = 1013,
        user_not_authorized_to_trade = 1014,
        required_field_missing_stop_orders_cannot_be_iocfak = 1016,
        required_field_missing_display_quantity_orders_cannot_be_iocfok = 1017,
        required_field_missing_stop_orders_cannot_be_iocfok = 1018,
        market_price_orders_not_supported_by_opposite_limit = 2013,
        order_gtd_expire_date_is_before_the_current_or_next_if_not_currently_in_a_session_trading_session_end_date = 2019,
        cannot_modify_order_because_order_does_not_exist = 2045,
        disclosed_quantity_cannot_be_greater_than_total_or_remaining_quantity = 2046,
        order_contract_is_unknown = 2047,
        the_order_was_submitted_with_a_different_sendercompid_than_the_requesting_cancel = 2048,
        the_order_was_submitted_with_a_different_clorderid_than_the_correlationclorderid_of_the_requesting_cancel = 2049,
        the_order_was_submitted_with_a_different_clorderid_than_the_originalclorderid_of_the_requesting_cancel = 2050,
        the_order_was_submitted_with_a_different_side_than_the_requesting_cancel = 2051,
        the_order_was_submitted_with_a_different_group_tag_55_than_the_requesting_cancel = 2052,
        the_order_was_submitted_with_a_different_security_type_than_the_requesting_cancel = 2053,
        the_order_was_submitted_with_a_different_account_than_the_requesting_cancel = 2054,
        the_order_was_submitted_with_a_different_quantity_than_the_requesting_cancel = 2055,
        the_order_was_submitted_with_a_different_traderid_than_the_requesting_cancel = 2056,
        attempt_to_cancel_an_order_with_a_different_firmid_than_the_original_order = 2057,
        attempt_to_cancel_an_order_with_a_different_senderlocationid_than_the_original_order = 2058,
        stop_price_maximini_must_be_smaller_than_or_equal_to_trigger_price = 2059,
        sell_order_stop_price_must_be_below_last_trade_price = 2060,
        buy_order_stop_price_must_be_above_last_trade_price = 2061,
        the_modify_was_submitted_on_a_different_product_than_the_original_order = 2100,
        attempt_to_modify_an_order_with_a_different_inflightfill_mitigation_status_than_first_modification = 2101,
        attempt_to_modify_an_order_with_a_different_sendercompid_than_the_original_order = 2102,
        attempt_to_modify_an_order_with_a_different_traderid_than_the_original_order = 2103,
        attempt_to_modify_an_order_with_a_different_accountid_than_the_original_order = 2104,
        attempt_to_modify_an_order_with_a_different_firmid_than_the_original_order = 2105,
        attempt_to_modify_an_order_with_a_different_senderlocationid_than_the_original_order = 2106,
        disclosed_quantity_is_not_allowed = 2107,
        account_or_give_up_firm_required_for_dma_customers = 2108,
        disclosed_qty_cannot_be_less_than_disclosed_qty_min = 2109,
        acct_type38_not_valid_for_tag_581_for_dma_customers = 2110,
        give_up_not_valid_for_fx_spot_contract = 2111,
        visibility_permission_not_granted_for_executing_traderentering_trader = 2112,
        executing_trader_doesnt_have_access_to_product_group = 2113,
        attempt_to_modify_market_order_to_some_other_type = 2114,
        order_quantity_is_outside_of_the_allowable_range = 2115,
        account_is_mandatory_for_fx_spot = 2116,
        order_on_behalf_by_dma_customer_is_not_allowed = 2117,
        attempt_to_modify_an_order_with_a_different_accounttype_than_the_original_order = 2118,
        account_or_give_up_firm_required_for_equities = 2123,
        order_type_not_permitted_while_the_market_is_in_pre_open = 2130,
        order_price_is_outside_limits = 2137,
        qty_is_not_multiple_of_round_lot = 2138,
        qty_is_greater_or_equal_than_maximum_trade_volume = 2139,
        order_price_is_outside_bands = 2179,
        order_price_is_outside_auction_bands = 2180,
        trade_outside_of_short_term_volatility_bands = 2181,
        all_legs_must_have_same_lot_types = 2182,
        all_legs_must_have_same_tick_increment = 2183,
        all_legs_must_have_same_step_of_quotation = 2184,
        trade_price_is_outside_of_static_limits = 2185,
        cod_not_supported_for_gtc_gtd_orders = 2186,
        order_not_bookable_at_this_time = 2187,
        minimum_quantity_was_not_filled = 2188,
        order_attributes_not_allowed_to_trip_an_auction = 2189,
        order_type_not_permitted_for_group = 2311,
        instrument_has_an_request_for_cross_in_progress = 2500,
        order_quantity_too_low = 2501,
        crosstype_ineligible_for_instrument = 2502,
        rfq_for_cross_is_not_allowed_since_contract_is_not_rfq_for_cross_eligible = 2503,
        dma_crossorder_not_allowed = 2504,
        cross_order_rejected_due_to_auction_trigger_validation = 2505,
        trade_on_behalf_rejected = 2506,
        market_maker_protection_in_effect_for_user_xxxxxxxx_and_group_xxxxxx = 2600,
        rfq_rejected_instrumentexchange_not_tradable = 3000,
        rfq_rejected_instrumentexchange_not_known = 3001,
        error_creating_contract = 3002,
        business_reject_other = 3010,
        business_reject_unknown_id = 3011,
        business_reject_unknown_security = 3012,
        business_reject_unsupported_message_type = 3013,
        business_reject_application_not_available = 3014,
        business_reject_required_field_missing = 3015,
        contract_claims_to_be_a_spread_but_is_missing_one_or_more_legs = 3016,
        fix_field_length_exceeds_max_length = 3017,
        special_auction_permissions_order_entry_not_allowed = 3020,
        engine_did_not_respond_to_fas_request = 4000,
        termo_message_rejected_unknown_instrument = 6001,
        termo_message_rejected_exchange_security_closed = 6002,
        termo_rejected_instrumentexchange_not_tradable = 6003,
        termo_message_rejected_limits_exceeded = 6004,
        termo_message_rejected_too_late_to_enter = 6005,
        termo_message_rejected_unknown_termo_quote = 6006,
        termo_message_rejected_duplicate_termo_quote = 6007,
        termo_message_rejected_invalid_bidask_spread = 6008,
        termo_message_rejected_invalid_price = 6009,
        termo_message_rejected_not_authorized_to_termo_quote_this_instrument = 6010,
        termo_message_rejected_pass = 6011,
        fix_field_incorrect_2 = 6012,
        not_a_valid_termo_instrument = 6013,
        values_dont_match_with_the_original_request = 6014,
        current_termo_request_status_does_not_allow_rejection = 6015,
        current_termo_request_status_does_not_allow_acceptance = 6016,
        wrong_type_of_order_book_for_termo = 6017,
        wrong_type_of_request_for_termo = 6018,
        days_to_settlement_must_be_between_16_and_999 = 6019,
        days_to_settlement_must_be_between_16_and_90 = 6020,
        instrument_not_allowed_to_this_market = 6021,
        instrument_not_allowed_to_this_market_2 = 6022,
        termo_price_should_be_greater_than_zero = 6023,
        termo_messages_should_not_be_entered_when_market_is_paused = 6024,
        termo_messages_should_not_be_entered_when_market_is_pre_open = 6025,
        termo_messages_should_not_be_entered_when_market_is_pcp = 6026,
        termo_messages_should_not_be_entered_when_market_is_no_cancel = 6027,
        termo_messages_should_not_be_entered_when_market_is_reserved = 6028,
        termo_messages_should_not_be_entered_when_market_is_forbidden = 6029,
        termo_messages_should_not_be_entered_when_market_is_pre_close = 6030,
        termo_messages_should_not_be_entered_when_market_is_pre_open_2 = 6031,
        not_a_valid_termo_underlying_instrument = 6032,
        received_a_null_adminoperation = 6033,
        first_trade_of_day_for_underlying_termo_instrument = 6034,
        termo_messages_should_not_be_entered_when_market_is_in_final_closing_call = 6035,
        invalid_cash_trade_in_tvr = 6036,
        only_buy_entry_request_for_tvr_is_accepted = 6037,
        there_is_no_bid_and_ask_for_underlying_contract = 6038,
        invalid_price = 6039,
        invalid_cash_trade_in_tvr_2 = 6040,
        invalid_cash_trade_in_tvr_3 = 6041,
        invalid_cash_trade_in_tvr_4 = 6042,
        invalid_cash_trade_in_tvr_5 = 6043,
        invalid_cash_trade_in_tvr_6 = 6044,
        order_rejected = 7000,
        fok_order_unmatchable_in_market = 7001,
        orders_may_not_be_entered_while_the_market_is_closed = 7002,
        order_contract_is_unknown_2 = 7005,
        no_partial_match_found_for_this_fak_order = 7006,
        maximum_quantity_depth_for_any_one_price_group_max_may_not_exceed_integermax_value = 7008,
        contract_for_this_order_contract_is_past_expiration_date_and_may_no_longer_be_traded = 7009,
        invalid_spread_price = 7010,
        maximum_number_of_working_orders_for_this_contract_has_been_exceeded = 7011,
        order_would_overwrite_existing_order_on_book = 7012,
        order_group_does_not_match_group_of_contract = 7013,
        order_security_type_does_not_match_security_type_of_contract = 7014,
        order_modify_has_different_side_than_existing_order = 7015,
        contract_is_not_eligible_for_electronic_matching = 7017,
        order_contract_is_not_gtc_or_gtd_eligible = 7018,
        no_trading_calendar_found_on_or_after_order_gtd_expire_date = 7020,
        tag_expiredate_432_beyond_instrument_expiration = 7021,
        tag_expiredate_432_beyond_uds_combo_earliest_leg_expiration = 7022,
        order_cannot_be_modified_or_cancelled_while_the_market_is_in_no_cancel = 7024,
        order_type_not_permitted_while_the_market_is_reserved = 7027,
        order_session_date_is_in_the_past = 7028,
        orders_may_not_be_entered_while_the_market_is_forbidden = 7029,
        quote_rejected_exchange_security_is_forbidden = 7030,
        orders_may_not_be_entered_while_the_market_is_preclosed = 7031,
        quote_rejected_exchange_security_is_preclosed = 7032,
        orders_may_not_be_entered_while_the_market_is_open = 7033,
        quote_rejected_exchange_security_is_forbidden_2 = 7034,
        rfq_rejected_instrument_exchange_is_open = 7035,
        time_in_force_59_not_valid_for_order_type_40 = 7036,
        good_for_auction_order_not_allowed = 7037,
        on_close_order_not_allowed = 7038,
        duplicate_client_order_id_for_this_sessioncontract = 7039,
        good_for_auction_order_cancel_not_allowed = 7040,
        on_close_order_cancel_not_allowed = 7041,
        good_for_auction_order_modify_not_allowed = 7042,
        on_close_order_modify_not_allowed = 7043,
        modify_of_order_participating_in_top_not_allowed = 7044,
        cancel_of_order_participating_in_top_not_allowed = 7045,
        order_type_duration_combination_invalid_for_auction = 7046,
        order_type_duration_combination_invalid = 7047,
        quantity_attribute_not_allowed_on_order_during_auction = 7048,
        order_entry_was_unsuccessful_error_message_is_not_possible_to_send_orders_with_validity_type_market_on_auction_with_minimum_quantity = 7049,
        max_floor_111_not_valid_for_time_in_force_59 = 7050,
        spread_orders_may_not_be_entered_while_the_underlying_leg_market_is_in_non_trading_state = 7055,
        orders_may_not_be_entered_while_the_market_is_in_final_closing_call = 7056,
        quote_rejected_unknown_instrument = 7101,
        quote_rejected_exchange_security_closed = 7102,
        quote_rejected_quote_exceeds_limit = 7103,
        quote_rejected_too_late_to_enter = 7104,
        quote_rejected_unknown_quote = 7105,
        quote_rejected_duplicate_quote_in_same_message = 7106,
        quote_rejected_invalid_bidask_spread = 7107,
        quote_rejected_invalid_price = 7108,
        quote_rejected_not_authorized_to_quote_this_instrument = 7109,
        quote_rejected_resting_cancelled_too_many_rejects = 7110,
        quote_rejected_duplicate_quote_different_id = 7111,
        quote_rejected_resting_cancelled_quote_exceeds_limit = 7112,
        quote_rejected_resting_cancelled_duplicate_quote = 7113,
        quote_rejected_resting_cancelled_invalid_bidask_spread = 7114,
        quote_rejected_resting_cancelled_invalid_price = 7115,
        quote_rejected_resting_cancelled_not_authorized_to_quote_this_instrument = 7116,
        quote_rejected_unspecified_reason = 7117,
        quote_rejected_exchange_security_is_in_pre_open = 7118,
        quote_rejected_exchange_security_is_in_no_cancel = 7119,
        quote_rejected_exchange_security_is_reserved = 7120,
        contract_not_eligible_for_negotiated_quote = 7121,
        rlp_order_rejected_participant_not_authorized = 7122,
        attempt_to_modify_the_order_type_fromto_rlp = 7123,
        invalid_field_for_order_with_order_type_tag_40_equals_w_rlp = 7124,
        rlp_order_rejected_only_one_order_is_allowed_by_firm_and_side = 7125,
        invalid_field_for_order_with_routing_instruction_tag_35487_equals_1_retail_liquidity_taker = 7126,
        invalid_field_for_order_with_order_type_tag_40_equals_p_pegged = 7127,
        qty_is_not_multiple_of_minimum_execution_quantity_for_pegged_order = 7128,
        account_is_mandatory_for_pegged_order = 7129,
        pegged_order_can_not_be_sent_in_non_regular_session = 7130,
        attempt_to_modify_the_order_type_fromto_pegged = 7131,
        order_rejected_pegged_orders_are_not_allowed_for_this_contract = 7132,
        order_rejected_routing_instruction_tag_35487_equals_broker_only_3_not_allowed_for_this_group = 7133,
        order_rejected_only_pegged_order_with_routing_instruction_tag_35487_equals_broker_only_3_is_allowed_for_this_group = 7134,
        cross_order_suspended_for_the_participant_or_session = 7135,
        order_quantity_is_outside_of_the_allowable_range_order_quantity_orderqty_contract_minimum_quantity_for_cross_mincrossqty = 7136,
        bbt_messages_should_not_be_entered_when_market_is_paused = 7137,
        bbt_messages_should_not_be_entered_when_market_is_pre_open = 7138,
        bbt_messages_should_not_be_entered_when_market_is_pcp = 7139,
        bbt_messages_should_not_be_entered_when_market_is_no_cancel = 7140,
        bbt_messages_should_not_be_entered_when_market_is_reserved = 7141,
        bbt_messages_should_not_be_entered_when_market_is_forbidden = 7142,
        bbt_messages_should_not_be_entered_when_market_is_pre_close = 7143,
        invalid_field_for_bbt_order = 7144,
        for_cancel_on_behalf_must_be_informed_only_the_actiontargetsessionid_or_the_actiontargetgroupid = 7145,
        actiontargetgroupid_invalid_it_doesnt_exist_or_it_is_disabled = 7146,
        fix_session_is_blocked_due_to_mass_cancel = 7147,
        actiontargetgroupid_must_be_informed = 7148,
        fix_session_doesnt_belong_to_the_actiontargetgroupid = 7149,
        technical_error_function_not_performed = 9999,
        exercise_price_not_allowed = 8006,
        no_positions_blocked = 8007,
        quantity_doesnt_match_with_the_original_request_quantity_on_original_request_quantity_on_original_request = 8008,
        exercise_must_be_on_maturity_date = 8011,
        function_not_available_this_time = 8014,
        blocking_quantity_more_than_999999999 = 8015,
        trade_does_not_belong_to_the_specified_firm_firm_id_xxx = 8020,
        blocking_qty_more_than_available_quantity = 8021,
        there_arent_positions_available_to_exercise = 8022,
        total_qty_must_be_the_sum_of_all_allocqty = 8023,
        trade_already_cancelled_or_does_not_exist_trade_id_xxx = 8024,
        available_quantity_to_block_is_zero = 8027,
        invalid_operation_for_contract_type = 8028,
        function_closed_or_suspended = 8036,
        exercise_price_outside_required_moneyness = 8039,
        invalid_exercise_request_id_to_cancel = 8040,
        invalid_blocking_id_to_unblock = 8059,
        invalid_quantity_to_unblock = 8062,
        on_behalf_operation_not_allowed_during_ccr_recovery = 8063,
        problem_parsing_incoming_message = 8065,
        exercise_quantity_should_be_greater_than_zero = 8066,
        system_initialization = 30002,
        line_busy = 30003,
        message_or_atributes_are_invalid = 30004,
        internal_error = 30005,
        timeout_waiting_risk_evaluation = 30006,
        timeout_waiting_risk_evaluation_low_priority = 30007,
        broker_negotiation_blocked = 30011,
        broker_not_available = 30012,
        brokers_capture_account_not_found = 30013,
        brokers_segment_negotiation_blocked = 30014,
        broker_segment_not_available = 30015,
        brokers_segment_protected_mode_under_activation = 30016,
        broker_pn_negotiation_blocked = 30017,
        broker_pn_not_available = 30018,
        broker_pn_protected_mode_under_activation = 30019,
        account_negotiation_blocked = 30021,
        account_not_available = 30022,
        accounts_protected_mode_under_activation = 30023,
        account_mandatory_on_dma_orders = 30024,
        transient_account_is_hierarchically_blocked_on_protected_mode = 30025,
        crossorders_or_crossforward_not_allowed_while_account_in_protected_mode = 30026,
        transient_account_not_allowed_in_extended_hours = 30027,
        document_negotiation_blocked = 30031,
        document_not_available = 30032,
        documents_protected_mode_under_activation = 30033,
        executor_document_cannot_use_default_broker_profile = 30034,
        document_in_blocked_profile = 30035,
        crossorders_or_crossforward_not_allowed_while_document_in_protected_mode = 30036,
        entering_trader_negotiation_blocked = 30041,
        entering_trader_not_available = 30042,
        entering_trader_blocked_by_sfd_overflow = 30043,
        non_dma_orders_must_provide_account_while_in_brokers_protected_mode = 30044,
        entering_trader_not_authorized_to_trade_accountless_orders = 30045,
        entering_trader_cannot_trade_on_behalf_of_other_firms_account = 30046,
        symbol_not_available = 30050,
        symbol_internal_data_corrupted = 30051,
        fix_message_type_does_not_support_operations_on_such_symbol = 30052,
        symbols_underlying_not_found_for_risk_aggregation = 30053,
        symbols_risk_unit_matrix_not_available = 30054,
        symbols_reference_price_missing_market_orders_not_allowed = 30055,
        symbols_calculated_price_invalid = 32056,
        spreads_leg_not_available = 30060,
        spreads_leg_internal_data_corrupted = 30061,
        unexpected_internal_error_during_risk_evaluation = 30070,
        sfd_broker_pn_pn_document_aggregation_day_trade_cash_balance_stop_loss_not_configured = 30113,
        sdp_broker_pn_pn_document_aggregation_order_exceeded_cash_settlement_exposure = 30114,
        rmkt_broker_pn_pn_document_aggregation_order_quantity_exceeded_risk_increase = 30115,
        sdp_broker_pn_pn_trader_aggregation_order_exceeded_cash_settlement_exposure = 30116,
        spvd_broker_pn_pn_document_aggregation_order_exceeded_potential_short_uncovered_balance = 30117,
        spvd_broker_pn_pn_trader_aggregation_order_exceeded_potential_short_uncovered_balance = 30118,
        rmse_broker_pn_pn_document_aggregation_order_exceeded_risk_increase_at_extended_session = 30119,
        rmse_broker_order_exceeded_risk_increase_at_extended_session = 30166,
        mkta_account_buy_not_allowed_for_symbols_market = 30201,
        mkta_account_sell_not_allowed_for_symbols_market = 30202,
        tmoc_account_maximum_order_size_exceeded_for_single_order = 30204,
        tmov_account_maximum_order_size_exceeded_for_single_order = 30205,
        spci_account_order_quantity_exceeded_short_position_per_instrument = 30206,
        spvi_account_order_quantity_exceeded_long_position_per_instrument = 30207,
        sdp_account_order_exceeded_cash_settlement_exposure = 30208,
        rmkt_account_order_quantity_exceeded_risk_increase = 30210,
        irmkt_account_order_quantity_exceeded_risk_increase_reducing_mode = 30211,
        spi_account_order_quantity_exceeded_long_and_short_position_reducing_mode = 30212,
        std_account_termo_not_allowed_protected_mode_enabled = 30213,
        spvd_account_order_exceeded_potential_short_uncovered_balance = 30215,
        mkta_document_buysell_symbols_market_not_configured = 30300,
        mkta_document_buy_not_allowed_for_symbols_market = 30301,
        mkta_document_sell_not_allowed_for_symbols_market = 30302,
        tmox_document_max = 30303,
        tmoc_document_max_bid_quantity_exceeded_for_single_order = 30304,
        tmov_document_max_offer_quantity_exceeded_for_single_order = 30305,
        spci_document_order_quantity_exceeded_max_bid_potential_balance = 30306,
        spvi_document_order_quantity_exceeded_max_offer_potential_balance = 30307,
        sdp_document_order_exceeded_max_financial_potential_balance_due = 30308,
        std_document_order_quantity_exceeded_max_operations_forward_balance = 30309,
        rmkt = 30310,
        irmkt_document_order_quantity_exceeded_max_incremental_market_risk = 30311,
        spi_document_order_quantity_exceeded_previous_potencial_balance = 30312,
        std_document_termo_not_allowed = 30313,
        sfd_document_day_trade_cash_balance_stop_loss_not_configured = 30314,
        spvd_document_order_exceeded_potential_short_uncovered_balance = 30315,
        rmse_document_order_exceeded_risk_increase_at_extended_session = 30316,
        rmse_document_order_exceeded_risk_increase_of_broker_at_extended_session = 30317,
        mkta_entering_trader_buysell_symbols_market_not_configured = 30400,
        mkta_entering_trader_buy_not_allowed_for_symbols_market = 30401,
        mkta_entering = 30402,
        tmox_entering_trader_max_bidoffer_quantity_not_configured = 30403,
        tmoc_entering_trader_max_bid_quantity_exceeded_for_single_order = 30404,
        tmov_entering_trader_max_offer_quantity_exceeded_for_si = 30405,
        spci_entering_trader_order_quantity_exceeded_max_bid_potential_balance = 30406,
        spvi_entering_trader_order_quantity_exceeded_max_offer_potential_balance = 30407,
        sdp_entering_trader_order_exceeded_max_financial_potential = 30408,
        spvd_trader_order_exceeded_potential_short_uncovered_balance = 30415,
        oms_unexpected_internal_error = 30500,
        oms_invalid_session_or_symbol = 30501,
        oms_clordid_cannot_be_empty = 30502,
        oms_clordid_is_duplicated = 30503,
        oms_clordid_not_found = 30504,
        oms_origclordid_cannot_be_empty = 30505,
        oms_crossid_cannot_be_empty = 30506,
        oms_clordid_is_duplicated_within_cross_order = 30507,
        oms_cross_order_modification_is_not_allowed = 30508,
        oms_orderid_not_found = 30509,
        oms_orderid_cannot_be_empty = 30510,
        oms_quotereqid_cannot_be_empty = 30511,
        oms_quotereqid_is_duplicated = 30512,
        oms_quotereqid_not_found = 30513,
        oms_quoteid_cannot_be_empty = 30514,
        oms_in = 30521,
        oms = 30522,
        oms_entering_firm_modification_is_not_allowed = 30523,
        oms_account_modification_on_dma_order_is_not_allowed = 30524,
        oms_account_information_missing_on_non = 30525,
        oms_entering_trader = 30526,
        oms_received_execution_report_rejection_for_an_active_order = 30527,
        broker_negotiation_blocked_2 = 31011,
        broker_not_available_2 = 31012,
        brokers_capture_account_not_found_2 = 31013,
        brokers_segment_negotiation_blocked_2 = 31014,
        broker_segment_not_available_2 = 31015,
        brokers_segment_protected_mode_under_activation_2 = 31016,
        account_negotiation_blocked_2 = 31021,
        account_not_available_2 = 31022,
        accounts_protected_mode_under_activation_2 = 31023,
        account_mandatory_on_dma_orders_2 = 31024,
        transient_account_is_hierarchically_blocked_on_protected_mode_2 = 31025,
        crossorders_or_crossforward_not_allowed_while_account_in_protected_mode_2 = 31026,
        transient_account_not_allowed_in_extended_hours_2 = 31027,
        document_negotiation_blocked_2 = 31031,
        document_not_available_2 = 31032,
        documents_protected_mode_under_activation_2 = 31033,
        executor_document_cannot_use_default_broker_profile_2 = 31034,
        document_in_blocked_profile_2 = 31035,
        crossorders_or_crossforward_not_allowed_while_document_in_protected_mode_2 = 31036,
        entering_trader_negotiation_blocked_2 = 31041,
        entering_trader_not_available_2 = 31042,
        entering_trader_blocked_by_sfd_overflow_2 = 31043,
        non_dma_orders_must_provide_account_while_in_brokers_protected_mode_2 = 31044,
        entering_trader_not_authorized_to_trade_accountless_orders_2 = 31045,
        entering_trader_cannot_trade_on_behalf_of_other_firms_account_2 = 31046,
        symbol_not_available_2 = 31050,
        symbol_internal_data_corrupted_2 = 31051,
        fix_message_type_does_not_support_operations_on_such_symbol_2 = 31052,
        symbols_underlying_not_found_for_risk_aggregation_2 = 31053,
        symbols_risk_unit_matrix_not_available_2 = 31054,
        symbols_reference_price_missing_market_orders_not_allowed_2 = 31055,
        symbols_calculated_price_invalid_2 = 31056,
        spreads_leg_not_available_2 = 31060,
        spreads_leg_internal_data_corrupted_2 = 31061,
        unexpected_internal_error_during_risk_evaluation_2 = 31070,
        mkta_account_buy_not_allowed_for_symbols_market_2 = 31201,
        mkta_account_sell_not_allowed_for_symbols_market_2 = 31202,
        tmoc_account_max_bid_quantity_exceeded_for_single_order = 31204,
        tmov_account_max_offer_quantity_exceeded_for_single_order = 31205,
        spci_account_order_quantity_exceeded_max_bid_potential_balance = 31206,
        spvi_account_order_quantity_exceeded_max_offer_potential_balance = 31207,
        sdp_account_order_exceeded_max_financial_potential_balance_due = 31208,
        rmkt_account_order_quantity_exceeded_max_market_risk = 31210,
        irmkt_account_order_quantity_exceeded_max_incremental_market_risk = 31211,
        spi_account_order_quantity_exceeded_previous_potencial_balance = 31212,
        std_account_termo_not_allowed_protected_mode_enabled_2 = 31213,
        spvd_account_order_exceeded_potential_short_uncovered_balance_2 = 31215,
        mkta_document_buysell_symbols_market_not_configured_2 = 31300,
        mkta_document_buy_not_allowed_for_symbols_market_2 = 31301,
        mkta_document_sell_not_allowed_for_symbols_market_2 = 31302,
        tmox_document_maximum_order_size_not_configured = 31303,
        tmoc_document_maximum_order_size_exceeded_for_single_order = 31304,
        tmov_document_maximum_order_size_exceeded_for_single_order = 31305,
        spci_document_order_quantity_exceeded_short_position_per_instrument = 31306,
        spvi_document_order_quantity_exceeded_long_position_per_instrument = 31307,
        sdp_document_order_exceeded_cash_settlement_exposure = 31308,
        std_document_order_quantity_exceeded_forward_contracts_exposure = 31309,
        rmkt_document_order_quantity_exceeded_risk_increase = 31310,
        irmkt_document_order_quantity_exceeded_risk_increase_reducing_mode = 31311,
        spi_document_order_quantity_exceeded_long_and_short_position_reducing_mode = 31312,
        std_document_termo_not_allowed_protected_mode_enabled = 31313,
        sfd_document_day_trade_cash_balance_stop_loss_not_configured_2 = 31314,
        spvd_document_order_exceeded_potential_short_uncovered_balance_2 = 31315,
        rmse_document_order_exceeded_risk_increase_at_extended_session_2 = 31316,
        rmse_document_order_exceeded_risk_increase_of_broker_at_extended_session_2 = 31317,
        mkta_entering_trader_buysell_symbols_market_not_configured_2 = 31400,
        mkta_entering_trader_buy_not_allowed_for_symbols_market_2 = 31401,
        mkta_entering_trader_sell_not_allowed_for_symbols_market = 31402,
        tmox_entering_trader_maximum_order_size_not_configured = 31403,
        tmoc_entering_trader_maximum_order_size_exceeded_for_single_order = 31404,
        tmov_entering_trader_maximum_order_size_exceeded_for_single_order = 31405,
        spci_entering_trader_order_quantity_exceeded_short_position_per_instrument = 31406,
        spvi_entering_trader_order_quantity_exceeded_long_position_per_instrument = 31407,
        sdp_entering_trader_order_exceeded_cash_settlement_exposure = 31408,
        oms_unexpected_internal_error_2 = 31500,
        oms_invalid_session_or_symbol_2 = 31501,
        oms_clordid_cannot_be_empty_2 = 31502,
        oms_clordid_is_duplicated_2 = 31503,
        oms_clordid_not_found_2 = 31504,
        oms_origclordid_cannot_be_empty_2 = 31505,
        oms_crossid_cannot_be_empty_2 = 31506,
        oms_clordid_is_duplicated_within_cross_order_2 = 31507,
        oms_cross_order_modification_is_not_allowed_2 = 31508,
        oms_orderid_not_found_2 = 31509,
        oms_orderid_cannot_be_empty_2 = 31510,
        oms_quotereqid_cannot_be_empty_2 = 31511,
        oms_quotereqid_is_duplicated_2 = 31512,
        oms_quotereqid_not_found_2 = 31513,
        oms_quoteid_cannot_be_empty_2 = 31514,
        oms_inflight_modification_is_not_allowed = 31521,
        oms_side_modification_is_not_allowed = 31522,
        oms_entering_firm_modification_is_not_allowed_2 = 31523,
        oms_account_modification_on_dma_order_is_not_allowed_2 = 31524,
        oms_account_information_missing_on_nondma_order = 31525,
        oms_entering_trader_modification_on_nondma_order_is_not_allowed = 31526,
        oms_received_execution_report_rejection_for_an_active_order_2 = 31527,
        field_missing_or_incorrect = 32000,
        line_not_available_or_busy = 32001,
        line_internal_error = 32002,
        line_recovering_or_starting_up = 32003,
        internal_gateway_error_message_forwarding_failure = 32004,
        invalid_quantity = 32005,
        duplicate_order = 32006,
        missing_account_field = 32007,
        unknown_account = 32008,
        unknown_firmid_for_routing = 32009,
        duplicate_firmid = 32010,
        duplicate_sender_location = 32011,
        duplicate_entering_trader = 32012,
        firm_or_trader_is_missing_in_nondma_order = 32013,
        firm_or_account_is_missing_in_dma_order = 32014,
        same_participants_on_both_sides_or_invalid_sides = 32015,
        buy_side_and_sell_side_having_different_firmids = 32016,
        buy_side_and_sell_side_trading_different_assets = 32017,
        invalid_price_2 = 32018,
        line_overloaded = 32019,
        line_administratively_blocked = 32020,
        invalid_price_3 = 32021,
        system_overloaded = 32022,
        system_error = 32023,
        throttle_limit_reached = 33000,
        invalid_security_id = 33001,
        unknown_market_segment_id = 33002,
        field_missing_or_incorrect_2 = 33003,
        system_error_2 = 33050,
    };

    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return tmp::ordered<order>(value_); }

  protected:
    std::underlying_type_t<type> value_;
};

// Ord Status: ordStatus
struct ord_status {
    enum class type : char {
        new_value = '0',
        partially_filled = '1',
        filled = '2',
        canceled = '4',
        replaced = '5',
        rejected = '8',
        expired = 'C',
        restated = 'R',
        previous_final_state = 'Z',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Order Category: orderCategory
struct order_category {
    enum class type : char {
        result_of_options_exercise = 'B',
        result_of_assignment_from_an_options_exercise = 'C',
        result_of_automatic_options_exercise = 'D',
        result_of_midpoint_order = 'E',
        result_of_block_book_trade = 'F',
        result_of_trade_at_close = 'G',
        result_of_trade_at_average = 'H',
    };

    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>('0');

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Order Id: orderID
struct order_id {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Order Id Optional: orderID
struct order_id_optional {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Order Qty: orderQty
struct order_qty {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Order Qty Optional: orderQty
struct order_qty_optional {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// OrdTagId
struct ordtagid {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(0ULL);

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// OrdType
struct ordtype {
    enum class type : char {
        market = '1',
        limit = '2',
        stop_loss = '3',
        stop_limit = '4',
        market_with_leftover_as_limit = 'K',
        rlp = 'W',
        pegged_midpoint = 'P',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Orig Pos Req Ref Id: origPosReqRefID
struct orig_pos_req_ref_id {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// OrigClOrdId
struct origclordid {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Padding
struct padding {
    using type = char;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    char value_;
};

// Padding 1: 1 bytes padding
struct padding_1 {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Pos Maint Action: posMaintAction
struct pos_maint_action {
    enum class type : char {
        new_value = '1',
        cancel = '3',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Pos Maint Result: posMaintResult
struct pos_maint_result {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Pos Maint Rpt Id: posMaintRptID
struct pos_maint_rpt_id {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Pos Maint Rpt Ref Id: posMaintRptRefID
struct pos_maint_rpt_ref_id {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Pos Maint Status: posMaintStatus
struct pos_maint_status {
    enum class type : char {
        accepted = '0',
        rejected = '2',
        completed = '3',
        not_executed = '9',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Pos Req Id: posReqID
struct pos_req_id {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Pos Req Id Optional: posReqID
struct pos_req_id_optional {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Pos Trans Type: posTransType
struct pos_trans_type {
    enum class type : std::uint8_t {
        exercise = 1,
        automatic_exercise = 105,
        exercise_not_automatic = 106,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Pos Type: Used to identify the type of quantity.
struct pos_type {
    enum class type : char {
        transaction_quantity = 'T',
        start_of_day_qty = 'S',
        option_exercise_qty = 'E',
        blocked_qty = 'B',
        uncovered_qty = 'U',
        covered_qty = 'C',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Poss Resend: possResend
struct poss_resend {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Prefix
struct prefix {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Price
struct price {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Price Optional: price
struct price_optional {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(-9223372036854775807LL - 1);
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Protection Price: protectionPrice
struct protection_price {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(-9223372036854775807LL - 1);
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Quantity
struct quantity {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Quote Id: quoteID
struct quote_id {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Quote Id Optional: quoteID
struct quote_id_optional {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Quote Reject Reason: quoteRejectReason
struct quote_reject_reason {
    enum class type : std::uint32_t {
        technical_error_function_not_performed = 9999,
        exercise_price_not_allowed = 8006,
        no_positions_blocked = 8007,
        quantity_doesnt_match_with_the_original_request_quantity_on_original_request_quantity_on_original_request = 8008,
        exercise_must_be_on_maturity_date = 8011,
        function_not_available_this_time = 8014,
        blocking_quantity_more_than_999999999 = 8015,
        trade_does_not_belong_to_the_specified_firm_firm_id_xxx = 8020,
        blocking_qty_more_than_available_quantity = 8021,
        there_arent_positions_available_to_exercise = 8022,
        total_qty_must_be_the_sum_of_all_allocqty = 8023,
        trade_already_cancelled_or_does_not_exist_trade_id_xxx = 8024,
        available_quantity_to_block_is_zero = 8027,
        invalid_operation_for_contract_type = 8028,
        function_closed_or_suspended = 8036,
        exercise_price_outside_required_moneyness = 8039,
        invalid_exercise_request_id_to_cancel = 8040,
        invalid_blocking_id_to_unblock = 8059,
        invalid_quantity_to_unblock = 8062,
        on_behalf_operation_not_allowed_during_ccr_recovery = 8063,
        problem_parsing_incoming_message = 8065,
        exercise_quantity_should_be_greater_than_zero = 8066,
        contrary_exercise_already_registered_for_this_position = 8069,
        inthemoney_contract_allows_contrary_exercise_to_not_exercise_automatically_only = 8070,
        atoutthemoney_contract_allows_contrary_exercise_to_exercise_automatically_only = 8071,
        dma_is_not_allowed_to_request_contrary_exercise = 8072,
        contrary_exercises_can_only_be_requested_by_default_link_or_position_owner_with_direct_access_on_absence_of_default_link = 8073,
        contrary_exercise_invalid_operation = 8074,
        threshold_must_not_be_informed = 8075,
    };

    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0);

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return tmp::ordered<order>(value_); }

  protected:
    std::underlying_type_t<type> value_;
};

// Quote Req Id Data
struct quote_req_id_data {
    using type = std::string_view;
    static constexpr bool dynamic = true;

    constexpr quote_req_id_data(const std::byte* data, std::size_t length) noexcept : data_{ data }, length_{ length } {}

    constexpr type value() const noexcept { return { reinterpret_cast<const char*>(data_), length_ }; }
    constexpr operator type() const noexcept { return value(); }
    // the bytes it takes
    constexpr std::size_t length() const noexcept { return length_; }

  protected:
    const std::byte* data_;
    std::size_t length_;
};

// Quote Req Id Length
struct quote_req_id_length {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Quote Request Reject Reason: quoteRequestRejectReason
struct quote_request_reject_reason {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Quote Status: quoteStatus
struct quote_status {
    enum class type : std::uint8_t {
        expired = 7,
        accepted = 0,
        rejected = 5,
        quote_not_found = 9,
        pending = 10,
        pass = 11,
        canceled = 17,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Quote Status Response To: quoteStatusResponseTo
struct quote_status_response_to {
    enum class type : char {
        quote = '0',
        quote_request = '1',
        quote_cancel = '2',
        quote_request_reject = '3',
    };

    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>('0');

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Ref Msg Type: refMsgType
struct ref_msg_type {
    enum class type : std::uint8_t {
        negotiate = 0,
        negotiate_response = 1,
        negotiate_reject = 2,
        establish = 3,
        establish_ack = 4,
        establish_reject = 5,
        terminate = 6,
        not_applied = 9,
        retransmit_request = 10,
        retransmission = 11,
        retransmit_reject = 12,
        sequence = 13,
        business_message_reject = 14,
        simple_new_order = 15,
        simple_modify_order = 16,
        new_order_single = 17,
        order_cancel_replace_request = 18,
        order_cancel_request = 19,
        new_order_cross = 20,
        execution_report_new = 21,
        execution_report_modify = 22,
        execution_report_cancel = 23,
        execution_report_trade = 24,
        execution_report_reject = 25,
        execution_report_forward = 26,
        security_definition_request = 27,
        security_definition_response = 28,
        order_mass_action_request = 29,
        order_mass_action_report = 30,
        quote_request = 31,
        quote_status_report = 32,
        quote = 33,
        quote_cancel = 34,
        quote_request_reject = 35,
        position_maintenance_cancel_request = 36,
        position_maintenance_request = 37,
        position_maintenance_report = 38,
        allocation_instruction = 39,
        allocation_report = 40,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Ref Seq Num: refSeqNum
struct ref_seq_num {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Request Timestamp: requestTimestamp
struct request_timestamp {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Retransmit Reject Code: retransmitRejectCode
struct retransmit_reject_code {
    enum class type : std::uint8_t {
        out_of_range = 0,
        invalid_session = 1,
        request_limit_exceeded = 2,
        retransmit_in_progress = 3,
        invalid_timestamp = 4,
        invalid_fromseqno = 5,
        invalid_count = 9,
        throttle_reject = 10,
        system_busy = 11,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Routing Instruction: routingInstruction
struct routing_instruction {
    enum class type : std::uint8_t {
        retail_liquidity_taker = 1,
        waived_priority = 2,
        broker_only = 3,
        broker_only_removal = 4,
    };

    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(0);

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Schema Id: Identifier of the schema publishing the message
struct schema_id {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Secondary Exec Id: secondaryExecID
struct secondary_exec_id {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Secondary Order Id: secondaryOrderID
struct secondary_order_id {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Secondary Order Id Optional: secondaryOrderID
struct secondary_order_id_optional {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Security Id: securityID
struct security_id {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Security Id Optional: securityID
struct security_id_optional {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Security Req Id: securityReqID
struct security_req_id {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Security Response Id: securityResponseID
struct security_response_id {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Security Response Type: securityResponseType
struct security_response_type {
    enum class type : std::uint8_t {
        accept_security_proposal_as_is = 1,
        reject_security_proposal = 5,
        accept_security_as_proposal_with_revisions = 2,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Security Strategy Type: securityStrategyType
struct security_strategy_type {
    using type = std::string_view;
    static constexpr std::size_t size = 3;
    static constexpr char fill = '\0';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 3> value_;
};

// Self Trade Prevention Instruction: selfTradePreventionInstruction
struct self_trade_prevention_instruction {
    enum class type : std::uint8_t {
        none = 0,
        cancel_aggressor_order = 1,
        cancel_resting_order = 2,
        cancel_both_orders = 3,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Sender Location: senderLocation
struct sender_location {
    using type = std::string_view;
    static constexpr std::size_t size = 10;
    static constexpr char fill = '\0';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 10> value_;
};

// Sending Time: sendingTime
struct sending_time {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Session Id: sessionID
struct session_id {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Session Ver Id: sessionVerID
struct session_ver_id {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Settl Type: settlType
struct settl_type {
    enum class type : char {
        buyers_discretion = '0',
        sellers_discretion = '8',
        mutual = 'X',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Settl Type Optional: settlType
struct settl_type_optional {
    enum class type : char {
        buyers_discretion = '0',
        sellers_discretion = '8',
        mutual = 'X',
    };

    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>('0');

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Short Qty: Short Quantity.
struct short_qty {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Side
struct side {
    enum class type : char {
        buy = '1',
        sell = '2',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Side Optional: side
struct side_optional {
    enum class type : char {
        buy = '1',
        sell = '2',
    };

    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>('0');

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Simple OrdType: ordType
struct simple_ordtype {
    enum class type : char {
        market = '1',
        limit = '2',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Single Cancel Restatement Reason: execRestatementReason
struct single_cancel_restatement_reason {
    enum class type : std::uint8_t {
        cancel_order_due_to_operational_error = 203,
    };

    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(0);

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Stop Px: stopPx
struct stop_px {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(-9223372036854775807LL - 1);
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Symbol
struct symbol {
    using type = std::string_view;
    static constexpr std::size_t size = 20;
    static constexpr char fill = '\0';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 20> value_;
};

// Template Id: Template ID used to encode the message
struct template_id {
    enum class type : std::uint16_t {
        negotiate_message = 1,
        negotiate_response_message = 2,
        negotiate_reject_message = 3,
        establish_message = 4,
        establish_ack_message = 5,
        establish_reject_message = 6,
        terminate_message = 7,
        not_applied_message = 8,
        sequence_message = 9,
        retransmit_request_message = 12,
        retransmission_message = 13,
        retransmit_reject_message = 14,
        simple_new_order_message = 100,
        simple_modify_order_message = 101,
        new_order_single_message = 102,
        order_cancel_replace_request_message = 104,
        order_cancel_request_message = 105,
        new_order_cross_message = 106,
        execution_report_new_message = 200,
        execution_report_modify_message = 201,
        execution_report_cancel_message = 202,
        execution_report_trade_message = 203,
        execution_report_reject_message = 204,
        execution_report_forward_message = 205,
        business_message_reject_message = 206,
        security_definition_request_message = 300,
        security_definition_response_message = 301,
        quote_request_message = 401,
        quote_status_report_message = 402,
        quote_message = 403,
        quote_cancel_message = 404,
        quote_request_reject_message = 405,
        position_maintenance_cancel_request_message = 501,
        position_maintenance_request_message = 502,
        position_maintenance_report_message = 503,
        allocation_instruction_message = 601,
        allocation_report_message = 602,
        order_mass_action_request_message = 701,
        order_mass_action_report_message = 702,
    };

    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return tmp::ordered<order>(value_); }

  protected:
    std::underlying_type_t<type> value_;
};

// Termination Code: terminationCode
struct termination_code {
    enum class type : std::uint8_t {
        unspecified = 0,
        finished = 1,
        unnegotiated = 2,
        not_established = 3,
        session_blocked = 4,
        negotiation_in_progress = 5,
        establish_in_progress = 6,
        keepalive_interval_lapsed = 10,
        invalid_sessionid = 11,
        invalid_sessionverid = 12,
        invalid_timestamp = 13,
        invalid_nextseqno = 14,
        unrecognized_message = 15,
        invalid_sofh = 16,
        decoding_error = 17,
        terminate_not_allowed = 20,
        terminate_in_progress = 21,
        protocol_version_not_supported = 23,
        backup_takeover_in_progress = 30,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Text Data: Free ASCII format text string generated by exchange.
struct text_data {
    using type = std::string_view;
    static constexpr bool dynamic = true;

    constexpr text_data(const std::byte* data, std::size_t length) noexcept : data_{ data }, length_{ length } {}

    constexpr type value() const noexcept { return { reinterpret_cast<const char*>(data_), length_ }; }
    constexpr operator type() const noexcept { return value(); }
    // the bytes it takes
    constexpr std::size_t length() const noexcept { return length_; }

  protected:
    const std::byte* data_;
    std::size_t length_;
};

// Text Length: Length of free format text string generated by exchange.
struct text_length {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Threshold Amount: thresholdAmount
struct threshold_amount {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(-9223372036854775807LL - 1);
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Time In Force: timeInForce
struct time_in_force {
    enum class type : char {
        day = '0',
        good_till_cancel = '1',
        immediate_or_cancel = '3',
        fill_or_kill = '4',
        good_till_date = '6',
        at_the_close = '7',
        good_for_auction = 'A',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Time In Force Optional: timeInForce
struct time_in_force_optional {
    enum class type : char {
        day = '0',
        good_till_cancel = '1',
        immediate_or_cancel = '3',
        fill_or_kill = '4',
        good_till_date = '6',
        at_the_close = '7',
        good_for_auction = 'A',
    };

    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>('0');

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Time In Force Simple: timeInForce
struct time_in_force_simple {
    enum class type : char {
        day = '0',
        immediate_or_cancel = '3',
        fill_or_kill = '4',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Timestamp
struct timestamp {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Tot No Related Sym: totNoRelatedSym
struct tot_no_related_sym {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(0ULL);

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Trade Date: tradeDate
struct trade_date {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Trade Date Optional: tradeDate
struct trade_date_optional {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Trade Id: tradeID
struct trade_id {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Trade Id Optional: tradeID
struct trade_id_optional {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Transact Time: transactTime
struct transact_time {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Version: Schema version
struct version {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Working Indicator: workingIndicator
struct working_indicator {
    enum class type : std::uint8_t {
        false_value = 0,
        true_value = 1,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};


/////////////////////////////////////////////////////////////////////
// Messages
/////////////////////////////////////////////////////////////////////

#pragma pack(push, 1)

// Text Section 1
struct text_section_1 {
    static constexpr std::string_view name = "Text Section 1";
    static constexpr std::size_t size = 1;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        text_length>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYENTRYPOINTFIELD(text_length);
};

static_assert(sizeof(text_section_1) == text_section_1::size, "text_section_1 lies over its bytes exactly");

// Text: text data struct
struct text {
    static constexpr std::string_view name = "Text";
    static constexpr bool is_message = false;
};

// Investor Id: SimpleNewOrderMessage
struct investor_id {
    static constexpr std::string_view name = "Investor Id";
    static constexpr std::size_t size = 8;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        prefix,
        offset_2_padding_2,
        document>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYENTRYPOINTFIELD(prefix);
    BINARYENTRYPOINTFIELD(offset_2_padding_2);
    BINARYENTRYPOINTFIELD(document);
};

static_assert(sizeof(investor_id) == investor_id::size, "investor_id lies over its bytes exactly");

// Outbound Business Header: OutboundBusinessHeader
struct outbound_business_header {
    static constexpr std::string_view name = "Outbound Business Header";
    static constexpr std::size_t size = 18;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        session_id,
        msg_seq_num,
        sending_time,
        poss_resend,
        padding>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYENTRYPOINTFIELD(session_id);
    BINARYENTRYPOINTFIELD(msg_seq_num);
    BINARYENTRYPOINTFIELD(sending_time);
    BINARYENTRYPOINTFIELD(poss_resend);
    BINARYENTRYPOINTFIELD(padding);
};

static_assert(sizeof(outbound_business_header) == outbound_business_header::size, "outbound_business_header lies over its bytes exactly");

// Order Mass Action Report Message Section 1
struct order_mass_action_report_message_section_1 {
    static constexpr std::string_view name = "Order Mass Action Report Message Section 1";
    static constexpr std::size_t size = 72;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        outbound_business_header,
        mass_action_type,
        mass_action_scope,
        clordid,
        mass_action_report_id,
        transact_time,
        mass_action_response,
        mass_action_reject_reason,
        mass_cancel_restatement_reason,
        ordtagid,
        side_optional,
        offset_49_padding_1,
        asset,
        security_id_optional,
        investor_id>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYENTRYPOINTFIELD(outbound_business_header);
    BINARYENTRYPOINTFIELD(mass_action_type);
    BINARYENTRYPOINTFIELD(mass_action_scope);
    BINARYENTRYPOINTFIELD(clordid);
    BINARYENTRYPOINTFIELD(mass_action_report_id);
    BINARYENTRYPOINTFIELD(transact_time);
    BINARYENTRYPOINTFIELD(mass_action_response);
    BINARYENTRYPOINTFIELD(mass_action_reject_reason);
    BINARYENTRYPOINTFIELD(mass_cancel_restatement_reason);
    BINARYENTRYPOINTFIELD(ordtagid);
    BINARYENTRYPOINTFIELD(side_optional);
    BINARYENTRYPOINTFIELD(offset_49_padding_1);
    BINARYENTRYPOINTFIELD(asset);
    BINARYENTRYPOINTFIELD(security_id_optional);
    BINARYENTRYPOINTFIELD(investor_id);
};

static_assert(sizeof(order_mass_action_report_message_section_1) == order_mass_action_report_message_section_1::size, "order_mass_action_report_message_section_1 lies over its bytes exactly");

// Order Mass Action Report Message: OrderMassActionReportMessage
struct order_mass_action_report_message {
    static constexpr std::string_view name = "Order Mass Action Report Message";
    static constexpr bool is_message = true;
};

// Inbound Business Header: InboundBusinessHeader
struct inbound_business_header {
    static constexpr std::string_view name = "Inbound Business Header";
    static constexpr std::size_t size = 18;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        session_id,
        msg_seq_num,
        sending_time,
        market_segment_id,
        padding>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYENTRYPOINTFIELD(session_id);
    BINARYENTRYPOINTFIELD(msg_seq_num);
    BINARYENTRYPOINTFIELD(sending_time);
    BINARYENTRYPOINTFIELD(market_segment_id);
    BINARYENTRYPOINTFIELD(padding);
};

static_assert(sizeof(inbound_business_header) == inbound_business_header::size, "inbound_business_header lies over its bytes exactly");

// Order Mass Action Request Message: OrderMassActionRequestMessage
struct order_mass_action_request_message {
    static constexpr std::string_view name = "Order Mass Action Request Message";
    static constexpr std::size_t size = 54;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        inbound_business_header,
        mass_action_type,
        mass_action_scope,
        clordid,
        mass_cancel_restatement_reason,
        ordtagid,
        side_optional,
        offset_31_padding_1,
        asset,
        security_id_optional,
        investor_id>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYENTRYPOINTFIELD(inbound_business_header);
    BINARYENTRYPOINTFIELD(mass_action_type);
    BINARYENTRYPOINTFIELD(mass_action_scope);
    BINARYENTRYPOINTFIELD(clordid);
    BINARYENTRYPOINTFIELD(mass_cancel_restatement_reason);
    BINARYENTRYPOINTFIELD(ordtagid);
    BINARYENTRYPOINTFIELD(side_optional);
    BINARYENTRYPOINTFIELD(offset_31_padding_1);
    BINARYENTRYPOINTFIELD(asset);
    BINARYENTRYPOINTFIELD(security_id_optional);
    BINARYENTRYPOINTFIELD(investor_id);
};

static_assert(sizeof(order_mass_action_request_message) == order_mass_action_request_message::size, "order_mass_action_request_message lies over its bytes exactly");

// Allocation Report Message: AllocationReportMessage
struct allocation_report_message {
    static constexpr std::string_view name = "Allocation Report Message";
    static constexpr std::size_t size = 84;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        outbound_business_header,
        alloc_id,
        security_id,
        alloc_report_id,
        alloc_trans_type,
        alloc_report_type,
        alloc_no_orders_type,
        alloc_rej_code,
        quantity,
        alloc_status,
        trade_date_optional,
        transact_time,
        side,
        sender_location,
        entering_trader>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYENTRYPOINTFIELD(outbound_business_header);
    BINARYENTRYPOINTFIELD(alloc_id);
    BINARYENTRYPOINTFIELD(security_id);
    BINARYENTRYPOINTFIELD(alloc_report_id);
    BINARYENTRYPOINTFIELD(alloc_trans_type);
    BINARYENTRYPOINTFIELD(alloc_report_type);
    BINARYENTRYPOINTFIELD(alloc_no_orders_type);
    BINARYENTRYPOINTFIELD(alloc_rej_code);
    BINARYENTRYPOINTFIELD(quantity);
    BINARYENTRYPOINTFIELD(alloc_status);
    BINARYENTRYPOINTFIELD(trade_date_optional);
    BINARYENTRYPOINTFIELD(transact_time);
    BINARYENTRYPOINTFIELD(side);
    BINARYENTRYPOINTFIELD(sender_location);
    BINARYENTRYPOINTFIELD(entering_trader);
};

static_assert(sizeof(allocation_report_message) == allocation_report_message::size, "allocation_report_message lies over its bytes exactly");

// Memo Section 1
struct memo_section_1 {
    static constexpr std::string_view name = "Memo Section 1";
    static constexpr std::size_t size = 1;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        memo_length>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYENTRYPOINTFIELD(memo_length);
};

static_assert(sizeof(memo_section_1) == memo_section_1::size, "memo_section_1 lies over its bytes exactly");

// Memo: memo data struct
struct memo {
    static constexpr std::string_view name = "Memo";
    static constexpr bool is_message = false;
};

// Desk Id Section 1
struct desk_id_section_1 {
    static constexpr std::string_view name = "Desk Id Section 1";
    static constexpr std::size_t size = 1;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        desk_id_length>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYENTRYPOINTFIELD(desk_id_length);
};

static_assert(sizeof(desk_id_section_1) == desk_id_section_1::size, "desk_id_section_1 lies over its bytes exactly");

// Desk Id: deskID data struct
struct desk_id {
    static constexpr std::string_view name = "Desk Id";
    static constexpr bool is_message = false;
};

// Allocation Instruction Message Section 1
struct allocation_instruction_message_section_1 {
    static constexpr std::string_view name = "Allocation Instruction Message Section 1";
    static constexpr std::size_t size = 86;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        inbound_business_header,
        alloc_id,
        security_id,
        alloc_trans_type,
        alloc_type,
        alloc_no_orders_type,
        quantity,
        sender_location,
        entering_trader,
        trade_id,
        trade_date_optional,
        individual_alloc_id,
        alloc_account,
        alloc_qty>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYENTRYPOINTFIELD(inbound_business_header);
    BINARYENTRYPOINTFIELD(alloc_id);
    BINARYENTRYPOINTFIELD(security_id);
    BINARYENTRYPOINTFIELD(alloc_trans_type);
    BINARYENTRYPOINTFIELD(alloc_type);
    BINARYENTRYPOINTFIELD(alloc_no_orders_type);
    BINARYENTRYPOINTFIELD(quantity);
    BINARYENTRYPOINTFIELD(sender_location);
    BINARYENTRYPOINTFIELD(entering_trader);
    BINARYENTRYPOINTFIELD(trade_id);
    BINARYENTRYPOINTFIELD(trade_date_optional);
    BINARYENTRYPOINTFIELD(individual_alloc_id);
    BINARYENTRYPOINTFIELD(alloc_account);
    BINARYENTRYPOINTFIELD(alloc_qty);
};

static_assert(sizeof(allocation_instruction_message_section_1) == allocation_instruction_message_section_1::size, "allocation_instruction_message_section_1 lies over its bytes exactly");

// Allocation Instruction Message: AllocationInstructionMessage
struct allocation_instruction_message {
    static constexpr std::string_view name = "Allocation Instruction Message";
    static constexpr bool is_message = true;
};

// Positions Group: noPositions
struct positions_group {
    static constexpr std::string_view name = "Positions Group";
    static constexpr std::size_t size = 17;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        pos_type,
        long_qty_optional,
        short_qty>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYENTRYPOINTFIELD(pos_type);
    BINARYENTRYPOINTFIELD(long_qty_optional);
    BINARYENTRYPOINTFIELD(short_qty);
};

static_assert(sizeof(positions_group) == positions_group::size, "positions_group lies over its bytes exactly");

// Group Size Encoding: GroupSizeEncoding
struct group_size_encoding {
    static constexpr std::string_view name = "Group Size Encoding";
    static constexpr std::size_t size = 3;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        block_length,
        num_in_group>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYENTRYPOINTFIELD(block_length);
    BINARYENTRYPOINTFIELD(num_in_group);
};

static_assert(sizeof(group_size_encoding) == group_size_encoding::size, "group_size_encoding lies over its bytes exactly");

// Positions Groups: noPositions Block
struct positions_groups {
    static constexpr std::string_view name = "Positions Groups";
    static constexpr bool is_message = false;

    // its repeating groups, whose entries the parse hands over one at a time
    BINARYENTRYPOINTSEQUENCE(positions_group);
};

// Position Maintenance Report Message Section 1
struct position_maintenance_report_message_section_1 {
    static constexpr std::string_view name = "Position Maintenance Report Message Section 1";
    static constexpr std::size_t size = 95;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        outbound_business_header,
        pos_req_id_optional,
        security_id,
        pos_maint_rpt_id,
        pos_trans_type,
        pos_maint_action,
        pos_maint_status,
        trade_id_optional,
        orig_pos_req_ref_id,
        account_type,
        clearing_business_date,
        threshold_amount,
        transact_time,
        account,
        sender_location,
        pos_maint_result,
        contrary_instruction_indicator>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYENTRYPOINTFIELD(outbound_business_header);
    BINARYENTRYPOINTFIELD(pos_req_id_optional);
    BINARYENTRYPOINTFIELD(security_id);
    BINARYENTRYPOINTFIELD(pos_maint_rpt_id);
    BINARYENTRYPOINTFIELD(pos_trans_type);
    BINARYENTRYPOINTFIELD(pos_maint_action);
    BINARYENTRYPOINTFIELD(pos_maint_status);
    BINARYENTRYPOINTFIELD(trade_id_optional);
    BINARYENTRYPOINTFIELD(orig_pos_req_ref_id);
    BINARYENTRYPOINTFIELD(account_type);
    BINARYENTRYPOINTFIELD(clearing_business_date);
    BINARYENTRYPOINTFIELD(threshold_amount);
    BINARYENTRYPOINTFIELD(transact_time);
    BINARYENTRYPOINTFIELD(account);
    BINARYENTRYPOINTFIELD(sender_location);
    BINARYENTRYPOINTFIELD(pos_maint_result);
    BINARYENTRYPOINTFIELD(contrary_instruction_indicator);
};

static_assert(sizeof(position_maintenance_report_message_section_1) == position_maintenance_report_message_section_1::size, "position_maintenance_report_message_section_1 lies over its bytes exactly");

// Position Maintenance Report Message: PositionMaintenanceReportMessage
struct position_maintenance_report_message {
    static constexpr std::string_view name = "Position Maintenance Report Message";
    static constexpr bool is_message = true;
};

// Position Maintenance Request Message Section 1
struct position_maintenance_request_message_section_1 {
    static constexpr std::string_view name = "Position Maintenance Request Message Section 1";
    static constexpr std::size_t size = 73;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        inbound_business_header,
        pos_req_id,
        security_id,
        threshold_amount,
        account,
        sender_location,
        pos_trans_type,
        clearing_business_date,
        contrary_instruction_indicator,
        entering_trader,
        long_qty>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYENTRYPOINTFIELD(inbound_business_header);
    BINARYENTRYPOINTFIELD(pos_req_id);
    BINARYENTRYPOINTFIELD(security_id);
    BINARYENTRYPOINTFIELD(threshold_amount);
    BINARYENTRYPOINTFIELD(account);
    BINARYENTRYPOINTFIELD(sender_location);
    BINARYENTRYPOINTFIELD(pos_trans_type);
    BINARYENTRYPOINTFIELD(clearing_business_date);
    BINARYENTRYPOINTFIELD(contrary_instruction_indicator);
    BINARYENTRYPOINTFIELD(entering_trader);
    BINARYENTRYPOINTFIELD(long_qty);
};

static_assert(sizeof(position_maintenance_request_message_section_1) == position_maintenance_request_message_section_1::size, "position_maintenance_request_message_section_1 lies over its bytes exactly");

// Position Maintenance Request Message: PositionMaintenanceRequestMessage
struct position_maintenance_request_message {
    static constexpr std::string_view name = "Position Maintenance Request Message";
    static constexpr bool is_message = true;
};

// Position Maintenance Cancel Request Message: PositionMaintenanceCancelRequestMessage
struct position_maintenance_cancel_request_message {
    static constexpr std::string_view name = "Position Maintenance Cancel Request Message";
    static constexpr std::size_t size = 65;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        inbound_business_header,
        pos_req_id,
        security_id,
        orig_pos_req_ref_id,
        pos_maint_rpt_ref_id,
        sender_location,
        entering_trader>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYENTRYPOINTFIELD(inbound_business_header);
    BINARYENTRYPOINTFIELD(pos_req_id);
    BINARYENTRYPOINTFIELD(security_id);
    BINARYENTRYPOINTFIELD(orig_pos_req_ref_id);
    BINARYENTRYPOINTFIELD(pos_maint_rpt_ref_id);
    BINARYENTRYPOINTFIELD(sender_location);
    BINARYENTRYPOINTFIELD(entering_trader);
};

static_assert(sizeof(position_maintenance_cancel_request_message) == position_maintenance_cancel_request_message::size, "position_maintenance_cancel_request_message lies over its bytes exactly");

// Quote Req Id Section 1
struct quote_req_id_section_1 {
    static constexpr std::string_view name = "Quote Req Id Section 1";
    static constexpr std::size_t size = 1;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        quote_req_id_length>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYENTRYPOINTFIELD(quote_req_id_length);
};

static_assert(sizeof(quote_req_id_section_1) == quote_req_id_section_1::size, "quote_req_id_section_1 lies over its bytes exactly");

// Quote Req Id: quoteReqID data struct
struct quote_req_id {
    static constexpr std::string_view name = "Quote Req Id";
    static constexpr bool is_message = false;
};

// Sides Group: noSides
struct sides_group {
    static constexpr std::string_view name = "Sides Group";
    static constexpr std::size_t size = 5;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        side,
        account>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYENTRYPOINTFIELD(side);
    BINARYENTRYPOINTFIELD(account);
};

static_assert(sizeof(sides_group) == sides_group::size, "sides_group lies over its bytes exactly");

// Sides Groups: noSides Block
struct sides_groups {
    static constexpr std::string_view name = "Sides Groups";
    static constexpr bool is_message = false;

    // its repeating groups, whose entries the parse hands over one at a time
    BINARYENTRYPOINTSEQUENCE(sides_group);
};

// Bidirectional Business Header: BidirectionalBusinessHeader
struct bidirectional_business_header {
    static constexpr std::string_view name = "Bidirectional Business Header";
    static constexpr std::size_t size = 19;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        session_id,
        msg_seq_num,
        sending_time,
        poss_resend,
        market_segment_id_optional,
        padding>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYENTRYPOINTFIELD(session_id);
    BINARYENTRYPOINTFIELD(msg_seq_num);
    BINARYENTRYPOINTFIELD(sending_time);
    BINARYENTRYPOINTFIELD(poss_resend);
    BINARYENTRYPOINTFIELD(market_segment_id_optional);
    BINARYENTRYPOINTFIELD(padding);
};

static_assert(sizeof(bidirectional_business_header) == bidirectional_business_header::size, "bidirectional_business_header lies over its bytes exactly");

// Quote Request Reject Message Section 1
struct quote_request_reject_message_section_1 {
    static constexpr std::string_view name = "Quote Request Reject Message Section 1";
    static constexpr std::size_t size = 102;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        bidirectional_business_header,
        quote_request_reject_reason,
        security_id,
        quote_id_optional,
        trade_id_optional,
        contra_broker,
        transact_time,
        entering_trader,
        settl_type_optional,
        price_optional,
        order_qty_optional,
        sender_location,
        executing_trader,
        fixed_rate_optional,
        days_to_settlement_optional>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYENTRYPOINTFIELD(bidirectional_business_header);
    BINARYENTRYPOINTFIELD(quote_request_reject_reason);
    BINARYENTRYPOINTFIELD(security_id);
    BINARYENTRYPOINTFIELD(quote_id_optional);
    BINARYENTRYPOINTFIELD(trade_id_optional);
    BINARYENTRYPOINTFIELD(contra_broker);
    BINARYENTRYPOINTFIELD(transact_time);
    BINARYENTRYPOINTFIELD(entering_trader);
    BINARYENTRYPOINTFIELD(settl_type_optional);
    BINARYENTRYPOINTFIELD(price_optional);
    BINARYENTRYPOINTFIELD(order_qty_optional);
    BINARYENTRYPOINTFIELD(sender_location);
    BINARYENTRYPOINTFIELD(executing_trader);
    BINARYENTRYPOINTFIELD(fixed_rate_optional);
    BINARYENTRYPOINTFIELD(days_to_settlement_optional);
};

static_assert(sizeof(quote_request_reject_message_section_1) == quote_request_reject_message_section_1::size, "quote_request_reject_message_section_1 lies over its bytes exactly");

// Quote Request Reject Message: QuoteRequestRejectMessage
struct quote_request_reject_message {
    static constexpr std::string_view name = "Quote Request Reject Message";
    static constexpr bool is_message = true;
};

// Quote Cancel Message Section 1
struct quote_cancel_message_section_1 {
    static constexpr std::string_view name = "Quote Cancel Message Section 1";
    static constexpr std::size_t size = 59;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        bidirectional_business_header,
        security_id,
        quote_id_optional,
        account,
        sender_location,
        entering_trader,
        executing_trader>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYENTRYPOINTFIELD(bidirectional_business_header);
    BINARYENTRYPOINTFIELD(security_id);
    BINARYENTRYPOINTFIELD(quote_id_optional);
    BINARYENTRYPOINTFIELD(account);
    BINARYENTRYPOINTFIELD(sender_location);
    BINARYENTRYPOINTFIELD(entering_trader);
    BINARYENTRYPOINTFIELD(executing_trader);
};

static_assert(sizeof(quote_cancel_message_section_1) == quote_cancel_message_section_1::size, "quote_cancel_message_section_1 lies over its bytes exactly");

// Quote Cancel Message: QuoteCancelMessage
struct quote_cancel_message {
    static constexpr std::string_view name = "Quote Cancel Message";
    static constexpr bool is_message = true;
};

// Quote Message Section 1
struct quote_message_section_1 {
    static constexpr std::string_view name = "Quote Message Section 1";
    static constexpr std::size_t size = 96;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        bidirectional_business_header,
        security_id,
        quote_id,
        transact_time,
        price_optional,
        order_qty,
        side,
        settl_type,
        account,
        sender_location,
        entering_trader,
        executing_trader,
        fixed_rate,
        execute_underlying_trade,
        days_to_settlement>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYENTRYPOINTFIELD(bidirectional_business_header);
    BINARYENTRYPOINTFIELD(security_id);
    BINARYENTRYPOINTFIELD(quote_id);
    BINARYENTRYPOINTFIELD(transact_time);
    BINARYENTRYPOINTFIELD(price_optional);
    BINARYENTRYPOINTFIELD(order_qty);
    BINARYENTRYPOINTFIELD(side);
    BINARYENTRYPOINTFIELD(settl_type);
    BINARYENTRYPOINTFIELD(account);
    BINARYENTRYPOINTFIELD(sender_location);
    BINARYENTRYPOINTFIELD(entering_trader);
    BINARYENTRYPOINTFIELD(executing_trader);
    BINARYENTRYPOINTFIELD(fixed_rate);
    BINARYENTRYPOINTFIELD(execute_underlying_trade);
    BINARYENTRYPOINTFIELD(days_to_settlement);
};

static_assert(sizeof(quote_message_section_1) == quote_message_section_1::size, "quote_message_section_1 lies over its bytes exactly");

// Quote Message: QuoteMessage
struct quote_message {
    static constexpr std::string_view name = "Quote Message";
    static constexpr bool is_message = true;
};

// Quote Status Report Message Section 1
struct quote_status_report_message_section_1 {
    static constexpr std::string_view name = "Quote Status Report Message Section 1";
    static constexpr std::size_t size = 110;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        bidirectional_business_header,
        quote_reject_reason,
        security_id,
        quote_id,
        trade_id_optional,
        contra_broker,
        transact_time,
        quote_status,
        quote_status_response_to,
        account,
        side_optional,
        settl_type_optional,
        price_optional,
        order_qty,
        sender_location,
        entering_trader,
        executing_trader,
        fixed_rate_optional,
        execute_underlying_trade,
        days_to_settlement_optional>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYENTRYPOINTFIELD(bidirectional_business_header);
    BINARYENTRYPOINTFIELD(quote_reject_reason);
    BINARYENTRYPOINTFIELD(security_id);
    BINARYENTRYPOINTFIELD(quote_id);
    BINARYENTRYPOINTFIELD(trade_id_optional);
    BINARYENTRYPOINTFIELD(contra_broker);
    BINARYENTRYPOINTFIELD(transact_time);
    BINARYENTRYPOINTFIELD(quote_status);
    BINARYENTRYPOINTFIELD(quote_status_response_to);
    BINARYENTRYPOINTFIELD(account);
    BINARYENTRYPOINTFIELD(side_optional);
    BINARYENTRYPOINTFIELD(settl_type_optional);
    BINARYENTRYPOINTFIELD(price_optional);
    BINARYENTRYPOINTFIELD(order_qty);
    BINARYENTRYPOINTFIELD(sender_location);
    BINARYENTRYPOINTFIELD(entering_trader);
    BINARYENTRYPOINTFIELD(executing_trader);
    BINARYENTRYPOINTFIELD(fixed_rate_optional);
    BINARYENTRYPOINTFIELD(execute_underlying_trade);
    BINARYENTRYPOINTFIELD(days_to_settlement_optional);
};

static_assert(sizeof(quote_status_report_message_section_1) == quote_status_report_message_section_1::size, "quote_status_report_message_section_1 lies over its bytes exactly");

// Quote Status Report Message: QuoteStatusReportMessage
struct quote_status_report_message {
    static constexpr std::string_view name = "Quote Status Report Message";
    static constexpr bool is_message = true;
};

// Quote Request Message Section 1
struct quote_request_message_section_1 {
    static constexpr std::string_view name = "Quote Request Message Section 1";
    static constexpr std::size_t size = 99;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        bidirectional_business_header,
        security_id,
        quote_id_optional,
        trade_id_optional,
        contra_broker,
        transact_time,
        price,
        settl_type,
        execute_underlying_trade,
        order_qty,
        sender_location,
        entering_trader,
        executing_trader,
        fixed_rate,
        days_to_settlement>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYENTRYPOINTFIELD(bidirectional_business_header);
    BINARYENTRYPOINTFIELD(security_id);
    BINARYENTRYPOINTFIELD(quote_id_optional);
    BINARYENTRYPOINTFIELD(trade_id_optional);
    BINARYENTRYPOINTFIELD(contra_broker);
    BINARYENTRYPOINTFIELD(transact_time);
    BINARYENTRYPOINTFIELD(price);
    BINARYENTRYPOINTFIELD(settl_type);
    BINARYENTRYPOINTFIELD(execute_underlying_trade);
    BINARYENTRYPOINTFIELD(order_qty);
    BINARYENTRYPOINTFIELD(sender_location);
    BINARYENTRYPOINTFIELD(entering_trader);
    BINARYENTRYPOINTFIELD(executing_trader);
    BINARYENTRYPOINTFIELD(fixed_rate);
    BINARYENTRYPOINTFIELD(days_to_settlement);
};

static_assert(sizeof(quote_request_message_section_1) == quote_request_message_section_1::size, "quote_request_message_section_1 lies over its bytes exactly");

// Quote Request Message: QuoteRequestMessage
struct quote_request_message {
    static constexpr std::string_view name = "Quote Request Message";
    static constexpr bool is_message = true;
};

// Security Definition Response Message: SecurityDefinitionResponseMessage
struct security_definition_response_message {
    static constexpr std::string_view name = "Security Definition Response Message";
    static constexpr std::size_t size = 83;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        outbound_business_header,
        offset_18_padding_2,
        security_req_id,
        security_id,
        security_response_type,
        security_strategy_type,
        symbol,
        security_response_id,
        sender_location,
        entering_trader>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYENTRYPOINTFIELD(outbound_business_header);
    BINARYENTRYPOINTFIELD(offset_18_padding_2);
    BINARYENTRYPOINTFIELD(security_req_id);
    BINARYENTRYPOINTFIELD(security_id);
    BINARYENTRYPOINTFIELD(security_response_type);
    BINARYENTRYPOINTFIELD(security_strategy_type);
    BINARYENTRYPOINTFIELD(symbol);
    BINARYENTRYPOINTFIELD(security_response_id);
    BINARYENTRYPOINTFIELD(sender_location);
    BINARYENTRYPOINTFIELD(entering_trader);
};

static_assert(sizeof(security_definition_response_message) == security_definition_response_message::size, "security_definition_response_message lies over its bytes exactly");

// Legs Group: noLegs
struct legs_group {
    static constexpr std::string_view name = "Legs Group";
    static constexpr std::size_t size = 30;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        leg_symbol,
        leg_ratio_qty,
        leg_side,
        padding_1>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYENTRYPOINTFIELD(leg_symbol);
    BINARYENTRYPOINTFIELD(leg_ratio_qty);
    BINARYENTRYPOINTFIELD(leg_side);
    BINARYENTRYPOINTFIELD(padding_1);
};

static_assert(sizeof(legs_group) == legs_group::size, "legs_group lies over its bytes exactly");

// Legs Groups: noLegs Block
struct legs_groups {
    static constexpr std::string_view name = "Legs Groups";
    static constexpr bool is_message = false;

    // its repeating groups, whose entries the parse hands over one at a time
    BINARYENTRYPOINTSEQUENCE(legs_group);
};

// Security Definition Request Message Section 1
struct security_definition_request_message_section_1 {
    static constexpr std::string_view name = "Security Definition Request Message Section 1";
    static constexpr std::size_t size = 41;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        inbound_business_header,
        security_req_id,
        sender_location,
        entering_trader>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYENTRYPOINTFIELD(inbound_business_header);
    BINARYENTRYPOINTFIELD(security_req_id);
    BINARYENTRYPOINTFIELD(sender_location);
    BINARYENTRYPOINTFIELD(entering_trader);
};

static_assert(sizeof(security_definition_request_message_section_1) == security_definition_request_message_section_1::size, "security_definition_request_message_section_1 lies over its bytes exactly");

// Security Definition Request Message: SecurityDefinitionRequestMessage
struct security_definition_request_message {
    static constexpr std::string_view name = "Security Definition Request Message";
    static constexpr bool is_message = true;
};

// Business Message Reject Message Section 1
struct business_message_reject_message_section_1 {
    static constexpr std::string_view name = "Business Message Reject Message Section 1";
    static constexpr std::size_t size = 36;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        outbound_business_header,
        ref_msg_type,
        offset_19_padding_1,
        ref_seq_num,
        business_reject_ref_id,
        business_reject_reason>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYENTRYPOINTFIELD(outbound_business_header);
    BINARYENTRYPOINTFIELD(ref_msg_type);
    BINARYENTRYPOINTFIELD(offset_19_padding_1);
    BINARYENTRYPOINTFIELD(ref_seq_num);
    BINARYENTRYPOINTFIELD(business_reject_ref_id);
    BINARYENTRYPOINTFIELD(business_reject_reason);
};

static_assert(sizeof(business_message_reject_message_section_1) == business_message_reject_message_section_1::size, "business_message_reject_message_section_1 lies over its bytes exactly");

// Business Message Reject Message: BusinessMessageRejectMessage
struct business_message_reject_message {
    static constexpr std::string_view name = "Business Message Reject Message";
    static constexpr bool is_message = true;
};

// Execution Report Forward Message Section 1
struct execution_report_forward_message_section_1 {
    static constexpr std::string_view name = "Execution Report Forward Message Section 1";
    static constexpr std::size_t size = 152;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        outbound_business_header,
        side,
        ord_status,
        clordid_optional,
        secondary_order_id,
        security_id,
        account,
        last_qty,
        last_px,
        exec_id,
        transact_time,
        leaves_qty,
        cum_qty,
        trade_id,
        contra_broker,
        order_id,
        aggressor_indicator,
        settl_type_optional,
        trade_date,
        days_to_settlement_optional,
        offset_118_padding_2,
        secondary_exec_id,
        exec_ref_id,
        fixed_rate_optional,
        order_qty>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYENTRYPOINTFIELD(outbound_business_header);
    BINARYENTRYPOINTFIELD(side);
    BINARYENTRYPOINTFIELD(ord_status);
    BINARYENTRYPOINTFIELD(clordid_optional);
    BINARYENTRYPOINTFIELD(secondary_order_id);
    BINARYENTRYPOINTFIELD(security_id);
    BINARYENTRYPOINTFIELD(account);
    BINARYENTRYPOINTFIELD(last_qty);
    BINARYENTRYPOINTFIELD(last_px);
    BINARYENTRYPOINTFIELD(exec_id);
    BINARYENTRYPOINTFIELD(transact_time);
    BINARYENTRYPOINTFIELD(leaves_qty);
    BINARYENTRYPOINTFIELD(cum_qty);
    BINARYENTRYPOINTFIELD(trade_id);
    BINARYENTRYPOINTFIELD(contra_broker);
    BINARYENTRYPOINTFIELD(order_id);
    BINARYENTRYPOINTFIELD(aggressor_indicator);
    BINARYENTRYPOINTFIELD(settl_type_optional);
    BINARYENTRYPOINTFIELD(trade_date);
    BINARYENTRYPOINTFIELD(days_to_settlement_optional);
    BINARYENTRYPOINTFIELD(offset_118_padding_2);
    BINARYENTRYPOINTFIELD(secondary_exec_id);
    BINARYENTRYPOINTFIELD(exec_ref_id);
    BINARYENTRYPOINTFIELD(fixed_rate_optional);
    BINARYENTRYPOINTFIELD(order_qty);
};

static_assert(sizeof(execution_report_forward_message_section_1) == execution_report_forward_message_section_1::size, "execution_report_forward_message_section_1 lies over its bytes exactly");

// Execution Report Forward Message: ExecutionReport_ForwardMessage
struct execution_report_forward_message {
    static constexpr std::string_view name = "Execution Report Forward Message";
    static constexpr bool is_message = true;
};

// Execution Report Reject Message Section 1
struct execution_report_reject_message_section_1 {
    static constexpr std::string_view name = "Execution Report Reject Message Section 1";
    static constexpr std::size_t size = 138;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        outbound_business_header,
        side,
        cxl_rej_response_to,
        clordid,
        secondary_order_id_optional,
        security_id,
        ord_rej_reason,
        transact_time,
        exec_id,
        order_id_optional,
        origclordid,
        account,
        ordtype,
        time_in_force,
        expire_date,
        order_qty,
        price_optional,
        stop_px,
        min_qty,
        max_floor,
        crossid_optional,
        crossed_indicator>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYENTRYPOINTFIELD(outbound_business_header);
    BINARYENTRYPOINTFIELD(side);
    BINARYENTRYPOINTFIELD(cxl_rej_response_to);
    BINARYENTRYPOINTFIELD(clordid);
    BINARYENTRYPOINTFIELD(secondary_order_id_optional);
    BINARYENTRYPOINTFIELD(security_id);
    BINARYENTRYPOINTFIELD(ord_rej_reason);
    BINARYENTRYPOINTFIELD(transact_time);
    BINARYENTRYPOINTFIELD(exec_id);
    BINARYENTRYPOINTFIELD(order_id_optional);
    BINARYENTRYPOINTFIELD(origclordid);
    BINARYENTRYPOINTFIELD(account);
    BINARYENTRYPOINTFIELD(ordtype);
    BINARYENTRYPOINTFIELD(time_in_force);
    BINARYENTRYPOINTFIELD(expire_date);
    BINARYENTRYPOINTFIELD(order_qty);
    BINARYENTRYPOINTFIELD(price_optional);
    BINARYENTRYPOINTFIELD(stop_px);
    BINARYENTRYPOINTFIELD(min_qty);
    BINARYENTRYPOINTFIELD(max_floor);
    BINARYENTRYPOINTFIELD(crossid_optional);
    BINARYENTRYPOINTFIELD(crossed_indicator);
};

static_assert(sizeof(execution_report_reject_message_section_1) == execution_report_reject_message_section_1::size, "execution_report_reject_message_section_1 lies over its bytes exactly");

// Execution Report Reject Message: ExecutionReport_RejectMessage
struct execution_report_reject_message {
    static constexpr std::string_view name = "Execution Report Reject Message";
    static constexpr bool is_message = true;
};

// Execution Report Trade Message Section 1
struct execution_report_trade_message_section_1 {
    static constexpr std::string_view name = "Execution Report Trade Message Section 1";
    static constexpr std::size_t size = 154;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        outbound_business_header,
        side,
        ord_status,
        clordid_optional,
        secondary_order_id,
        security_id,
        account,
        last_qty,
        last_px,
        exec_id,
        transact_time,
        leaves_qty,
        cum_qty,
        aggressor_indicator,
        exec_type,
        order_category,
        multi_leg_reporting_type,
        trade_id,
        contra_broker,
        order_id,
        trade_date,
        tot_no_related_sym,
        offset_119_padding_1,
        secondary_exec_id,
        exec_ref_id,
        crossid_optional,
        crossed_indicator,
        order_qty>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYENTRYPOINTFIELD(outbound_business_header);
    BINARYENTRYPOINTFIELD(side);
    BINARYENTRYPOINTFIELD(ord_status);
    BINARYENTRYPOINTFIELD(clordid_optional);
    BINARYENTRYPOINTFIELD(secondary_order_id);
    BINARYENTRYPOINTFIELD(security_id);
    BINARYENTRYPOINTFIELD(account);
    BINARYENTRYPOINTFIELD(last_qty);
    BINARYENTRYPOINTFIELD(last_px);
    BINARYENTRYPOINTFIELD(exec_id);
    BINARYENTRYPOINTFIELD(transact_time);
    BINARYENTRYPOINTFIELD(leaves_qty);
    BINARYENTRYPOINTFIELD(cum_qty);
    BINARYENTRYPOINTFIELD(aggressor_indicator);
    BINARYENTRYPOINTFIELD(exec_type);
    BINARYENTRYPOINTFIELD(order_category);
    BINARYENTRYPOINTFIELD(multi_leg_reporting_type);
    BINARYENTRYPOINTFIELD(trade_id);
    BINARYENTRYPOINTFIELD(contra_broker);
    BINARYENTRYPOINTFIELD(order_id);
    BINARYENTRYPOINTFIELD(trade_date);
    BINARYENTRYPOINTFIELD(tot_no_related_sym);
    BINARYENTRYPOINTFIELD(offset_119_padding_1);
    BINARYENTRYPOINTFIELD(secondary_exec_id);
    BINARYENTRYPOINTFIELD(exec_ref_id);
    BINARYENTRYPOINTFIELD(crossid_optional);
    BINARYENTRYPOINTFIELD(crossed_indicator);
    BINARYENTRYPOINTFIELD(order_qty);
};

static_assert(sizeof(execution_report_trade_message_section_1) == execution_report_trade_message_section_1::size, "execution_report_trade_message_section_1 lies over its bytes exactly");

// Execution Report Trade Message: ExecutionReport_TradeMessage
struct execution_report_trade_message {
    static constexpr std::string_view name = "Execution Report Trade Message";
    static constexpr bool is_message = true;
};

// Execution Report Cancel Message Section 1
struct execution_report_cancel_message_section_1 {
    static constexpr std::string_view name = "Execution Report Cancel Message Section 1";
    static constexpr std::size_t size = 156;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        outbound_business_header,
        side,
        ord_status,
        clordid,
        secondary_order_id,
        security_id,
        cum_qty,
        account,
        exec_id,
        transact_time,
        market_segment_received_time,
        order_id,
        origclordid,
        trade_date,
        working_indicator,
        exec_restatement_reason,
        offset_100_padding_4,
        mass_action_report_id_optional,
        ordtype,
        time_in_force,
        expire_date,
        order_qty,
        price_optional,
        stop_px,
        min_qty,
        max_floor>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYENTRYPOINTFIELD(outbound_business_header);
    BINARYENTRYPOINTFIELD(side);
    BINARYENTRYPOINTFIELD(ord_status);
    BINARYENTRYPOINTFIELD(clordid);
    BINARYENTRYPOINTFIELD(secondary_order_id);
    BINARYENTRYPOINTFIELD(security_id);
    BINARYENTRYPOINTFIELD(cum_qty);
    BINARYENTRYPOINTFIELD(account);
    BINARYENTRYPOINTFIELD(exec_id);
    BINARYENTRYPOINTFIELD(transact_time);
    BINARYENTRYPOINTFIELD(market_segment_received_time);
    BINARYENTRYPOINTFIELD(order_id);
    BINARYENTRYPOINTFIELD(origclordid);
    BINARYENTRYPOINTFIELD(trade_date);
    BINARYENTRYPOINTFIELD(working_indicator);
    BINARYENTRYPOINTFIELD(exec_restatement_reason);
    BINARYENTRYPOINTFIELD(offset_100_padding_4);
    BINARYENTRYPOINTFIELD(mass_action_report_id_optional);
    BINARYENTRYPOINTFIELD(ordtype);
    BINARYENTRYPOINTFIELD(time_in_force);
    BINARYENTRYPOINTFIELD(expire_date);
    BINARYENTRYPOINTFIELD(order_qty);
    BINARYENTRYPOINTFIELD(price_optional);
    BINARYENTRYPOINTFIELD(stop_px);
    BINARYENTRYPOINTFIELD(min_qty);
    BINARYENTRYPOINTFIELD(max_floor);
};

static_assert(sizeof(execution_report_cancel_message_section_1) == execution_report_cancel_message_section_1::size, "execution_report_cancel_message_section_1 lies over its bytes exactly");

// Execution Report Cancel Message: ExecutionReport_CancelMessage
struct execution_report_cancel_message {
    static constexpr std::string_view name = "Execution Report Cancel Message";
    static constexpr bool is_message = true;
};

// Execution Report Modify Message Section 1
struct execution_report_modify_message_section_1 {
    static constexpr std::string_view name = "Execution Report Modify Message Section 1";
    static constexpr std::size_t size = 160;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        outbound_business_header,
        side,
        ord_status,
        clordid,
        secondary_order_id,
        security_id,
        leaves_qty,
        account,
        exec_id,
        transact_time,
        cum_qty,
        market_segment_received_time,
        order_id,
        origclordid,
        protection_price,
        trade_date,
        working_indicator,
        multi_leg_reporting_type,
        ordtype,
        time_in_force,
        expire_date,
        order_qty,
        price_optional,
        stop_px,
        min_qty,
        max_floor>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYENTRYPOINTFIELD(outbound_business_header);
    BINARYENTRYPOINTFIELD(side);
    BINARYENTRYPOINTFIELD(ord_status);
    BINARYENTRYPOINTFIELD(clordid);
    BINARYENTRYPOINTFIELD(secondary_order_id);
    BINARYENTRYPOINTFIELD(security_id);
    BINARYENTRYPOINTFIELD(leaves_qty);
    BINARYENTRYPOINTFIELD(account);
    BINARYENTRYPOINTFIELD(exec_id);
    BINARYENTRYPOINTFIELD(transact_time);
    BINARYENTRYPOINTFIELD(cum_qty);
    BINARYENTRYPOINTFIELD(market_segment_received_time);
    BINARYENTRYPOINTFIELD(order_id);
    BINARYENTRYPOINTFIELD(origclordid);
    BINARYENTRYPOINTFIELD(protection_price);
    BINARYENTRYPOINTFIELD(trade_date);
    BINARYENTRYPOINTFIELD(working_indicator);
    BINARYENTRYPOINTFIELD(multi_leg_reporting_type);
    BINARYENTRYPOINTFIELD(ordtype);
    BINARYENTRYPOINTFIELD(time_in_force);
    BINARYENTRYPOINTFIELD(expire_date);
    BINARYENTRYPOINTFIELD(order_qty);
    BINARYENTRYPOINTFIELD(price_optional);
    BINARYENTRYPOINTFIELD(stop_px);
    BINARYENTRYPOINTFIELD(min_qty);
    BINARYENTRYPOINTFIELD(max_floor);
};

static_assert(sizeof(execution_report_modify_message_section_1) == execution_report_modify_message_section_1::size, "execution_report_modify_message_section_1 lies over its bytes exactly");

// Execution Report Modify Message: ExecutionReport_ModifyMessage
struct execution_report_modify_message {
    static constexpr std::string_view name = "Execution Report Modify Message";
    static constexpr bool is_message = true;
};

// Execution Report New Message Section 1
struct execution_report_new_message_section_1 {
    static constexpr std::string_view name = "Execution Report New Message Section 1";
    static constexpr std::size_t size = 144;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        outbound_business_header,
        side,
        ord_status,
        clordid,
        secondary_order_id,
        security_id,
        order_id,
        account,
        exec_id,
        transact_time,
        market_segment_received_time,
        protection_price,
        trade_date,
        working_indicator,
        multi_leg_reporting_type,
        ordtype,
        time_in_force,
        expire_date,
        order_qty,
        price_optional,
        stop_px,
        min_qty,
        max_floor,
        crossid_optional>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYENTRYPOINTFIELD(outbound_business_header);
    BINARYENTRYPOINTFIELD(side);
    BINARYENTRYPOINTFIELD(ord_status);
    BINARYENTRYPOINTFIELD(clordid);
    BINARYENTRYPOINTFIELD(secondary_order_id);
    BINARYENTRYPOINTFIELD(security_id);
    BINARYENTRYPOINTFIELD(order_id);
    BINARYENTRYPOINTFIELD(account);
    BINARYENTRYPOINTFIELD(exec_id);
    BINARYENTRYPOINTFIELD(transact_time);
    BINARYENTRYPOINTFIELD(market_segment_received_time);
    BINARYENTRYPOINTFIELD(protection_price);
    BINARYENTRYPOINTFIELD(trade_date);
    BINARYENTRYPOINTFIELD(working_indicator);
    BINARYENTRYPOINTFIELD(multi_leg_reporting_type);
    BINARYENTRYPOINTFIELD(ordtype);
    BINARYENTRYPOINTFIELD(time_in_force);
    BINARYENTRYPOINTFIELD(expire_date);
    BINARYENTRYPOINTFIELD(order_qty);
    BINARYENTRYPOINTFIELD(price_optional);
    BINARYENTRYPOINTFIELD(stop_px);
    BINARYENTRYPOINTFIELD(min_qty);
    BINARYENTRYPOINTFIELD(max_floor);
    BINARYENTRYPOINTFIELD(crossid_optional);
};

static_assert(sizeof(execution_report_new_message_section_1) == execution_report_new_message_section_1::size, "execution_report_new_message_section_1 lies over its bytes exactly");

// Execution Report New Message: ExecutionReport_NewMessage
struct execution_report_new_message {
    static constexpr std::string_view name = "Execution Report New Message";
    static constexpr bool is_message = true;
};

// Cross Sides Group: noSides
struct cross_sides_group {
    static constexpr std::string_view name = "Cross Sides Group";
    static constexpr std::size_t size = 18;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        side,
        offset_1_padding_1,
        account,
        entering_firm_optional,
        clordid>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYENTRYPOINTFIELD(side);
    BINARYENTRYPOINTFIELD(offset_1_padding_1);
    BINARYENTRYPOINTFIELD(account);
    BINARYENTRYPOINTFIELD(entering_firm_optional);
    BINARYENTRYPOINTFIELD(clordid);
};

static_assert(sizeof(cross_sides_group) == cross_sides_group::size, "cross_sides_group lies over its bytes exactly");

// Cross Sides Groups: noSides Block
struct cross_sides_groups {
    static constexpr std::string_view name = "Cross Sides Groups";
    static constexpr bool is_message = false;

    // its repeating groups, whose entries the parse hands over one at a time
    BINARYENTRYPOINTSEQUENCE(cross_sides_group);
};

// New Order Cross Message Section 1
struct new_order_cross_message_section_1 {
    static constexpr std::string_view name = "New Order Cross Message Section 1";
    static constexpr std::size_t size = 74;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        inbound_business_header,
        offset_18_padding_2,
        crossid,
        sender_location,
        entering_trader,
        executing_trader_optional,
        security_id,
        order_qty,
        price,
        crossed_indicator>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYENTRYPOINTFIELD(inbound_business_header);
    BINARYENTRYPOINTFIELD(offset_18_padding_2);
    BINARYENTRYPOINTFIELD(crossid);
    BINARYENTRYPOINTFIELD(sender_location);
    BINARYENTRYPOINTFIELD(entering_trader);
    BINARYENTRYPOINTFIELD(executing_trader_optional);
    BINARYENTRYPOINTFIELD(security_id);
    BINARYENTRYPOINTFIELD(order_qty);
    BINARYENTRYPOINTFIELD(price);
    BINARYENTRYPOINTFIELD(crossed_indicator);
};

static_assert(sizeof(new_order_cross_message_section_1) == new_order_cross_message_section_1::size, "new_order_cross_message_section_1 lies over its bytes exactly");

// New Order Cross Message: NewOrderCrossMessage
struct new_order_cross_message {
    static constexpr std::string_view name = "New Order Cross Message";
    static constexpr bool is_message = true;
};

// Order Cancel Request Message Section 1
struct order_cancel_request_message_section_1 {
    static constexpr std::string_view name = "Order Cancel Request Message Section 1";
    static constexpr std::size_t size = 76;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        inbound_business_header,
        offset_18_padding_2,
        clordid,
        security_id,
        order_id_optional,
        origclordid,
        side,
        single_cancel_restatement_reason,
        offset_54_padding_2,
        sender_location,
        entering_trader,
        executing_trader_optional>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYENTRYPOINTFIELD(inbound_business_header);
    BINARYENTRYPOINTFIELD(offset_18_padding_2);
    BINARYENTRYPOINTFIELD(clordid);
    BINARYENTRYPOINTFIELD(security_id);
    BINARYENTRYPOINTFIELD(order_id_optional);
    BINARYENTRYPOINTFIELD(origclordid);
    BINARYENTRYPOINTFIELD(side);
    BINARYENTRYPOINTFIELD(single_cancel_restatement_reason);
    BINARYENTRYPOINTFIELD(offset_54_padding_2);
    BINARYENTRYPOINTFIELD(sender_location);
    BINARYENTRYPOINTFIELD(entering_trader);
    BINARYENTRYPOINTFIELD(executing_trader_optional);
};

static_assert(sizeof(order_cancel_request_message_section_1) == order_cancel_request_message_section_1::size, "order_cancel_request_message_section_1 lies over its bytes exactly");

// Order Cancel Request Message: OrderCancelRequestMessage
struct order_cancel_request_message {
    static constexpr std::string_view name = "Order Cancel Request Message";
    static constexpr bool is_message = true;
};

// Custodian Info: NewOrderSingleMessage
struct custodian_info {
    static constexpr std::string_view name = "Custodian Info";
    static constexpr std::size_t size = 12;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        custodian,
        custody_account,
        custody_allocation_type>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYENTRYPOINTFIELD(custodian);
    BINARYENTRYPOINTFIELD(custody_account);
    BINARYENTRYPOINTFIELD(custody_allocation_type);
};

static_assert(sizeof(custodian_info) == custodian_info::size, "custodian_info lies over its bytes exactly");

// Order Cancel Replace Request Message Section 1
struct order_cancel_replace_request_message_section_1 {
    static constexpr std::string_view name = "Order Cancel Replace Request Message Section 1";
    static constexpr std::size_t size = 144;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        inbound_business_header,
        ordtagid,
        mm_protection_reset,
        clordid,
        account,
        sender_location,
        entering_trader,
        self_trade_prevention_instruction,
        security_id,
        side,
        ordtype,
        time_in_force_optional,
        routing_instruction,
        order_qty,
        price_optional,
        order_id_optional,
        origclordid,
        stop_px,
        min_qty,
        max_floor,
        executing_trader_optional,
        account_type,
        expire_date,
        custodian_info,
        investor_id>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYENTRYPOINTFIELD(inbound_business_header);
    BINARYENTRYPOINTFIELD(ordtagid);
    BINARYENTRYPOINTFIELD(mm_protection_reset);
    BINARYENTRYPOINTFIELD(clordid);
    BINARYENTRYPOINTFIELD(account);
    BINARYENTRYPOINTFIELD(sender_location);
    BINARYENTRYPOINTFIELD(entering_trader);
    BINARYENTRYPOINTFIELD(self_trade_prevention_instruction);
    BINARYENTRYPOINTFIELD(security_id);
    BINARYENTRYPOINTFIELD(side);
    BINARYENTRYPOINTFIELD(ordtype);
    BINARYENTRYPOINTFIELD(time_in_force_optional);
    BINARYENTRYPOINTFIELD(routing_instruction);
    BINARYENTRYPOINTFIELD(order_qty);
    BINARYENTRYPOINTFIELD(price_optional);
    BINARYENTRYPOINTFIELD(order_id_optional);
    BINARYENTRYPOINTFIELD(origclordid);
    BINARYENTRYPOINTFIELD(stop_px);
    BINARYENTRYPOINTFIELD(min_qty);
    BINARYENTRYPOINTFIELD(max_floor);
    BINARYENTRYPOINTFIELD(executing_trader_optional);
    BINARYENTRYPOINTFIELD(account_type);
    BINARYENTRYPOINTFIELD(expire_date);
    BINARYENTRYPOINTFIELD(custodian_info);
    BINARYENTRYPOINTFIELD(investor_id);
};

static_assert(sizeof(order_cancel_replace_request_message_section_1) == order_cancel_replace_request_message_section_1::size, "order_cancel_replace_request_message_section_1 lies over its bytes exactly");

// Order Cancel Replace Request Message: OrderCancelReplaceRequestMessage
struct order_cancel_replace_request_message {
    static constexpr std::string_view name = "Order Cancel Replace Request Message";
    static constexpr bool is_message = true;
};

// New Order Single Message Section 1
struct new_order_single_message_section_1 {
    static constexpr std::string_view name = "New Order Single Message Section 1";
    static constexpr std::size_t size = 127;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        inbound_business_header,
        ordtagid,
        mm_protection_reset,
        clordid,
        account,
        sender_location,
        entering_trader,
        self_trade_prevention_instruction,
        security_id,
        side,
        ordtype,
        time_in_force,
        routing_instruction,
        order_qty,
        price_optional,
        stop_px,
        min_qty,
        max_floor,
        executing_trader_optional,
        expire_date,
        custodian_info,
        investor_id>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYENTRYPOINTFIELD(inbound_business_header);
    BINARYENTRYPOINTFIELD(ordtagid);
    BINARYENTRYPOINTFIELD(mm_protection_reset);
    BINARYENTRYPOINTFIELD(clordid);
    BINARYENTRYPOINTFIELD(account);
    BINARYENTRYPOINTFIELD(sender_location);
    BINARYENTRYPOINTFIELD(entering_trader);
    BINARYENTRYPOINTFIELD(self_trade_prevention_instruction);
    BINARYENTRYPOINTFIELD(security_id);
    BINARYENTRYPOINTFIELD(side);
    BINARYENTRYPOINTFIELD(ordtype);
    BINARYENTRYPOINTFIELD(time_in_force);
    BINARYENTRYPOINTFIELD(routing_instruction);
    BINARYENTRYPOINTFIELD(order_qty);
    BINARYENTRYPOINTFIELD(price_optional);
    BINARYENTRYPOINTFIELD(stop_px);
    BINARYENTRYPOINTFIELD(min_qty);
    BINARYENTRYPOINTFIELD(max_floor);
    BINARYENTRYPOINTFIELD(executing_trader_optional);
    BINARYENTRYPOINTFIELD(expire_date);
    BINARYENTRYPOINTFIELD(custodian_info);
    BINARYENTRYPOINTFIELD(investor_id);
};

static_assert(sizeof(new_order_single_message_section_1) == new_order_single_message_section_1::size, "new_order_single_message_section_1 lies over its bytes exactly");

// New Order Single Message: NewOrderSingleMessage
struct new_order_single_message {
    static constexpr std::string_view name = "New Order Single Message";
    static constexpr bool is_message = true;
};

// Simple Modify Order Message Section 1
struct simple_modify_order_message_section_1 {
    static constexpr std::string_view name = "Simple Modify Order Message Section 1";
    static constexpr std::size_t size = 100;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        inbound_business_header,
        ordtagid,
        mm_protection_reset,
        clordid,
        account,
        sender_location,
        entering_trader,
        self_trade_prevention_instruction,
        security_id,
        side,
        simple_ordtype,
        time_in_force_simple,
        routing_instruction,
        order_qty,
        price_optional,
        order_id_optional,
        origclordid,
        investor_id>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYENTRYPOINTFIELD(inbound_business_header);
    BINARYENTRYPOINTFIELD(ordtagid);
    BINARYENTRYPOINTFIELD(mm_protection_reset);
    BINARYENTRYPOINTFIELD(clordid);
    BINARYENTRYPOINTFIELD(account);
    BINARYENTRYPOINTFIELD(sender_location);
    BINARYENTRYPOINTFIELD(entering_trader);
    BINARYENTRYPOINTFIELD(self_trade_prevention_instruction);
    BINARYENTRYPOINTFIELD(security_id);
    BINARYENTRYPOINTFIELD(side);
    BINARYENTRYPOINTFIELD(simple_ordtype);
    BINARYENTRYPOINTFIELD(time_in_force_simple);
    BINARYENTRYPOINTFIELD(routing_instruction);
    BINARYENTRYPOINTFIELD(order_qty);
    BINARYENTRYPOINTFIELD(price_optional);
    BINARYENTRYPOINTFIELD(order_id_optional);
    BINARYENTRYPOINTFIELD(origclordid);
    BINARYENTRYPOINTFIELD(investor_id);
};

static_assert(sizeof(simple_modify_order_message_section_1) == simple_modify_order_message_section_1::size, "simple_modify_order_message_section_1 lies over its bytes exactly");

// Simple Modify Order Message: SimpleModifyOrderMessage
struct simple_modify_order_message {
    static constexpr std::string_view name = "Simple Modify Order Message";
    static constexpr bool is_message = true;
};

// Simple New Order Message Section 1
struct simple_new_order_message_section_1 {
    static constexpr std::string_view name = "Simple New Order Message Section 1";
    static constexpr std::size_t size = 84;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        inbound_business_header,
        ordtagid,
        mm_protection_reset,
        clordid,
        account,
        sender_location,
        entering_trader,
        self_trade_prevention_instruction,
        security_id,
        side,
        simple_ordtype,
        time_in_force_simple,
        routing_instruction,
        order_qty,
        price_optional,
        investor_id>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYENTRYPOINTFIELD(inbound_business_header);
    BINARYENTRYPOINTFIELD(ordtagid);
    BINARYENTRYPOINTFIELD(mm_protection_reset);
    BINARYENTRYPOINTFIELD(clordid);
    BINARYENTRYPOINTFIELD(account);
    BINARYENTRYPOINTFIELD(sender_location);
    BINARYENTRYPOINTFIELD(entering_trader);
    BINARYENTRYPOINTFIELD(self_trade_prevention_instruction);
    BINARYENTRYPOINTFIELD(security_id);
    BINARYENTRYPOINTFIELD(side);
    BINARYENTRYPOINTFIELD(simple_ordtype);
    BINARYENTRYPOINTFIELD(time_in_force_simple);
    BINARYENTRYPOINTFIELD(routing_instruction);
    BINARYENTRYPOINTFIELD(order_qty);
    BINARYENTRYPOINTFIELD(price_optional);
    BINARYENTRYPOINTFIELD(investor_id);
};

static_assert(sizeof(simple_new_order_message_section_1) == simple_new_order_message_section_1::size, "simple_new_order_message_section_1 lies over its bytes exactly");

// Simple New Order Message: SimpleNewOrderMessage
struct simple_new_order_message {
    static constexpr std::string_view name = "Simple New Order Message";
    static constexpr bool is_message = true;
};

// Retransmit Reject Message: RetransmitRejectMessage
struct retransmit_reject_message {
    static constexpr std::string_view name = "Retransmit Reject Message";
    static constexpr std::size_t size = 13;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        session_id,
        request_timestamp,
        retransmit_reject_code>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYENTRYPOINTFIELD(session_id);
    BINARYENTRYPOINTFIELD(request_timestamp);
    BINARYENTRYPOINTFIELD(retransmit_reject_code);
};

static_assert(sizeof(retransmit_reject_message) == retransmit_reject_message::size, "retransmit_reject_message lies over its bytes exactly");

// Retransmission Message: RetransmissionMessage
struct retransmission_message {
    static constexpr std::string_view name = "Retransmission Message";
    static constexpr std::size_t size = 20;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        session_id,
        request_timestamp,
        next_seq_no,
        count_type>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYENTRYPOINTFIELD(session_id);
    BINARYENTRYPOINTFIELD(request_timestamp);
    BINARYENTRYPOINTFIELD(next_seq_no);
    BINARYENTRYPOINTFIELD(count_type);
};

static_assert(sizeof(retransmission_message) == retransmission_message::size, "retransmission_message lies over its bytes exactly");

// Retransmit Request Message: RetransmitRequestMessage
struct retransmit_request_message {
    static constexpr std::string_view name = "Retransmit Request Message";
    static constexpr std::size_t size = 20;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        session_id,
        timestamp,
        from_seq_no,
        count_type>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYENTRYPOINTFIELD(session_id);
    BINARYENTRYPOINTFIELD(timestamp);
    BINARYENTRYPOINTFIELD(from_seq_no);
    BINARYENTRYPOINTFIELD(count_type);
};

static_assert(sizeof(retransmit_request_message) == retransmit_request_message::size, "retransmit_request_message lies over its bytes exactly");

// Sequence Message: SequenceMessage
struct sequence_message {
    static constexpr std::string_view name = "Sequence Message";
    static constexpr std::size_t size = 4;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        next_seq_no>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYENTRYPOINTFIELD(next_seq_no);
};

static_assert(sizeof(sequence_message) == sequence_message::size, "sequence_message lies over its bytes exactly");

// Not Applied Message: NotAppliedMessage
struct not_applied_message {
    static constexpr std::string_view name = "Not Applied Message";
    static constexpr std::size_t size = 8;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        from_seq_no,
        count_type>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYENTRYPOINTFIELD(from_seq_no);
    BINARYENTRYPOINTFIELD(count_type);
};

static_assert(sizeof(not_applied_message) == not_applied_message::size, "not_applied_message lies over its bytes exactly");

// Terminate Message: TerminateMessage
struct terminate_message {
    static constexpr std::string_view name = "Terminate Message";
    static constexpr std::size_t size = 13;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        session_id,
        session_ver_id,
        termination_code>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYENTRYPOINTFIELD(session_id);
    BINARYENTRYPOINTFIELD(session_ver_id);
    BINARYENTRYPOINTFIELD(termination_code);
};

static_assert(sizeof(terminate_message) == terminate_message::size, "terminate_message lies over its bytes exactly");

// Establish Reject Message: EstablishRejectMessage
struct establish_reject_message {
    static constexpr std::string_view name = "Establish Reject Message";
    static constexpr std::size_t size = 26;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        session_id,
        session_ver_id,
        request_timestamp,
        establishment_reject_code,
        offset_21_padding_1,
        last_incoming_seq_no_optional>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYENTRYPOINTFIELD(session_id);
    BINARYENTRYPOINTFIELD(session_ver_id);
    BINARYENTRYPOINTFIELD(request_timestamp);
    BINARYENTRYPOINTFIELD(establishment_reject_code);
    BINARYENTRYPOINTFIELD(offset_21_padding_1);
    BINARYENTRYPOINTFIELD(last_incoming_seq_no_optional);
};

static_assert(sizeof(establish_reject_message) == establish_reject_message::size, "establish_reject_message lies over its bytes exactly");

// Establish Ack Message: EstablishAckMessage
struct establish_ack_message {
    static constexpr std::string_view name = "Establish Ack Message";
    static constexpr std::size_t size = 36;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        session_id,
        session_ver_id,
        request_timestamp,
        keep_alive_interval,
        next_seq_no,
        last_incoming_seq_no>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYENTRYPOINTFIELD(session_id);
    BINARYENTRYPOINTFIELD(session_ver_id);
    BINARYENTRYPOINTFIELD(request_timestamp);
    BINARYENTRYPOINTFIELD(keep_alive_interval);
    BINARYENTRYPOINTFIELD(next_seq_no);
    BINARYENTRYPOINTFIELD(last_incoming_seq_no);
};

static_assert(sizeof(establish_ack_message) == establish_ack_message::size, "establish_ack_message lies over its bytes exactly");

// Credentials Section 1
struct credentials_section_1 {
    static constexpr std::string_view name = "Credentials Section 1";
    static constexpr std::size_t size = 1;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        credentials_length>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYENTRYPOINTFIELD(credentials_length);
};

static_assert(sizeof(credentials_section_1) == credentials_section_1::size, "credentials_section_1 lies over its bytes exactly");

// Credentials: credentials data struct
struct credentials {
    static constexpr std::string_view name = "Credentials";
    static constexpr bool is_message = false;
};

// Establish Message Section 1
struct establish_message_section_1 {
    static constexpr std::string_view name = "Establish Message Section 1";
    static constexpr std::size_t size = 42;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        session_id,
        session_ver_id,
        timestamp,
        keep_alive_interval,
        next_seq_no,
        cancel_on_disconnect_type,
        offset_33_padding_1,
        cod_timeout_window>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYENTRYPOINTFIELD(session_id);
    BINARYENTRYPOINTFIELD(session_ver_id);
    BINARYENTRYPOINTFIELD(timestamp);
    BINARYENTRYPOINTFIELD(keep_alive_interval);
    BINARYENTRYPOINTFIELD(next_seq_no);
    BINARYENTRYPOINTFIELD(cancel_on_disconnect_type);
    BINARYENTRYPOINTFIELD(offset_33_padding_1);
    BINARYENTRYPOINTFIELD(cod_timeout_window);
};

static_assert(sizeof(establish_message_section_1) == establish_message_section_1::size, "establish_message_section_1 lies over its bytes exactly");

// Establish Message: EstablishMessage
struct establish_message {
    static constexpr std::string_view name = "Establish Message";
    static constexpr bool is_message = true;
};

// Negotiate Reject Message: NegotiateRejectMessage
struct negotiate_reject_message {
    static constexpr std::string_view name = "Negotiate Reject Message";
    static constexpr std::size_t size = 36;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        session_id,
        session_ver_id,
        request_timestamp,
        entering_firm_optional,
        negotiation_reject_code,
        offset_25_padding_3,
        current_session_ver_id>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYENTRYPOINTFIELD(session_id);
    BINARYENTRYPOINTFIELD(session_ver_id);
    BINARYENTRYPOINTFIELD(request_timestamp);
    BINARYENTRYPOINTFIELD(entering_firm_optional);
    BINARYENTRYPOINTFIELD(negotiation_reject_code);
    BINARYENTRYPOINTFIELD(offset_25_padding_3);
    BINARYENTRYPOINTFIELD(current_session_ver_id);
};

static_assert(sizeof(negotiate_reject_message) == negotiate_reject_message::size, "negotiate_reject_message lies over its bytes exactly");

// Negotiate Response Message: NegotiateResponseMessage
struct negotiate_response_message {
    static constexpr std::string_view name = "Negotiate Response Message";
    static constexpr std::size_t size = 24;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        session_id,
        session_ver_id,
        request_timestamp,
        entering_firm>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYENTRYPOINTFIELD(session_id);
    BINARYENTRYPOINTFIELD(session_ver_id);
    BINARYENTRYPOINTFIELD(request_timestamp);
    BINARYENTRYPOINTFIELD(entering_firm);
};

static_assert(sizeof(negotiate_response_message) == negotiate_response_message::size, "negotiate_response_message lies over its bytes exactly");

// Client App Version Section 1
struct client_app_version_section_1 {
    static constexpr std::string_view name = "Client App Version Section 1";
    static constexpr std::size_t size = 1;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        client_app_version_length>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYENTRYPOINTFIELD(client_app_version_length);
};

static_assert(sizeof(client_app_version_section_1) == client_app_version_section_1::size, "client_app_version_section_1 lies over its bytes exactly");

// Client App Version: clientAppVersion data struct
struct client_app_version {
    static constexpr std::string_view name = "Client App Version";
    static constexpr bool is_message = false;
};

// Client App Name Section 1
struct client_app_name_section_1 {
    static constexpr std::string_view name = "Client App Name Section 1";
    static constexpr std::size_t size = 1;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        client_app_name_length>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYENTRYPOINTFIELD(client_app_name_length);
};

static_assert(sizeof(client_app_name_section_1) == client_app_name_section_1::size, "client_app_name_section_1 lies over its bytes exactly");

// Client App Name: clientAppName data struct
struct client_app_name {
    static constexpr std::string_view name = "Client App Name";
    static constexpr bool is_message = false;
};

// Client Ip Section 1
struct client_ip_section_1 {
    static constexpr std::string_view name = "Client Ip Section 1";
    static constexpr std::size_t size = 1;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        client_ip_length>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYENTRYPOINTFIELD(client_ip_length);
};

static_assert(sizeof(client_ip_section_1) == client_ip_section_1::size, "client_ip_section_1 lies over its bytes exactly");

// Client Ip: clientIP data struct
struct client_ip {
    static constexpr std::string_view name = "Client Ip";
    static constexpr bool is_message = false;
};

// Negotiate Message Section 1
struct negotiate_message_section_1 {
    static constexpr std::string_view name = "Negotiate Message Section 1";
    static constexpr std::size_t size = 28;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        session_id,
        session_ver_id,
        timestamp,
        entering_firm,
        onbehalf_firm>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYENTRYPOINTFIELD(session_id);
    BINARYENTRYPOINTFIELD(session_ver_id);
    BINARYENTRYPOINTFIELD(timestamp);
    BINARYENTRYPOINTFIELD(entering_firm);
    BINARYENTRYPOINTFIELD(onbehalf_firm);
};

static_assert(sizeof(negotiate_message_section_1) == negotiate_message_section_1::size, "negotiate_message_section_1 lies over its bytes exactly");

// Negotiate Message: NegotiateMessage
struct negotiate_message {
    static constexpr std::string_view name = "Negotiate Message";
    static constexpr bool is_message = true;
};

// Payload: Branch
struct payload {
    static constexpr std::string_view name = "Payload";
    static constexpr bool is_message = false;
};

// Message Header: B3 Sbe message header — message identifiers and length of message root
struct message_header {
    static constexpr std::string_view name = "Message Header";
    static constexpr std::size_t size = 8;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        block_length,
        template_id,
        schema_id,
        version>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYENTRYPOINTFIELD(block_length);
    BINARYENTRYPOINTFIELD(template_id);
    BINARYENTRYPOINTFIELD(schema_id);
    BINARYENTRYPOINTFIELD(version);
};

static_assert(sizeof(message_header) == message_header::size, "message_header lies over its bytes exactly");

// Simple Open Framing Header
struct simple_open_framing_header {
    static constexpr std::string_view name = "Simple Open Framing Header";
    static constexpr std::size_t size = 4;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        message_length,
        encoding_type>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYENTRYPOINTFIELD(message_length);
    BINARYENTRYPOINTFIELD(encoding_type);
};

static_assert(sizeof(simple_open_framing_header) == simple_open_framing_header::size, "simple_open_framing_header lies over its bytes exactly");

// Simple Open Frame Section 1
struct simple_open_frame_section_1 {
    static constexpr std::string_view name = "Simple Open Frame Section 1";
    static constexpr std::size_t size = 12;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        simple_open_framing_header,
        message_header>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYENTRYPOINTFIELD(simple_open_framing_header);
    BINARYENTRYPOINTFIELD(message_header);
};

static_assert(sizeof(simple_open_frame_section_1) == simple_open_frame_section_1::size, "simple_open_frame_section_1 lies over its bytes exactly");

// Simple Open Frame
struct simple_open_frame {
    static constexpr std::string_view name = "Simple Open Frame";
    static constexpr bool is_message = false;
};

// Packet: Simple Open Frame Packet
struct packet {
    static constexpr std::string_view name = "Packet";
    static constexpr bool is_message = false;
};

#pragma pack(pop)

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0
