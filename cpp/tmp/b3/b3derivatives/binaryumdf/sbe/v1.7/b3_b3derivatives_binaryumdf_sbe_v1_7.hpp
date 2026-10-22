// B3 B3Derivatives BinaryUmdf Sbe 1.7 Template Meta Programming

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
#ifndef BINARYUMDFFIELD
#define BINARYUMDFFIELD(type) constexpr const type& ref(const type*) const noexcept { return type##_; } type type##_
#endif

// A repeating group of a message: its entries' type, which the parse hands over one at a time; no bytes
#ifndef BINARYUMDFSEQUENCE
#define BINARYUMDFSEQUENCE(type) using type##_sequence = tmp::sequence<type>
#endif

namespace b3::b3derivatives::binaryumdf::sbe::v1_7 {

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
} // namespace tmp

/////////////////////////////////////////////////////////////////////
// Types
/////////////////////////////////////////////////////////////////////

// Aggressor Side: aggressorSide
struct aggressor_side {
    enum class type : std::uint8_t {
        no_aggressor = 0,
        buy = 1,
        sell = 2,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Aggressor Time: aggressorTime
struct aggressor_time {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
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

// Avg Daily Traded Qty: avgDailyTradedQty
struct avg_daily_traded_qty {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(-9223372036854775807LL - 1);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
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

// Block Trade: BlockTrade
struct block_trade {
    using type = bool;
    static constexpr std::uint64_t mask = 0x4000ULL;
    static constexpr int shift = 14;
};

// Cfi Code: cfiCode
struct cfi_code {
    using type = std::string_view;
    static constexpr std::size_t size = 6;
    static constexpr char fill = '\0';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 6> value_;
};

// Channel Id: B3 Channel Id
struct channel_id {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Clearing House Id: clearingHouseID
struct clearing_house_id {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Contract Multiplier: contractMultiplier
struct contract_multiplier {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(-9223372036854775807LL - 1);
    static constexpr int exponent = -8;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Corporate Action Event Id: corporateActionEventId
struct corporate_action_event_id {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Country Of Issue: countryOfIssue
struct country_of_issue {
    using type = std::string_view;
    static constexpr std::size_t size = 2;
    static constexpr char fill = '\0';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 2> value_;
};

// Crossed
struct crossed {
    using type = bool;
    static constexpr std::uint64_t mask = 0x2ULL;
    static constexpr int shift = 1;
};

// Currency
struct currency {
    using type = std::string_view;
    static constexpr std::size_t size = 3;
    static constexpr char fill = '\0';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 3> value_;
};

// Cxl Qty: cxlQty
struct cxl_qty {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(-9223372036854775807LL - 1);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Dated Date: datedDate
struct dated_date {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0LL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Day
struct day {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
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

// End Date: endDate
struct end_date {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0LL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// End Of Event: EndOfEvent
struct end_of_event {
    using type = bool;
    static constexpr std::uint64_t mask = 0x80ULL;
    static constexpr int shift = 7;
};

// Entering Firm: enteringFirm
struct entering_firm {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Exercise Style: exerciseStyle
struct exercise_style {
    enum class type : std::uint8_t {
        european = 0,
        american = 1,
    };

    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(255);

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Fill Qty: fillQty
struct fill_qty {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Governance Indicator: governanceIndicator
struct governance_indicator {
    enum class type : std::uint8_t {
        no = 0,
        n_1 = 1,
        n_2 = 2,
        nm = 4,
        ma = 5,
        mb = 6,
        m_2 = 7,
    };

    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(255);

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Headline Data: Bytes of the string, encoded in UTF-8.
struct headline_data {
    using type = std::string_view;
    static constexpr bool dynamic = true;

    constexpr headline_data(const std::byte* data, std::size_t length) noexcept : data_{ data }, length_{ length } {}

    constexpr type value() const noexcept { return { reinterpret_cast<const char*>(data_), length_ }; }
    constexpr operator type() const noexcept { return value(); }
    // the bytes it takes
    constexpr std::size_t length() const noexcept { return length_; }

