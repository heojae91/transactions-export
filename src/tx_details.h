//
// Created by mwo on 14/11/15.
//

#ifndef XMR2CSV_TXDATA_H
#define XMR2CSV_TXDATA_H



#include "../ext/minicsv.h"

#include "monero_headers.h"
#include "tools.h"

#include <iomanip>
#include <sstream>

namespace xmreg
{

    using namespace cryptonote;
    using namespace crypto;
    using namespace std;


    struct transfer_details
    {
        account_public_address m_addr;
        uint64_t m_block_height;
        uint64_t m_block_timestamp;
        uint64_t m_amount;
        transaction m_tx;
        crypto::hash payment_id;
        size_t m_internal_output_index;
        public_key out_pub_key;
        key_image key_img;
        bool m_spent;

        crypto::hash tx_hash() const;

        public_key tx_pub_key() const;

        uint64_t amount() const;

        uint64_t amount(secret_key prv_view_key) const;
    };

    struct tx_data
    {
      int block_index;
      string transaction_id;
      string output_pubkey;
    };
    // 필요한 내용 : i (블록높이), tx_hash(트랜잭션해쉬), output_data(사용된 공개키(pubkey), 높이(height)), abs_offset(처음나온곳),

    struct input_data
    {
      uint64_t first_block; // 처음 발견된 브록
      uint64_t tx_idx; // 우리가 발견한 tx_hash가 속해있는 높이

      string tx_hash; // 거래가포함된 tx_hash
      string pubkey; // 거래의 pubkey

      int freq = 0;
    };

    ostream&
    operator<<(ostream& os, const transfer_details& dt);


    vector<xmreg::transfer_details>
    get_belonging_outputs(const block& blk,
                          const transaction& tx,
                          const account_public_address& addr,
                          const secret_key& private_view_key,
                          uint64_t block_height = 0);


    vector<xmreg::transfer_details>
    get_outputs(const block& blk,
                const transaction& tx,
                uint64_t block_height = 0);

    bool
    get_payment_id(const transaction& tx,
                   const account_public_address& addr,
                   crypto::hash& payment_id);

    bool
    get_payment_id(const transaction& tx,
                   crypto::hash& payment_id);

    vector<xmreg::tx_data>
    get_transaction_inputs(const transaction& tx,
                            input_data& id,
                            // const vector<crypto::key_image>& key_images_gen,
                            uint64_t block_height = 0);

    void print_all_tx_data(input_data& txd);
}

template<>
csv::ostringstream&
operator<<(csv::ostringstream& ostm, const xmreg::transfer_details& td);


#endif //XMR2CSV_TXDATA_H
