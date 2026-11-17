// Databento.MarketData.Normalized.Dbn.v2: pcap/Result.hpp
#pragma once

namespace packet {

    enum class result {
        databento_marketdata_normalized_dbn_v2,
        error,
        end_of_file,
        unknown
    };

}