  protected:
    const std::byte* data_;
    std::size_t length_;
};

// Headline Length: Length of a string, in bytes. For instance, the string 'Ação', converted to UTF-8, has 6 bytes, so length = 6.
struct headline_length {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// High Limit Price: highLimitPrice
struct high_limit_price {
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

// Imbalance More Buyers: ImbalanceMoreBuyers
struct imbalance_more_buyers {
    using type = bool;
    static constexpr std::uint64_t mask = 0x100ULL;
    static constexpr int shift = 8;
};

// Imbalance More Sellers: ImbalanceMoreSellers
struct imbalance_more_sellers {
    using type = bool;
    static constexpr std::uint64_t mask = 0x200ULL;
    static constexpr int shift = 9;
};

// Index Pct: Required if this is an equity index instrument. Indicates the percentage that this underlying composes the index.
struct index_pct {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0LL);
    static constexpr int exponent = -9;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Index Theoretical Qty: The theoretical quantity of this underlying composing the index. This tag is only used for index instruments.
struct index_theoretical_qty {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(-9223372036854775807LL - 1);
    static constexpr int exponent = -8;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Instr Attrib Type: Code to represent the type of instrument attributes.
struct instr_attrib_type {
    enum class type : std::uint8_t {
        trade_type_eligibility = 24,
        gtd_gtc_eligibility = 34,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Instr Attrib Value: Attribute value appropriate to the InstrAttribType (871) field.
struct instr_attrib_value {
    enum class type : std::uint8_t {
        electronic_match_or_gtd_gtc_eligible = 1,
        order_cross_eligible = 2,
        block_trade_eligible = 3,
        flag_rfq_for_cross_eligible = 14,
        negotiated_quote_eligible = 17,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Isin Number: isinNumber
struct isin_number {
    using type = std::string_view;
    static constexpr std::size_t size = 12;
    static constexpr char fill = '\0';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 12> value_;
};

// Issue Date: issueDate
struct issue_date {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Language Code: languageCode
struct language_code {
    using type = std::string_view;
    static constexpr std::size_t size = 2;
    static constexpr char fill = '\0';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 2> value_;
};

// Last Fragment: lastFragment
struct last_fragment {
    enum class type : std::uint8_t {
        false_value = 0,
        true_value = 1,
    };

    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(255);

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Last Implied Msg: LastImpliedMsg
struct last_implied_msg {
    using type = bool;
    static constexpr std::uint64_t mask = 0x10ULL;
    static constexpr int shift = 4;
};

// Last Msg Seq Num Processed: lastMsgSeqNumProcessed
struct last_msg_seq_num_processed {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

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

// Last Quote Msg: LastQuoteMsg
struct last_quote_msg {
    using type = bool;
    static constexpr std::uint64_t mask = 0x4ULL;
    static constexpr int shift = 2;
};

// Last Rpt Seq: lastRptSeq
struct last_rpt_seq {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Last Stats Msg: LastStatsMsg
struct last_stats_msg {
    using type = bool;
    static constexpr std::uint64_t mask = 0x8ULL;
    static constexpr int shift = 3;
};

// Last Trade At The Same Price: LastTradeAtTheSamePrice
struct last_trade_at_the_same_price {
    using type = bool;
    static constexpr std::uint64_t mask = 0x4ULL;
    static constexpr int shift = 2;
};

// Last Trade Date: lastTradeDate
struct last_trade_date {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Last Trade Msg: LastTradeMsg
struct last_trade_msg {
    using type = bool;
    static constexpr std::uint64_t mask = 0x1ULL;
    static constexpr int shift = 0;
};

// Last Volume Msg: LastVolumeMsg
struct last_volume_msg {
    using type = bool;
    static constexpr std::uint64_t mask = 0x2ULL;
    static constexpr int shift = 1;
};

// Leg Ratio Qty: Ratio of quantity for this leg relative to the entire security.
struct leg_ratio_qty {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(-9223372036854775807LL - 1);
    static constexpr int exponent = -7;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Leg Security Id: Leg's security ID.
struct leg_security_id {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Leg Security Type: Leg's security type.
struct leg_security_type {
    enum class type : std::uint8_t {
        cash = 1,
        corp = 2,
        cs = 3,
        dterm = 4,
        etf = 5,
        fopt = 6,
        forward = 7,
        fut = 8,
        index = 9,
        indexopt = 10,
        mleg = 11,
        opt = 12,
        optexer = 13,
        ps = 14,
        secloan = 15,
        sopt = 16,
        spot = 17,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Leg Side: Side of this leg.
struct leg_side {
    enum class type : std::uint8_t {
        buy = 1,
        sell = 2,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Leg Symbol: Leg symbol.
struct leg_symbol {
    using type = std::string_view;
    static constexpr std::size_t size = 20;
    static constexpr char fill = '\0';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 20> value_;
};

// Lot Type: lotType
struct lot_type {
    enum class type : std::uint8_t {
        odd_lot = 1,
        round_lot = 2,
        block_lot = 3,
    };

    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(255);

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Low Limit Price: lowLimitPrice
struct low_limit_price {
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

// Market Segment Id: marketSegmentID
struct market_segment_id {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(0ULL);

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Maturity Date: maturityDate
struct maturity_date {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0LL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Max Order Qty: maxOrderQty
struct max_order_qty {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(-9223372036854775807LL - 1);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Max Trade Vol: maxTradeVol
struct max_trade_vol {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(-9223372036854775807LL - 1);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Md Corporate Offset Price Optional: mDEntryPx
struct md_corporate_offset_price_optional {
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

// Md Corporate Price: mDEntryPx
struct md_corporate_price {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -8;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Md Entry Buyer: mDEntryBuyer
struct md_entry_buyer {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Md Entry Interest Rate: mDEntryInterestRate
struct md_entry_interest_rate {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0LL);
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Md Entry Position No: mDEntryPositionNo
struct md_entry_position_no {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Md Entry Seller: mDEntrySeller
struct md_entry_seller {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Md Entry Size Quantity: mDEntrySize
struct md_entry_size_quantity {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Md Entry Size Quantity Optional: mDEntrySize
struct md_entry_size_quantity_optional {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(-9223372036854775807LL - 1);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Md Entry Timestamp: mDEntryTimestamp
struct md_entry_timestamp {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Md Entry Type: mDEntryType
struct md_entry_type {
    enum class type : char {
        bid = '0',
        offer = '1',
        trade = '2',
        index_value = '3',
        opening_price = '4',
        closing_price = '5',
        settlement_price = '6',
        session_high_price = '7',
        session_low_price = '8',
        execution_statistics = '9',
        imbalance = 'A',
        trade_volume = 'B',
        open_interest = 'C',
        empty_book = 'J',
        security_trading_state_phase = 'c',
        price_band = 'g',
        quantity_band = 'h',
        composite_underlying_price = 'D',
        execution_summary = 's',
        volatility_price = 'v',
        trade_bust = 'u',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Md Future Price: mDEntryPx
struct md_future_price {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Md Insert Timestamp: mDInsertTimestamp
struct md_insert_timestamp {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Md Update Action: mDUpdateAction
struct md_update_action {
    enum class type : std::uint8_t {
        new_value = 0,
        change = 1,
        delete_value = 2,
        delete_thru = 3,
        delete_from = 4,
        overlay = 5,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
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

// Min Cross Qty: minCrossQty
struct min_cross_qty {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(-9223372036854775807LL - 1);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Min Lot Size: minLotSize
struct min_lot_size {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(-9223372036854775807LL - 1);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Min Order Qty: minOrderQty
struct min_order_qty {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(-9223372036854775807LL - 1);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Min Price Increment Legacy: minPriceIncrement
struct min_price_increment_legacy {
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

// Min Price Increment Optional: minPriceIncrement
struct min_price_increment_optional {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(-9223372036854775807LL - 1);
    static constexpr int exponent = -8;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Min Trade Vol: minTradeVol
struct min_trade_vol {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(-9223372036854775807LL - 1);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Month
struct month {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Multi Leg Model: multiLegModel
struct multi_leg_model {
    enum class type : std::uint8_t {
        predefined = 0,
        user_defined = 1,
    };

    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(255);

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Multi Leg Price Method: multiLegPriceMethod
struct multi_leg_price_method {
    enum class type : std::uint8_t {
        net_price = 0,
        reversed_net_price = 1,
        yield_difference = 2,
        individual = 3,
        contract_weighted_average_price = 4,
        multiplied_price = 5,
    };

    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(255);

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Net Chg Prev Day: netChgPrevDay
struct net_chg_prev_day {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(-9223372036854775807LL - 1);
    static constexpr int exponent = -8;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// News Id: newsID
struct news_id {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// News Source: newsSource
struct news_source {
    enum class type : std::uint8_t {
        other = 0,
        dcm = 1,
        bbmnet = 2,
        market_surveillance = 3,
        internet = 4,
        dpr_ve = 5,
        mkt_ops_fx_agency = 19,
        mkt_ops_derivatives_agency = 20,
        over_the_counter_news_agency = 11,
        electronic_purchase_exchange = 13,
        cblc_news_agency = 14,
        bovespa_index_agency = 15,
        bovespa_institutional_agency = 16,
        mkt_ops_equities_agency = 17,
        bovespa_companies_agency = 18,
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

// No Shares Issued: noSharesIssued
struct no_shares_issued {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0ULL);

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

// Number Of Trades: numberOfTrades
struct number_of_trades {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Offset 1 Padding 3: 3 bytes padding
struct offset_1_padding_3 {
    using type = std::uint32_t;
    static constexpr std::size_t size = 3;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::assembled<order, type>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<std::byte, 3> value_;
};

// Offset 10 Padding 2: 2 bytes padding
struct offset_10_padding_2 {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Offset 11 Padding 1: 1 bytes padding
struct offset_11_padding_1 {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Offset 14 Padding 2: 2 bytes padding
struct offset_14_padding_2 {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Offset 26 Padding 2: 2 bytes padding
struct offset_26_padding_2 {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Offset 3 Padding 5: 5 bytes padding
struct offset_3_padding_5 {
    using type = std::uint64_t;
    static constexpr std::size_t size = 5;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::assembled<order, type>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<std::byte, 5> value_;
};

// Offset 34 Padding 2: 2 bytes padding
struct offset_34_padding_2 {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Offset 43 Padding 1: 1 bytes padding
struct offset_43_padding_1 {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Offset 8 Padding 2: 2 bytes padding
struct offset_8_padding_2 {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Offset 9 Padding 1: 1 bytes padding
struct offset_9_padding_1 {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Offset 9 Padding 3: 3 bytes padding
struct offset_9_padding_3 {
    using type = std::uint32_t;
    static constexpr std::size_t size = 3;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::assembled<order, type>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<std::byte, 3> value_;
};

// Open Close Settl Flag: openCloseSettlFlag
struct open_close_settl_flag {
    enum class type : std::uint8_t {
        daily = 0,
        session = 1,
        expected_entry = 3,
        entry_from_previous_business_day = 4,
        theoretical_price = 5,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Opening Price: OpeningPrice
struct opening_price {
    using type = bool;
    static constexpr std::uint64_t mask = 0x1ULL;
    static constexpr int shift = 0;
};

// Orig Time: origTime
struct orig_time {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Out Of Sequence: OutOfSequence
struct out_of_sequence {
    using type = bool;
    static constexpr std::uint64_t mask = 0x8ULL;
    static constexpr int shift = 3;
};

// Packet Reserved: Packet Reserved Field
struct packet_reserved {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Padding 2: 2 bytes padding
struct padding_2 {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Padding 3: 3 bytes padding
struct padding_3 {
    using type = std::uint32_t;
    static constexpr std::size_t size = 3;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::assembled<order, type>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<std::byte, 3> value_;
};

// Part Count: partCount
struct part_count {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Part Number: partNumber
struct part_number {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Price Band Midpoint Price Type: priceBandMidpointPriceType
struct price_band_midpoint_price_type {
    enum class type : std::uint8_t {
        last_traded_price = 0,
        complementary_last_price = 1,
        theoretical_price = 2,
    };

    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(255);

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Price Band Type: priceBandType
struct price_band_type {
    enum class type : std::uint8_t {
        hard_limit = 1,
        auction_limits = 2,
        rejection_band = 3,
        static_limits = 4,
    };

    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(255);

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Price Divisor: priceDivisor
struct price_divisor {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(-9223372036854775807LL - 1);
    static constexpr int exponent = -8;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Price Limit Type: priceLimitType
struct price_limit_type {
    enum class type : std::uint8_t {
        price_unit = 0,
        ticks = 1,
        percentage = 2,
    };

    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(255);

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Price Type: priceType
struct price_type {
    enum class type : std::uint8_t {
        percentage = 1,
        pu = 2,
        fixed_amount = 3,
    };

    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(0);

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Product
struct product {
    enum class type : std::uint8_t {
        commodity = 2,
        corporate = 3,
        currency = 4,
        equity = 5,
        government = 6,
        index = 7,
        economic_indicator = 15,
        multileg = 16,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Put Or Call: putOrCall
struct put_or_call {
    enum class type : std::uint8_t {
        put = 0,
        call = 1,
    };

    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(255);

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Recovery Msg: RecoveryMsg
struct recovery_msg {
    using type = bool;
    static constexpr std::uint64_t mask = 0x20ULL;
    static constexpr int shift = 5;
};

// Regular Trade: RegularTrade
struct regular_trade {
    using type = bool;
    static constexpr std::uint64_t mask = 0x2000ULL;
    static constexpr int shift = 13;
};

// Reserved
struct reserved {
    using type = bool;
    static constexpr std::uint64_t mask = 0x40ULL;
    static constexpr int shift = 6;
};

// Reserved 6: 6 reserved bits
struct reserved_6 {
    using type = std::uint16_t;
    static constexpr std::uint64_t mask = 0xFC00ULL;
    static constexpr int shift = 10;
};

// Rpt Seq: rptSeq
struct rpt_seq {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
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

// Security Desc Data: textual description for the financial instrument
struct security_desc_data {
    using type = std::string_view;
    static constexpr bool dynamic = true;

    constexpr security_desc_data(const std::byte* data, std::size_t length) noexcept : data_{ data }, length_{ length } {}

    constexpr type value() const noexcept { return { reinterpret_cast<const char*>(data_), length_ }; }
    constexpr operator type() const noexcept { return value(); }
    // the bytes it takes
    constexpr std::size_t length() const noexcept { return length_; }

  protected:
    const std::byte* data_;
    std::size_t length_;
};

// Security Desc Length: Length in bytes of the security description text
struct security_desc_length {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Security Exchange: securityExchange
struct security_exchange {
    using type = std::string_view;
    static constexpr std::size_t size = 4;
    static constexpr char fill = '\0';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 4> value_;
};

// Security Group: securityGroup
struct security_group {
    using type = std::string_view;
    static constexpr std::size_t size = 3;
    static constexpr char fill = '\0';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 3> value_;
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

// Security Id Optional: Security Id as defined by B3. For the Security Id list, see the Security Definition message in the market data feed
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

// Security Id Source: securityIDSource
struct security_id_source {
    enum class type : char {
        isin = '4',
        exchange_symbol = '8',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Security Match Type: securityMatchType
struct security_match_type {
    enum class type : std::uint8_t {
        issuing_buy_back_auction = 8,
    };

    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(255);

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

// Security Sub Type: securitySubType
struct security_sub_type {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Security Trading Event: securityTradingEvent
struct security_trading_event {
    enum class type : std::uint8_t {
        trading_session_change = 4,
        security_status_change = 101,
        security_rejoins_security_group_status = 102,
    };

    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(255);

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Security Trading Status: securityTradingStatus
struct security_trading_status {
    enum class type : std::uint8_t {
        pause = 2,
        close = 4,
        open = 17,
        forbidden = 18,
        unknown_or_invalid = 20,
        reserved = 21,
        final_closing_call = 101,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Security Type: securityType
struct security_type {
    enum class type : std::uint8_t {
        cash = 1,
        corp = 2,
        cs = 3,
        dterm = 4,
        etf = 5,
        fopt = 6,
        forward = 7,
        fut = 8,
        index = 9,
        indexopt = 10,
        mleg = 11,
        opt = 12,
        optexer = 13,
        ps = 14,
        secloan = 15,
        sopt = 16,
        spot = 17,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Security Update Action: securityUpdateAction
struct security_update_action {
    enum class type : char {
        add = 'A',
        delete_value = 'D',
        modify = 'M',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Security Validity Timestamp: securityValidityTimestamp
struct security_validity_timestamp {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(-9223372036854775807LL - 1);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Seller Days: sellerDays
struct seller_days {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Sending Time: Packet Sending Time
struct sending_time {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Sequence Number: Packet Sequence Number
struct sequence_number {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Sequence Version: Packet Sequence Version
struct sequence_version {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Settl Currency: settlCurrency
struct settl_currency {
    using type = std::string_view;
    static constexpr std::size_t size = 3;
    static constexpr char fill = '\0';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 3> value_;
};

// Settl Date: settlDate
struct settl_date {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0LL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Settl Type: settlType
struct settl_type {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(65535ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Start Date: startDate
struct start_date {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0LL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Strike Currency: strikeCurrency
struct strike_currency {
    using type = std::string_view;
    static constexpr std::size_t size = 3;
    static constexpr char fill = '\0';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 3> value_;
};

// Strike Price: strikePrice
struct strike_price {
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
        sequence_reset_1_message = 1,
        sequence_2_message = 2,
        empty_book_9_message = 9,
        channel_reset_11_message = 11,
        security_status_3_message = 3,
        security_group_phase_10_message = 10,
        deprecatedsecurity_definition_message = 4,
        security_definition_message = 12,
        news_5_message = 5,
        opening_price_15_message = 15,
        theoretical_opening_price_16_message = 16,
        closing_price_17_message = 17,
        auction_imbalance_19_message = 19,
        price_band_20_message = 20,
        quantity_band_21_message = 21,
        price_band_22_message = 22,
        high_price_24_message = 24,
        low_price_25_message = 25,
        last_trade_price_27_message = 27,
        snapshot_full_refresh_header_30_message = 30,
        order_mb_o_50_message = 50,
        delete_order_mb_o_51_message = 51,
        mass_delete_orders_mb_o_52_message = 52,
        trade_53_message = 53,
        forward_trade_54_message = 54,
        execution_summary_55_message = 55,
        execution_statistics_56_message = 56,
        trade_bust_57_message = 57,
        snapshot_full_refresh_orders_mb_o_71_message = 71,
    };

    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return tmp::ordered<order>(value_); }

  protected:
    std::underlying_type_t<type> value_;
};

// Text Data: Bytes of the string, encoded in UTF-8.
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

// Text Length: Length of a string, in bytes. For instance, the string 'Ação', converted to UTF-8, has 6 bytes, so length = 6.
struct text_length {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Tick Size Denominator: tickSizeDenominator
struct tick_size_denominator {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(255ULL);

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Tot No Related Sym: totNoRelatedSym
struct tot_no_related_sym {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Tot Num Bids: totNumBids
struct tot_num_bids {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Tot Num Offers: totNumOffers
struct tot_num_offers {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Tot Num Reports: totNumReports
struct tot_num_reports {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Tot Num Stats: totNumStats
struct tot_num_stats {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Total Text Length: totalTextLength
struct total_text_length {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Trad Ses Open Time: tradSesOpenTime
struct trad_ses_open_time {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
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

// Trade On Behalf: TradeOnBehalf
struct trade_on_behalf {
    using type = bool;
    static constexpr std::uint64_t mask = 0x40ULL;
    static constexpr int shift = 6;
};

// Trade Volume: tradeVolume
struct trade_volume {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Traded Hidden Qty: tradedHiddenQty
struct traded_hidden_qty {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(-9223372036854775807LL - 1);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Trading Reference Price Legacy: tradingReferencePrice
struct trading_reference_price_legacy {
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

// Trading Reference Price Optional: tradingReferencePrice
struct trading_reference_price_optional {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(-9223372036854775807LL - 1);
    static constexpr int exponent = -8;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Trading Session Id: tradingSessionID
struct trading_session_id {
    enum class type : std::uint8_t {
        regular_trading_session = 1,
        non_regular_trading_session = 6,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Trading Session Sub Id: tradingSessionSubID
struct trading_session_sub_id {
    enum class type : std::uint8_t {
        pause = 2,
        close = 4,
        open = 17,
        forbidden = 18,
        unknown_or_invalid = 20,
        reserved = 21,
        final_closing_call = 101,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Transact Time: transactTime
struct transact_time {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Trd Sub Type: trdSubType
struct trd_sub_type {
    enum class type : std::uint8_t {
        multi_asset_trade = 101,
        leg_trade = 102,
        midpoint_trade = 103,
        block_book_trade = 104,
        rf_trade = 105,
        rlp_trade = 106,
        tac_trade = 107,
        taa_trade = 108,
    };

    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(0);

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Underlying Security Id: Underlying instrument's security ID.
struct underlying_security_id {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Underlying Symbol: Underlying instrument's ticker symbol.
struct underlying_symbol {
    using type = std::string_view;
    static constexpr std::size_t size = 20;
    static constexpr char fill = '\0';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 20> value_;
};

// Unused Imbalance Condition 0: Unused ImbalanceCondition 0
struct unused_imbalance_condition_0 {
    using type = bool;
    static constexpr std::uint64_t mask = 0x1ULL;
    static constexpr int shift = 0;
};

// Unused Imbalance Condition 1: Unused ImbalanceCondition 1
struct unused_imbalance_condition_1 {
    using type = bool;
    static constexpr std::uint64_t mask = 0x2ULL;
    static constexpr int shift = 1;
};

// Unused Imbalance Condition 2: Unused ImbalanceCondition 2
struct unused_imbalance_condition_2 {
    using type = bool;
    static constexpr std::uint64_t mask = 0x4ULL;
    static constexpr int shift = 2;
};

// Unused Imbalance Condition 3: Unused ImbalanceCondition 3
struct unused_imbalance_condition_3 {
    using type = bool;
    static constexpr std::uint64_t mask = 0x8ULL;
    static constexpr int shift = 3;
};

// Unused Imbalance Condition 4: Unused ImbalanceCondition 4
struct unused_imbalance_condition_4 {
    using type = bool;
    static constexpr std::uint64_t mask = 0x10ULL;
    static constexpr int shift = 4;
};

// Unused Imbalance Condition 5: Unused ImbalanceCondition 5
struct unused_imbalance_condition_5 {
    using type = bool;
    static constexpr std::uint64_t mask = 0x20ULL;
    static constexpr int shift = 5;
};

// Unused Imbalance Condition 6: Unused ImbalanceCondition 6
struct unused_imbalance_condition_6 {
    using type = bool;
    static constexpr std::uint64_t mask = 0x40ULL;
    static constexpr int shift = 6;
};

// Unused Imbalance Condition 7: Unused ImbalanceCondition 7
struct unused_imbalance_condition_7 {
    using type = bool;
    static constexpr std::uint64_t mask = 0x80ULL;
    static constexpr int shift = 7;
};

// Unused Trade Condition 10: Unused TradeCondition 10
struct unused_trade_condition_10 {
    using type = bool;
    static constexpr std::uint64_t mask = 0x400ULL;
    static constexpr int shift = 10;
};

// Unused Trade Condition 11: Unused TradeCondition 11
struct unused_trade_condition_11 {
    using type = bool;
    static constexpr std::uint64_t mask = 0x800ULL;
    static constexpr int shift = 11;
};

// Unused Trade Condition 12: Unused TradeCondition 12
struct unused_trade_condition_12 {
    using type = bool;
    static constexpr std::uint64_t mask = 0x1000ULL;
    static constexpr int shift = 12;
};

// Unused Trade Condition 15: Unused TradeCondition 15
struct unused_trade_condition_15 {
    using type = bool;
    static constexpr std::uint64_t mask = 0x8000ULL;
    static constexpr int shift = 15;
};

// Unused Trade Condition 4: Unused TradeCondition 4
struct unused_trade_condition_4 {
    using type = bool;
    static constexpr std::uint64_t mask = 0x10ULL;
    static constexpr int shift = 4;
};

// Unused Trade Condition 5: Unused TradeCondition 5
struct unused_trade_condition_5 {
    using type = bool;
    static constexpr std::uint64_t mask = 0x20ULL;
    static constexpr int shift = 5;
};

// Unused Trade Condition 7: Unused TradeCondition 7
struct unused_trade_condition_7 {
    using type = bool;
    static constexpr std::uint64_t mask = 0x80ULL;
    static constexpr int shift = 7;
};

// Unused Trade Condition 8: Unused TradeCondition 8
struct unused_trade_condition_8 {
    using type = bool;
    static constexpr std::uint64_t mask = 0x100ULL;
    static constexpr int shift = 8;
};

// Unused Trade Condition 9: Unused TradeCondition 9
struct unused_trade_condition_9 {
    using type = bool;
    static constexpr std::uint64_t mask = 0x200ULL;
    static constexpr int shift = 9;
};

// Url Link Data: Bytes of the string, encoded in UTF-8.
struct url_link_data {
    using type = std::string_view;
    static constexpr bool dynamic = true;

    constexpr url_link_data(const std::byte* data, std::size_t length) noexcept : data_{ data }, length_{ length } {}

    constexpr type value() const noexcept { return { reinterpret_cast<const char*>(data_), length_ }; }
    constexpr operator type() const noexcept { return value(); }
    // the bytes it takes
    constexpr std::size_t length() const noexcept { return length_; }

  protected:
    const std::byte* data_;
    std::size_t length_;
};

// Url Link Length: Length of a string, in bytes. For instance, the string 'Ação', converted to UTF-8, has 6 bytes, so length = 6.
struct url_link_length {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
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

// Vwap Px: vwapPx
struct vwap_px {
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

// Week
struct week {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Year
struct year {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};


/////////////////////////////////////////////////////////////////////
// Messages
/////////////////////////////////////////////////////////////////////

#pragma pack(push, 1)

// Snapshot Full Refresh Orders Mb O 71 Message no M D Entries Group: noMDEntries
struct snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_group {
    static constexpr std::string_view name = "Snapshot Full Refresh Orders Mb O 71 Message no M D Entries Group";
    static constexpr std::size_t size = 41;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        md_corporate_offset_price_optional,
        md_entry_size_quantity,
        md_entry_position_no,
        entering_firm,
        md_insert_timestamp,
        secondary_order_id,
        md_entry_type>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYUMDFFIELD(md_corporate_offset_price_optional);
    BINARYUMDFFIELD(md_entry_size_quantity);
    BINARYUMDFFIELD(md_entry_position_no);
    BINARYUMDFFIELD(entering_firm);
    BINARYUMDFFIELD(md_insert_timestamp);
    BINARYUMDFFIELD(secondary_order_id);
    BINARYUMDFFIELD(md_entry_type);
};

static_assert(sizeof(snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_group) == snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_group::size, "snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_group lies over its bytes exactly");

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
    BINARYUMDFFIELD(block_length);
    BINARYUMDFFIELD(num_in_group);
};

static_assert(sizeof(group_size_encoding) == group_size_encoding::size, "group_size_encoding lies over its bytes exactly");

// Snapshot Full Refresh Orders Mb O 71 Message no M D Entries Groups: noMDEntries Block
struct snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_groups {
    static constexpr std::string_view name = "Snapshot Full Refresh Orders Mb O 71 Message no M D Entries Groups";
    static constexpr bool is_message = false;

    // its repeating groups, whose entries the parse hands over one at a time
    BINARYUMDFSEQUENCE(snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_group);
};

// Snapshot Full Refresh Orders Mb O 71 Message Section 1
struct snapshot_full_refresh_orders_mb_o_71_message_section_1 {
    static constexpr std::string_view name = "Snapshot Full Refresh Orders Mb O 71 Message Section 1";
    static constexpr std::size_t size = 8;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        security_id>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYUMDFFIELD(security_id);
};

static_assert(sizeof(snapshot_full_refresh_orders_mb_o_71_message_section_1) == snapshot_full_refresh_orders_mb_o_71_message_section_1::size, "snapshot_full_refresh_orders_mb_o_71_message_section_1 lies over its bytes exactly");

// Snapshot Full Refresh Orders Mb O 71 Message: SnapshotFullRefresh_Orders_MBO_71Message
struct snapshot_full_refresh_orders_mb_o_71_message {
    static constexpr std::string_view name = "Snapshot Full Refresh Orders Mb O 71 Message";
    static constexpr bool is_message = true;
};

// Match Event Indicator: MatchEventIndicator bit set
struct match_event_indicator {
    static constexpr std::string_view name = "Match Event Indicator";
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    // the bits of the type asked for
    template <typename Bit>
    constexpr typename Bit::type get() const noexcept { return static_cast<typename Bit::type>((value() & Bit::mask) >> Bit::shift); }

    constexpr type value() const noexcept { return value_; }

  protected:
    type value_;
};

static_assert(sizeof(match_event_indicator) == match_event_indicator::size, "match_event_indicator lies over its bytes exactly");

// Trade Bust 57 Message: TradeBust_57Message
struct trade_bust_57_message {
    static constexpr std::string_view name = "Trade Bust 57 Message";
    static constexpr std::size_t size = 48;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        security_id,
        match_event_indicator,
        trading_session_id,
        offset_10_padding_2,
        md_future_price,
        md_entry_size_quantity,
        trade_id,
        trade_date,
        offset_34_padding_2,
        md_entry_timestamp,
        rpt_seq>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYUMDFFIELD(security_id);
    BINARYUMDFFIELD(match_event_indicator);
    BINARYUMDFFIELD(trading_session_id);
    BINARYUMDFFIELD(offset_10_padding_2);
    BINARYUMDFFIELD(md_future_price);
    BINARYUMDFFIELD(md_entry_size_quantity);
    BINARYUMDFFIELD(trade_id);
    BINARYUMDFFIELD(trade_date);
    BINARYUMDFFIELD(offset_34_padding_2);
    BINARYUMDFFIELD(md_entry_timestamp);
    BINARYUMDFFIELD(rpt_seq);
};

static_assert(sizeof(trade_bust_57_message) == trade_bust_57_message::size, "trade_bust_57_message lies over its bytes exactly");

// Execution Statistics 56 Message: ExecutionStatistics_56Message
struct execution_statistics_56_message {
    static constexpr std::string_view name = "Execution Statistics 56 Message";
    static constexpr std::size_t size = 52;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        security_id,
        match_event_indicator,
        trading_session_id,
        trade_date,
        trade_volume,
        vwap_px,
        net_chg_prev_day,
        number_of_trades,
        md_entry_timestamp,
        rpt_seq>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYUMDFFIELD(security_id);
    BINARYUMDFFIELD(match_event_indicator);
    BINARYUMDFFIELD(trading_session_id);
    BINARYUMDFFIELD(trade_date);
    BINARYUMDFFIELD(trade_volume);
    BINARYUMDFFIELD(vwap_px);
    BINARYUMDFFIELD(net_chg_prev_day);
    BINARYUMDFFIELD(number_of_trades);
    BINARYUMDFFIELD(md_entry_timestamp);
    BINARYUMDFFIELD(rpt_seq);
};

static_assert(sizeof(execution_statistics_56_message) == execution_statistics_56_message::size, "execution_statistics_56_message lies over its bytes exactly");

// Execution Summary 55 Message: ExecutionSummary_55Message
struct execution_summary_55_message {
    static constexpr std::string_view name = "Execution Summary 55 Message";
    static constexpr std::size_t size = 64;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        security_id,
        offset_8_padding_2,
        aggressor_side,
        offset_11_padding_1,
        last_px,
        fill_qty,
        traded_hidden_qty,
        cxl_qty,
        aggressor_time,
        rpt_seq,
        md_entry_timestamp>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYUMDFFIELD(security_id);
    BINARYUMDFFIELD(offset_8_padding_2);
    BINARYUMDFFIELD(aggressor_side);
    BINARYUMDFFIELD(offset_11_padding_1);
    BINARYUMDFFIELD(last_px);
    BINARYUMDFFIELD(fill_qty);
    BINARYUMDFFIELD(traded_hidden_qty);
    BINARYUMDFFIELD(cxl_qty);
    BINARYUMDFFIELD(aggressor_time);
    BINARYUMDFFIELD(rpt_seq);
    BINARYUMDFFIELD(md_entry_timestamp);
};

static_assert(sizeof(execution_summary_55_message) == execution_summary_55_message::size, "execution_summary_55_message lies over its bytes exactly");

// Trade Condition: TradeCondition bit set
struct trade_condition {
    static constexpr std::string_view name = "Trade Condition";
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    // the bits of the type asked for
    template <typename Bit>
    constexpr typename Bit::type get() const noexcept { return static_cast<typename Bit::type>((value() & Bit::mask) >> Bit::shift); }

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }

  protected:
    type value_;
};

static_assert(sizeof(trade_condition) == trade_condition::size, "trade_condition lies over its bytes exactly");

// Forward Trade 54 Message: ForwardTrade_54Message
struct forward_trade_54_message {
    static constexpr std::string_view name = "Forward Trade 54 Message";
    static constexpr std::size_t size = 68;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        security_id,
        match_event_indicator,
        trading_session_id,
        trade_condition,
        md_future_price,
        md_entry_size_quantity,
        trade_id,
        md_entry_buyer,
        md_entry_seller,
        trade_date,
        md_entry_timestamp,
        rpt_seq,
        seller_days,
        md_entry_interest_rate,
        trd_sub_type,
        padding_3>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYUMDFFIELD(security_id);
    BINARYUMDFFIELD(match_event_indicator);
    BINARYUMDFFIELD(trading_session_id);
    BINARYUMDFFIELD(trade_condition);
    BINARYUMDFFIELD(md_future_price);
    BINARYUMDFFIELD(md_entry_size_quantity);
    BINARYUMDFFIELD(trade_id);
    BINARYUMDFFIELD(md_entry_buyer);
    BINARYUMDFFIELD(md_entry_seller);
    BINARYUMDFFIELD(trade_date);
    BINARYUMDFFIELD(md_entry_timestamp);
    BINARYUMDFFIELD(rpt_seq);
    BINARYUMDFFIELD(seller_days);
    BINARYUMDFFIELD(md_entry_interest_rate);
    BINARYUMDFFIELD(trd_sub_type);
    BINARYUMDFFIELD(padding_3);
};

static_assert(sizeof(forward_trade_54_message) == forward_trade_54_message::size, "forward_trade_54_message lies over its bytes exactly");

// Trade 53 Message: Trade_53Message
struct trade_53_message {
    static constexpr std::string_view name = "Trade 53 Message";
    static constexpr std::size_t size = 56;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        security_id,
        match_event_indicator,
        trading_session_id,
        trade_condition,
        md_future_price,
        md_entry_size_quantity,
        trade_id,
        md_entry_buyer,
        md_entry_seller,
        trade_date,
        trd_sub_type,
        offset_43_padding_1,
        md_entry_timestamp,
        rpt_seq>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYUMDFFIELD(security_id);
    BINARYUMDFFIELD(match_event_indicator);
    BINARYUMDFFIELD(trading_session_id);
    BINARYUMDFFIELD(trade_condition);
    BINARYUMDFFIELD(md_future_price);
    BINARYUMDFFIELD(md_entry_size_quantity);
    BINARYUMDFFIELD(trade_id);
    BINARYUMDFFIELD(md_entry_buyer);
    BINARYUMDFFIELD(md_entry_seller);
    BINARYUMDFFIELD(trade_date);
    BINARYUMDFFIELD(trd_sub_type);
    BINARYUMDFFIELD(offset_43_padding_1);
    BINARYUMDFFIELD(md_entry_timestamp);
    BINARYUMDFFIELD(rpt_seq);
};

static_assert(sizeof(trade_53_message) == trade_53_message::size, "trade_53_message lies over its bytes exactly");

// Mass Delete Orders Mb O 52 Message: MassDeleteOrders_MBO_52Message
struct mass_delete_orders_mb_o_52_message {
    static constexpr std::string_view name = "Mass Delete Orders Mb O 52 Message";
    static constexpr std::size_t size = 28;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        security_id,
        match_event_indicator,
        md_update_action,
        md_entry_type,
        offset_11_padding_1,
        md_entry_position_no,
        md_entry_timestamp,
        rpt_seq>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYUMDFFIELD(security_id);
    BINARYUMDFFIELD(match_event_indicator);
    BINARYUMDFFIELD(md_update_action);
    BINARYUMDFFIELD(md_entry_type);
    BINARYUMDFFIELD(offset_11_padding_1);
    BINARYUMDFFIELD(md_entry_position_no);
    BINARYUMDFFIELD(md_entry_timestamp);
    BINARYUMDFFIELD(rpt_seq);
};

static_assert(sizeof(mass_delete_orders_mb_o_52_message) == mass_delete_orders_mb_o_52_message::size, "mass_delete_orders_mb_o_52_message lies over its bytes exactly");

// Delete Order Mb O 51 Message: DeleteOrder_MBO_51Message
struct delete_order_mb_o_51_message {
    static constexpr std::string_view name = "Delete Order Mb O 51 Message";
    static constexpr std::size_t size = 44;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        security_id,
        match_event_indicator,
        offset_9_padding_1,
        md_entry_type,
        offset_11_padding_1,
        md_entry_position_no,
        md_entry_size_quantity_optional,
        secondary_order_id,
        md_entry_timestamp,
        rpt_seq>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYUMDFFIELD(security_id);
    BINARYUMDFFIELD(match_event_indicator);
    BINARYUMDFFIELD(offset_9_padding_1);
    BINARYUMDFFIELD(md_entry_type);
    BINARYUMDFFIELD(offset_11_padding_1);
    BINARYUMDFFIELD(md_entry_position_no);
    BINARYUMDFFIELD(md_entry_size_quantity_optional);
    BINARYUMDFFIELD(secondary_order_id);
    BINARYUMDFFIELD(md_entry_timestamp);
    BINARYUMDFFIELD(rpt_seq);
};

static_assert(sizeof(delete_order_mb_o_51_message) == delete_order_mb_o_51_message::size, "delete_order_mb_o_51_message lies over its bytes exactly");

// Order Mb O 50 Message: Order_MBO_50Message
struct order_mb_o_50_message {
    static constexpr std::string_view name = "Order Mb O 50 Message";
    static constexpr std::size_t size = 64;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        security_id,
        match_event_indicator,
        md_update_action,
        md_entry_type,
        offset_11_padding_1,
        md_corporate_offset_price_optional,
        md_entry_size_quantity,
        md_entry_position_no,
        entering_firm,
        md_insert_timestamp,
        secondary_order_id,
        rpt_seq,
        md_entry_timestamp>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYUMDFFIELD(security_id);
    BINARYUMDFFIELD(match_event_indicator);
    BINARYUMDFFIELD(md_update_action);
    BINARYUMDFFIELD(md_entry_type);
    BINARYUMDFFIELD(offset_11_padding_1);
    BINARYUMDFFIELD(md_corporate_offset_price_optional);
    BINARYUMDFFIELD(md_entry_size_quantity);
    BINARYUMDFFIELD(md_entry_position_no);
    BINARYUMDFFIELD(entering_firm);
    BINARYUMDFFIELD(md_insert_timestamp);
    BINARYUMDFFIELD(secondary_order_id);
    BINARYUMDFFIELD(rpt_seq);
    BINARYUMDFFIELD(md_entry_timestamp);
};

static_assert(sizeof(order_mb_o_50_message) == order_mb_o_50_message::size, "order_mb_o_50_message lies over its bytes exactly");

// Snapshot Full Refresh Header 30 Message: SnapshotFullRefresh_Header_30Message
struct snapshot_full_refresh_header_30_message {
    static constexpr std::string_view name = "Snapshot Full Refresh Header 30 Message";
    static constexpr std::size_t size = 32;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        security_id,
        last_msg_seq_num_processed,
        tot_num_reports,
        tot_num_bids,
        tot_num_offers,
        tot_num_stats,
        offset_26_padding_2,
        last_rpt_seq>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYUMDFFIELD(security_id);
    BINARYUMDFFIELD(last_msg_seq_num_processed);
    BINARYUMDFFIELD(tot_num_reports);
    BINARYUMDFFIELD(tot_num_bids);
    BINARYUMDFFIELD(tot_num_offers);
    BINARYUMDFFIELD(tot_num_stats);
    BINARYUMDFFIELD(offset_26_padding_2);
    BINARYUMDFFIELD(last_rpt_seq);
};

static_assert(sizeof(snapshot_full_refresh_header_30_message) == snapshot_full_refresh_header_30_message::size, "snapshot_full_refresh_header_30_message lies over its bytes exactly");

// Last Trade Price 27 Message: LastTradePrice_27Message
struct last_trade_price_27_message {
    static constexpr std::string_view name = "Last Trade Price 27 Message";
    static constexpr std::size_t size = 68;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        security_id,
        match_event_indicator,
        trading_session_id,
        trade_condition,
        md_future_price,
        md_entry_size_quantity,
        trade_id,
        md_entry_buyer,
        md_entry_seller,
        trade_date,
        md_entry_timestamp,
        rpt_seq,
        seller_days,
        md_entry_interest_rate,
        trd_sub_type,
        padding_3>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYUMDFFIELD(security_id);
    BINARYUMDFFIELD(match_event_indicator);
    BINARYUMDFFIELD(trading_session_id);
    BINARYUMDFFIELD(trade_condition);
    BINARYUMDFFIELD(md_future_price);
    BINARYUMDFFIELD(md_entry_size_quantity);
    BINARYUMDFFIELD(trade_id);
    BINARYUMDFFIELD(md_entry_buyer);
    BINARYUMDFFIELD(md_entry_seller);
    BINARYUMDFFIELD(trade_date);
    BINARYUMDFFIELD(md_entry_timestamp);
    BINARYUMDFFIELD(rpt_seq);
    BINARYUMDFFIELD(seller_days);
    BINARYUMDFFIELD(md_entry_interest_rate);
    BINARYUMDFFIELD(trd_sub_type);
    BINARYUMDFFIELD(padding_3);
};

static_assert(sizeof(last_trade_price_27_message) == last_trade_price_27_message::size, "last_trade_price_27_message lies over its bytes exactly");

// Low Price 25 Message: LowPrice_25Message
struct low_price_25_message {
    static constexpr std::string_view name = "Low Price 25 Message";
    static constexpr std::size_t size = 32;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        security_id,
        match_event_indicator,
        md_update_action,
        trade_date,
        md_future_price,
        md_entry_timestamp,
        rpt_seq>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYUMDFFIELD(security_id);
    BINARYUMDFFIELD(match_event_indicator);
    BINARYUMDFFIELD(md_update_action);
    BINARYUMDFFIELD(trade_date);
    BINARYUMDFFIELD(md_future_price);
    BINARYUMDFFIELD(md_entry_timestamp);
    BINARYUMDFFIELD(rpt_seq);
};

static_assert(sizeof(low_price_25_message) == low_price_25_message::size, "low_price_25_message lies over its bytes exactly");

// High Price 24 Message: HighPrice_24Message
struct high_price_24_message {
    static constexpr std::string_view name = "High Price 24 Message";
    static constexpr std::size_t size = 32;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        security_id,
        match_event_indicator,
        md_update_action,
        trade_date,
        md_future_price,
        md_entry_timestamp,
        rpt_seq>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYUMDFFIELD(security_id);
    BINARYUMDFFIELD(match_event_indicator);
    BINARYUMDFFIELD(md_update_action);
    BINARYUMDFFIELD(trade_date);
    BINARYUMDFFIELD(md_future_price);
    BINARYUMDFFIELD(md_entry_timestamp);
    BINARYUMDFFIELD(rpt_seq);
};

static_assert(sizeof(high_price_24_message) == high_price_24_message::size, "high_price_24_message lies over its bytes exactly");

// Price Band 22 Message: PriceBand_22Message
struct price_band_22_message {
    static constexpr std::string_view name = "Price Band 22 Message";
    static constexpr std::size_t size = 48;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        security_id,
        match_event_indicator,
        price_band_type,
        price_limit_type,
        price_band_midpoint_price_type,
        low_limit_price,
        high_limit_price,
        trading_reference_price_optional,
        md_entry_timestamp,
        rpt_seq>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYUMDFFIELD(security_id);
    BINARYUMDFFIELD(match_event_indicator);
    BINARYUMDFFIELD(price_band_type);
    BINARYUMDFFIELD(price_limit_type);
    BINARYUMDFFIELD(price_band_midpoint_price_type);
    BINARYUMDFFIELD(low_limit_price);
    BINARYUMDFFIELD(high_limit_price);
    BINARYUMDFFIELD(trading_reference_price_optional);
    BINARYUMDFFIELD(md_entry_timestamp);
    BINARYUMDFFIELD(rpt_seq);
};

static_assert(sizeof(price_band_22_message) == price_band_22_message::size, "price_band_22_message lies over its bytes exactly");

// Quantity Band 21 Message: QuantityBand_21Message
struct quantity_band_21_message {
    static constexpr std::string_view name = "Quantity Band 21 Message";
    static constexpr std::size_t size = 40;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        security_id,
        match_event_indicator,
        offset_9_padding_3,
        avg_daily_traded_qty,
        max_trade_vol,
        md_entry_timestamp,
        rpt_seq>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYUMDFFIELD(security_id);
    BINARYUMDFFIELD(match_event_indicator);
    BINARYUMDFFIELD(offset_9_padding_3);
    BINARYUMDFFIELD(avg_daily_traded_qty);
    BINARYUMDFFIELD(max_trade_vol);
    BINARYUMDFFIELD(md_entry_timestamp);
    BINARYUMDFFIELD(rpt_seq);
};

static_assert(sizeof(quantity_band_21_message) == quantity_band_21_message::size, "quantity_band_21_message lies over its bytes exactly");

// Price Band 20 Message: PriceBand_20Message
struct price_band_20_message {
    static constexpr std::string_view name = "Price Band 20 Message";
    static constexpr std::size_t size = 48;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        security_id,
        match_event_indicator,
        price_band_type,
        price_limit_type,
        price_band_midpoint_price_type,
        low_limit_price,
        high_limit_price,
        trading_reference_price_legacy,
        md_entry_timestamp,
        rpt_seq>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYUMDFFIELD(security_id);
    BINARYUMDFFIELD(match_event_indicator);
    BINARYUMDFFIELD(price_band_type);
    BINARYUMDFFIELD(price_limit_type);
    BINARYUMDFFIELD(price_band_midpoint_price_type);
    BINARYUMDFFIELD(low_limit_price);
    BINARYUMDFFIELD(high_limit_price);
    BINARYUMDFFIELD(trading_reference_price_legacy);
    BINARYUMDFFIELD(md_entry_timestamp);
    BINARYUMDFFIELD(rpt_seq);
};

static_assert(sizeof(price_band_20_message) == price_band_20_message::size, "price_band_20_message lies over its bytes exactly");

// Imbalance Condition: ImbalanceCondition bit set
struct imbalance_condition {
    static constexpr std::string_view name = "Imbalance Condition";
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    // the bits of the type asked for
    template <typename Bit>
    constexpr typename Bit::type get() const noexcept { return static_cast<typename Bit::type>((value() & Bit::mask) >> Bit::shift); }

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }

  protected:
    type value_;
};

static_assert(sizeof(imbalance_condition) == imbalance_condition::size, "imbalance_condition lies over its bytes exactly");

// Auction Imbalance 19 Message: AuctionImbalance_19Message
struct auction_imbalance_19_message {
    static constexpr std::string_view name = "Auction Imbalance 19 Message";
    static constexpr std::size_t size = 32;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        security_id,
        match_event_indicator,
        md_update_action,
        imbalance_condition,
        md_entry_size_quantity_optional,
        md_entry_timestamp,
        rpt_seq>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYUMDFFIELD(security_id);
    BINARYUMDFFIELD(match_event_indicator);
    BINARYUMDFFIELD(md_update_action);
    BINARYUMDFFIELD(imbalance_condition);
    BINARYUMDFFIELD(md_entry_size_quantity_optional);
    BINARYUMDFFIELD(md_entry_timestamp);
    BINARYUMDFFIELD(rpt_seq);
};

static_assert(sizeof(auction_imbalance_19_message) == auction_imbalance_19_message::size, "auction_imbalance_19_message lies over its bytes exactly");

// Closing Price 17 Message: ClosingPrice_17Message
struct closing_price_17_message {
    static constexpr std::string_view name = "Closing Price 17 Message";
    static constexpr std::size_t size = 36;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        security_id,
        match_event_indicator,
        open_close_settl_flag,
        offset_10_padding_2,
        md_corporate_price,
        last_trade_date,
        trade_date,
        md_entry_timestamp,
        rpt_seq>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYUMDFFIELD(security_id);
    BINARYUMDFFIELD(match_event_indicator);
    BINARYUMDFFIELD(open_close_settl_flag);
    BINARYUMDFFIELD(offset_10_padding_2);
    BINARYUMDFFIELD(md_corporate_price);
    BINARYUMDFFIELD(last_trade_date);
    BINARYUMDFFIELD(trade_date);
    BINARYUMDFFIELD(md_entry_timestamp);
    BINARYUMDFFIELD(rpt_seq);
};

static_assert(sizeof(closing_price_17_message) == closing_price_17_message::size, "closing_price_17_message lies over its bytes exactly");

// Theoretical Opening Price 16 Message: TheoreticalOpeningPrice_16Message
struct theoretical_opening_price_16_message {
    static constexpr std::string_view name = "Theoretical Opening Price 16 Message";
    static constexpr std::size_t size = 40;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        security_id,
        match_event_indicator,
        md_update_action,
        trade_date,
        md_corporate_offset_price_optional,
        md_entry_size_quantity_optional,
        md_entry_timestamp,
        rpt_seq>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYUMDFFIELD(security_id);
    BINARYUMDFFIELD(match_event_indicator);
    BINARYUMDFFIELD(md_update_action);
    BINARYUMDFFIELD(trade_date);
    BINARYUMDFFIELD(md_corporate_offset_price_optional);
    BINARYUMDFFIELD(md_entry_size_quantity_optional);
    BINARYUMDFFIELD(md_entry_timestamp);
    BINARYUMDFFIELD(rpt_seq);
};

static_assert(sizeof(theoretical_opening_price_16_message) == theoretical_opening_price_16_message::size, "theoretical_opening_price_16_message lies over its bytes exactly");

// Opening Price 15 Message: OpeningPrice_15Message
struct opening_price_15_message {
    static constexpr std::string_view name = "Opening Price 15 Message";
    static constexpr std::size_t size = 44;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        security_id,
        match_event_indicator,
        md_update_action,
        open_close_settl_flag,
        offset_11_padding_1,
        md_future_price,
        net_chg_prev_day,
        trade_date,
        md_entry_timestamp,
        rpt_seq,
        padding_2>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYUMDFFIELD(security_id);
    BINARYUMDFFIELD(match_event_indicator);
    BINARYUMDFFIELD(md_update_action);
    BINARYUMDFFIELD(open_close_settl_flag);
    BINARYUMDFFIELD(offset_11_padding_1);
    BINARYUMDFFIELD(md_future_price);
    BINARYUMDFFIELD(net_chg_prev_day);
    BINARYUMDFFIELD(trade_date);
    BINARYUMDFFIELD(md_entry_timestamp);
    BINARYUMDFFIELD(rpt_seq);
    BINARYUMDFFIELD(padding_2);
};

static_assert(sizeof(opening_price_15_message) == opening_price_15_message::size, "opening_price_15_message lies over its bytes exactly");

// Url Link Section 1
struct url_link_section_1 {
    static constexpr std::string_view name = "Url Link Section 1";
    static constexpr std::size_t size = 2;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        url_link_length>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYUMDFFIELD(url_link_length);
};

static_assert(sizeof(url_link_section_1) == url_link_section_1::size, "url_link_section_1 lies over its bytes exactly");

// Url Link: uRLLink data struct
struct url_link {
    static constexpr std::string_view name = "Url Link";
    static constexpr bool is_message = false;
};

// Text Section 1
struct text_section_1 {
    static constexpr std::string_view name = "Text Section 1";
    static constexpr std::size_t size = 2;
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
    BINARYUMDFFIELD(text_length);
};

static_assert(sizeof(text_section_1) == text_section_1::size, "text_section_1 lies over its bytes exactly");

// Text: text data struct
struct text {
    static constexpr std::string_view name = "Text";
    static constexpr bool is_message = false;
};

// Headline Section 1
struct headline_section_1 {
    static constexpr std::string_view name = "Headline Section 1";
    static constexpr std::size_t size = 2;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        headline_length>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYUMDFFIELD(headline_length);
};

static_assert(sizeof(headline_section_1) == headline_section_1::size, "headline_section_1 lies over its bytes exactly");

// Headline: headline data struct
struct headline {
    static constexpr std::string_view name = "Headline";
    static constexpr bool is_message = false;
};

// News 5 Message Section 1
struct news_5_message_section_1 {
    static constexpr std::string_view name = "News 5 Message Section 1";
    static constexpr std::size_t size = 36;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        security_id_optional,
        match_event_indicator,
        news_source,
        language_code,
        part_count,
        part_number,
        news_id,
        orig_time,
        total_text_length>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYUMDFFIELD(security_id_optional);
    BINARYUMDFFIELD(match_event_indicator);
    BINARYUMDFFIELD(news_source);
    BINARYUMDFFIELD(language_code);
    BINARYUMDFFIELD(part_count);
    BINARYUMDFFIELD(part_number);
    BINARYUMDFFIELD(news_id);
    BINARYUMDFFIELD(orig_time);
    BINARYUMDFFIELD(total_text_length);
};

static_assert(sizeof(news_5_message_section_1) == news_5_message_section_1::size, "news_5_message_section_1 lies over its bytes exactly");

// News 5 Message: News_5Message
struct news_5_message {
    static constexpr std::string_view name = "News 5 Message";
    static constexpr bool is_message = true;
};

// Security Desc Section 1
struct security_desc_section_1 {
    static constexpr std::string_view name = "Security Desc Section 1";
    static constexpr std::size_t size = 1;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        security_desc_length>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYUMDFFIELD(security_desc_length);
};

static_assert(sizeof(security_desc_section_1) == security_desc_section_1::size, "security_desc_section_1 lies over its bytes exactly");

// Security Desc: securityDesc data struct
struct security_desc {
    static constexpr std::string_view name = "Security Desc";
    static constexpr bool is_message = false;
};

// Instr Attribs Group: noInstrAttribs
struct instr_attribs_group {
    static constexpr std::string_view name = "Instr Attribs Group";
    static constexpr std::size_t size = 2;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        instr_attrib_type,
        instr_attrib_value>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYUMDFFIELD(instr_attrib_type);
    BINARYUMDFFIELD(instr_attrib_value);
};

static_assert(sizeof(instr_attribs_group) == instr_attribs_group::size, "instr_attribs_group lies over its bytes exactly");

// Instr Attribs Groups: noInstrAttribs Block
struct instr_attribs_groups {
    static constexpr std::string_view name = "Instr Attribs Groups";
    static constexpr bool is_message = false;

    // its repeating groups, whose entries the parse hands over one at a time
    BINARYUMDFSEQUENCE(instr_attribs_group);
};

// Legs Group: noLegs
struct legs_group {
    static constexpr std::string_view name = "Legs Group";
    static constexpr std::size_t size = 38;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        leg_security_id,
        leg_ratio_qty,
        leg_security_type,
        leg_side,
        leg_symbol>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYUMDFFIELD(leg_security_id);
    BINARYUMDFFIELD(leg_ratio_qty);
    BINARYUMDFFIELD(leg_security_type);
    BINARYUMDFFIELD(leg_side);
    BINARYUMDFFIELD(leg_symbol);
};

static_assert(sizeof(legs_group) == legs_group::size, "legs_group lies over its bytes exactly");

// Legs Groups: noLegs Block
struct legs_groups {
    static constexpr std::string_view name = "Legs Groups";
    static constexpr bool is_message = false;

    // its repeating groups, whose entries the parse hands over one at a time
    BINARYUMDFSEQUENCE(legs_group);
};

// Underlyings Group: noUnderlyings
struct underlyings_group {
    static constexpr std::string_view name = "Underlyings Group";
    static constexpr std::size_t size = 28;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        underlying_security_id,
        underlying_symbol>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYUMDFFIELD(underlying_security_id);
    BINARYUMDFFIELD(underlying_symbol);
};

static_assert(sizeof(underlyings_group) == underlyings_group::size, "underlyings_group lies over its bytes exactly");

// Underlyings Groups: noUnderlyings Block
struct underlyings_groups {
    static constexpr std::string_view name = "Underlyings Groups";
    static constexpr bool is_message = false;

    // its repeating groups, whose entries the parse hands over one at a time
    BINARYUMDFSEQUENCE(underlyings_group);
};

// Contract Settl Month: SecurityDefinition_4Message
struct contract_settl_month {
    static constexpr std::string_view name = "Contract Settl Month";
    static constexpr std::size_t size = 5;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        year,
        month,
        day,
        week>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYUMDFFIELD(year);
    BINARYUMDFFIELD(month);
    BINARYUMDFFIELD(day);
    BINARYUMDFFIELD(week);
};

static_assert(sizeof(contract_settl_month) == contract_settl_month::size, "contract_settl_month lies over its bytes exactly");

// Maturity Month Year: SecurityDefinition_4Message
struct maturity_month_year {
    static constexpr std::string_view name = "Maturity Month Year";
    static constexpr std::size_t size = 5;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        year,
        month,
        day,
        week>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYUMDFFIELD(year);
    BINARYUMDFFIELD(month);
    BINARYUMDFFIELD(day);
    BINARYUMDFFIELD(week);
};

static_assert(sizeof(maturity_month_year) == maturity_month_year::size, "maturity_month_year lies over its bytes exactly");

// Security Definition Message Section 1
struct security_definition_message_section_1 {
    static constexpr std::string_view name = "Security Definition Message Section 1";
    static constexpr std::size_t size = 230;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        security_id,
        security_exchange,
        security_id_source,
        security_group,
        symbol,
        security_update_action,
        security_type,
        security_sub_type,
        tot_no_related_sym,
        min_price_increment_optional,
        strike_price,
        contract_multiplier,
        price_divisor,
        security_validity_timestamp,
        no_shares_issued,
        clearing_house_id,
        min_order_qty,
        max_order_qty,
        min_lot_size,
        min_trade_vol,
        corporate_action_event_id,
        issue_date,
        maturity_date,
        country_of_issue,
        start_date,
        end_date,
        settl_type,
        settl_date,
        dated_date,
        isin_number,
        asset,
        cfi_code,
        maturity_month_year,
        contract_settl_month,
        currency,
        strike_currency,
        settl_currency,
        security_strategy_type,
        lot_type,
        tick_size_denominator,
        product,
        exercise_style,
        put_or_call,
        price_type,
        market_segment_id,
        governance_indicator,
        security_match_type,
        last_fragment,
        multi_leg_model,
        multi_leg_price_method,
        min_cross_qty>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYUMDFFIELD(security_id);
    BINARYUMDFFIELD(security_exchange);
    BINARYUMDFFIELD(security_id_source);
    BINARYUMDFFIELD(security_group);
    BINARYUMDFFIELD(symbol);
    BINARYUMDFFIELD(security_update_action);
    BINARYUMDFFIELD(security_type);
    BINARYUMDFFIELD(security_sub_type);
    BINARYUMDFFIELD(tot_no_related_sym);
    BINARYUMDFFIELD(min_price_increment_optional);
    BINARYUMDFFIELD(strike_price);
    BINARYUMDFFIELD(contract_multiplier);
    BINARYUMDFFIELD(price_divisor);
    BINARYUMDFFIELD(security_validity_timestamp);
    BINARYUMDFFIELD(no_shares_issued);
    BINARYUMDFFIELD(clearing_house_id);
    BINARYUMDFFIELD(min_order_qty);
    BINARYUMDFFIELD(max_order_qty);
    BINARYUMDFFIELD(min_lot_size);
    BINARYUMDFFIELD(min_trade_vol);
    BINARYUMDFFIELD(corporate_action_event_id);
    BINARYUMDFFIELD(issue_date);
    BINARYUMDFFIELD(maturity_date);
    BINARYUMDFFIELD(country_of_issue);
    BINARYUMDFFIELD(start_date);
    BINARYUMDFFIELD(end_date);
    BINARYUMDFFIELD(settl_type);
    BINARYUMDFFIELD(settl_date);
    BINARYUMDFFIELD(dated_date);
    BINARYUMDFFIELD(isin_number);
    BINARYUMDFFIELD(asset);
    BINARYUMDFFIELD(cfi_code);
    BINARYUMDFFIELD(maturity_month_year);
    BINARYUMDFFIELD(contract_settl_month);
    BINARYUMDFFIELD(currency);
    BINARYUMDFFIELD(strike_currency);
    BINARYUMDFFIELD(settl_currency);
    BINARYUMDFFIELD(security_strategy_type);
    BINARYUMDFFIELD(lot_type);
    BINARYUMDFFIELD(tick_size_denominator);
    BINARYUMDFFIELD(product);
    BINARYUMDFFIELD(exercise_style);
    BINARYUMDFFIELD(put_or_call);
    BINARYUMDFFIELD(price_type);
    BINARYUMDFFIELD(market_segment_id);
    BINARYUMDFFIELD(governance_indicator);
    BINARYUMDFFIELD(security_match_type);
    BINARYUMDFFIELD(last_fragment);
    BINARYUMDFFIELD(multi_leg_model);
    BINARYUMDFFIELD(multi_leg_price_method);
    BINARYUMDFFIELD(min_cross_qty);
};

static_assert(sizeof(security_definition_message_section_1) == security_definition_message_section_1::size, "security_definition_message_section_1 lies over its bytes exactly");

// Security Definition Message: SecurityDefinition_12Message
struct security_definition_message {
    static constexpr std::string_view name = "Security Definition Message";
    static constexpr bool is_message = true;
};

// Deprecated Instr Attribs Group: noInstrAttribs
struct deprecated_instr_attribs_group {
    static constexpr std::string_view name = "Deprecated Instr Attribs Group";
    static constexpr std::size_t size = 2;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        instr_attrib_type,
        instr_attrib_value>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYUMDFFIELD(instr_attrib_type);
    BINARYUMDFFIELD(instr_attrib_value);
};

static_assert(sizeof(deprecated_instr_attribs_group) == deprecated_instr_attribs_group::size, "deprecated_instr_attribs_group lies over its bytes exactly");

// Deprecated Instr Attribs Groups: noInstrAttribs Block
struct deprecated_instr_attribs_groups {
    static constexpr std::string_view name = "Deprecated Instr Attribs Groups";
    static constexpr bool is_message = false;

    // its repeating groups, whose entries the parse hands over one at a time
    BINARYUMDFSEQUENCE(deprecated_instr_attribs_group);
};

// Deprecated Legs Group: noLegs
struct deprecated_legs_group {
    static constexpr std::string_view name = "Deprecated Legs Group";
    static constexpr std::size_t size = 38;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        leg_security_id,
        leg_ratio_qty,
        leg_security_type,
        leg_side,
        leg_symbol>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYUMDFFIELD(leg_security_id);
    BINARYUMDFFIELD(leg_ratio_qty);
    BINARYUMDFFIELD(leg_security_type);
    BINARYUMDFFIELD(leg_side);
    BINARYUMDFFIELD(leg_symbol);
};

static_assert(sizeof(deprecated_legs_group) == deprecated_legs_group::size, "deprecated_legs_group lies over its bytes exactly");

// Deprecated Legs Groups: noLegs Block
struct deprecated_legs_groups {
    static constexpr std::string_view name = "Deprecated Legs Groups";
    static constexpr bool is_message = false;

    // its repeating groups, whose entries the parse hands over one at a time
    BINARYUMDFSEQUENCE(deprecated_legs_group);
};

// Deprecated Underlyings Group: noUnderlyings
struct deprecated_underlyings_group {
    static constexpr std::string_view name = "Deprecated Underlyings Group";
    static constexpr std::size_t size = 44;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        underlying_security_id,
        index_pct,
        index_theoretical_qty,
        underlying_symbol>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYUMDFFIELD(underlying_security_id);
    BINARYUMDFFIELD(index_pct);
    BINARYUMDFFIELD(index_theoretical_qty);
    BINARYUMDFFIELD(underlying_symbol);
};

static_assert(sizeof(deprecated_underlyings_group) == deprecated_underlyings_group::size, "deprecated_underlyings_group lies over its bytes exactly");

// Deprecated Underlyings Groups: noUnderlyings Block
struct deprecated_underlyings_groups {
    static constexpr std::string_view name = "Deprecated Underlyings Groups";
    static constexpr bool is_message = false;

    // its repeating groups, whose entries the parse hands over one at a time
    BINARYUMDFSEQUENCE(deprecated_underlyings_group);
};

// Deprecated Security Definition Message Section 1
struct deprecated_security_definition_message_section_1 {
    static constexpr std::string_view name = "Deprecated Security Definition Message Section 1";
    static constexpr std::size_t size = 230;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        security_id,
        security_exchange,
        security_id_source,
        security_group,
        symbol,
        security_update_action,
        security_type,
        security_sub_type,
        tot_no_related_sym,
        min_price_increment_legacy,
        strike_price,
        contract_multiplier,
        price_divisor,
        security_validity_timestamp,
        no_shares_issued,
        clearing_house_id,
        min_order_qty,
        max_order_qty,
        min_lot_size,
        min_trade_vol,
        corporate_action_event_id,
        issue_date,
        maturity_date,
        country_of_issue,
        start_date,
        end_date,
        settl_type,
        settl_date,
        dated_date,
        isin_number,
        asset,
        cfi_code,
        maturity_month_year,
        contract_settl_month,
        currency,
        strike_currency,
        settl_currency,
        security_strategy_type,
        lot_type,
        tick_size_denominator,
        product,
        exercise_style,
        put_or_call,
        price_type,
        market_segment_id,
        governance_indicator,
        security_match_type,
        last_fragment,
        multi_leg_model,
        multi_leg_price_method,
        min_cross_qty>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYUMDFFIELD(security_id);
    BINARYUMDFFIELD(security_exchange);
    BINARYUMDFFIELD(security_id_source);
    BINARYUMDFFIELD(security_group);
    BINARYUMDFFIELD(symbol);
    BINARYUMDFFIELD(security_update_action);
    BINARYUMDFFIELD(security_type);
    BINARYUMDFFIELD(security_sub_type);
    BINARYUMDFFIELD(tot_no_related_sym);
    BINARYUMDFFIELD(min_price_increment_legacy);
    BINARYUMDFFIELD(strike_price);
    BINARYUMDFFIELD(contract_multiplier);
    BINARYUMDFFIELD(price_divisor);
    BINARYUMDFFIELD(security_validity_timestamp);
    BINARYUMDFFIELD(no_shares_issued);
    BINARYUMDFFIELD(clearing_house_id);
    BINARYUMDFFIELD(min_order_qty);
    BINARYUMDFFIELD(max_order_qty);
    BINARYUMDFFIELD(min_lot_size);
    BINARYUMDFFIELD(min_trade_vol);
    BINARYUMDFFIELD(corporate_action_event_id);
    BINARYUMDFFIELD(issue_date);
    BINARYUMDFFIELD(maturity_date);
    BINARYUMDFFIELD(country_of_issue);
    BINARYUMDFFIELD(start_date);
    BINARYUMDFFIELD(end_date);
    BINARYUMDFFIELD(settl_type);
    BINARYUMDFFIELD(settl_date);
    BINARYUMDFFIELD(dated_date);
    BINARYUMDFFIELD(isin_number);
    BINARYUMDFFIELD(asset);
    BINARYUMDFFIELD(cfi_code);
    BINARYUMDFFIELD(maturity_month_year);
    BINARYUMDFFIELD(contract_settl_month);
    BINARYUMDFFIELD(currency);
    BINARYUMDFFIELD(strike_currency);
    BINARYUMDFFIELD(settl_currency);
    BINARYUMDFFIELD(security_strategy_type);
    BINARYUMDFFIELD(lot_type);
    BINARYUMDFFIELD(tick_size_denominator);
    BINARYUMDFFIELD(product);
    BINARYUMDFFIELD(exercise_style);
    BINARYUMDFFIELD(put_or_call);
    BINARYUMDFFIELD(price_type);
    BINARYUMDFFIELD(market_segment_id);
    BINARYUMDFFIELD(governance_indicator);
    BINARYUMDFFIELD(security_match_type);
    BINARYUMDFFIELD(last_fragment);
    BINARYUMDFFIELD(multi_leg_model);
    BINARYUMDFFIELD(multi_leg_price_method);
    BINARYUMDFFIELD(min_cross_qty);
};

static_assert(sizeof(deprecated_security_definition_message_section_1) == deprecated_security_definition_message_section_1::size, "deprecated_security_definition_message_section_1 lies over its bytes exactly");

// Deprecated Security Definition Message: SecurityDefinition_4Message
struct deprecated_security_definition_message {
    static constexpr std::string_view name = "Deprecated Security Definition Message";
    static constexpr bool is_message = true;
};

// Security Group Phase 10 Message: SecurityGroupPhase_10Message
struct security_group_phase_10_message {
    static constexpr std::string_view name = "Security Group Phase 10 Message";
    static constexpr std::size_t size = 32;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        security_group,
        offset_3_padding_5,
        match_event_indicator,
        trading_session_id,
        trading_session_sub_id,
        security_trading_event,
        trade_date,
        offset_14_padding_2,
        trad_ses_open_time,
        transact_time>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYUMDFFIELD(security_group);
    BINARYUMDFFIELD(offset_3_padding_5);
    BINARYUMDFFIELD(match_event_indicator);
    BINARYUMDFFIELD(trading_session_id);
    BINARYUMDFFIELD(trading_session_sub_id);
    BINARYUMDFFIELD(security_trading_event);
    BINARYUMDFFIELD(trade_date);
    BINARYUMDFFIELD(offset_14_padding_2);
    BINARYUMDFFIELD(trad_ses_open_time);
    BINARYUMDFFIELD(transact_time);
};

static_assert(sizeof(security_group_phase_10_message) == security_group_phase_10_message::size, "security_group_phase_10_message lies over its bytes exactly");

// Security Status 3 Message: SecurityStatus_3Message
struct security_status_3_message {
    static constexpr std::string_view name = "Security Status 3 Message";
    static constexpr std::size_t size = 36;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        security_id,
        match_event_indicator,
        trading_session_id,
        security_trading_status,
        security_trading_event,
        trade_date,
        offset_14_padding_2,
        trad_ses_open_time,
        transact_time,
        rpt_seq>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYUMDFFIELD(security_id);
    BINARYUMDFFIELD(match_event_indicator);
    BINARYUMDFFIELD(trading_session_id);
    BINARYUMDFFIELD(security_trading_status);
    BINARYUMDFFIELD(security_trading_event);
    BINARYUMDFFIELD(trade_date);
    BINARYUMDFFIELD(offset_14_padding_2);
    BINARYUMDFFIELD(trad_ses_open_time);
    BINARYUMDFFIELD(transact_time);
    BINARYUMDFFIELD(rpt_seq);
};

static_assert(sizeof(security_status_3_message) == security_status_3_message::size, "security_status_3_message lies over its bytes exactly");

// Channel Reset 11 Message: ChannelReset_11Message
struct channel_reset_11_message {
    static constexpr std::string_view name = "Channel Reset 11 Message";
    static constexpr std::size_t size = 12;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        match_event_indicator,
        offset_1_padding_3,
        md_entry_timestamp>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYUMDFFIELD(match_event_indicator);
    BINARYUMDFFIELD(offset_1_padding_3);
    BINARYUMDFFIELD(md_entry_timestamp);
};

static_assert(sizeof(channel_reset_11_message) == channel_reset_11_message::size, "channel_reset_11_message lies over its bytes exactly");

// Empty Book Message: EmptyBook_9Message
struct empty_book_message {
    static constexpr std::string_view name = "Empty Book Message";
    static constexpr std::size_t size = 20;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        security_id,
        match_event_indicator,
        offset_9_padding_3,
        md_entry_timestamp>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYUMDFFIELD(security_id);
    BINARYUMDFFIELD(match_event_indicator);
    BINARYUMDFFIELD(offset_9_padding_3);
    BINARYUMDFFIELD(md_entry_timestamp);
};

static_assert(sizeof(empty_book_message) == empty_book_message::size, "empty_book_message lies over its bytes exactly");

// Sequence Message: Sequence_2Message
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
    BINARYUMDFFIELD(next_seq_no);
};

static_assert(sizeof(sequence_message) == sequence_message::size, "sequence_message lies over its bytes exactly");

// Sequence Reset Message
struct sequence_reset_message {
    static constexpr std::string_view name = "Sequence Reset Message";
    static constexpr std::size_t size = 0;
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
    BINARYUMDFFIELD(block_length);
    BINARYUMDFFIELD(template_id);
    BINARYUMDFFIELD(schema_id);
    BINARYUMDFFIELD(version);
};

static_assert(sizeof(message_header) == message_header::size, "message_header lies over its bytes exactly");

// Framing Header: B3 Sbe framing header
struct framing_header {
    static constexpr std::string_view name = "Framing Header";
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
    BINARYUMDFFIELD(message_length);
    BINARYUMDFFIELD(encoding_type);
};

static_assert(sizeof(framing_header) == framing_header::size, "framing_header lies over its bytes exactly");

// Message Section 1
struct message_section_1 {
    static constexpr std::string_view name = "Message Section 1";
    static constexpr std::size_t size = 12;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        framing_header,
        message_header>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYUMDFFIELD(framing_header);
    BINARYUMDFFIELD(message_header);
};

static_assert(sizeof(message_section_1) == message_section_1::size, "message_section_1 lies over its bytes exactly");

// Message: B3 Market Data Message
struct message {
    static constexpr std::string_view name = "Message";
    static constexpr bool is_message = false;
};

// Packet Header: B3 Mdp Packet Header
struct packet_header {
    static constexpr std::string_view name = "Packet Header";
    static constexpr std::size_t size = 16;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        channel_id,
        packet_reserved,
        sequence_version,
        sequence_number,
        sending_time>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    BINARYUMDFFIELD(channel_id);
    BINARYUMDFFIELD(packet_reserved);
    BINARYUMDFFIELD(sequence_version);
    BINARYUMDFFIELD(sequence_number);
    BINARYUMDFFIELD(sending_time);
};

static_assert(sizeof(packet_header) == packet_header::size, "packet_header lies over its bytes exactly");

// Packet: B3 Binary Umdf Packet
struct packet {
    static constexpr std::string_view name = "Packet";
    static constexpr bool is_message = false;
};

#pragma pack(pop)

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_7
