#pragma once

#include <gstio/action.h>
#include <gstio/chain.h>
#include <gstio/crypto.h>
#include <gstio/db.h>
#include <gstio/permission.h>
#include <gstio/print.h>
#include <gstio/privileged.h>
#include <gstio/system.h>
#include <gstio/transaction.h>
#include <gstio/types.h>

#include <type_traits>

namespace gstio { namespace native {
   template <typename... Args, size_t... Is>
   auto get_args_full(std::index_sequence<Is...>) {
       std::tuple<std::decay_t<Args>...> tup;
       return std::tuple<Args...>{std::get<Is>(tup)...};
   }

   template <typename R, typename... Args>
   auto get_args_full(R(Args...)) {
       return get_args_full<Args...>(std::index_sequence_for<Args...>{});
   }

   template <typename R, typename... Args>
   auto get_args(R(Args...)) {
       return std::tuple<std::decay_t<Args>...>{};
   }
   
   template <typename R, typename Args, size_t... Is>
   auto create_function(std::index_sequence<Is...>) {
      return std::function<R(typename std::tuple_element<Is, Args>::type ...)>{ 
         [](typename std::tuple_element<Is, Args>::type ...) { 
            gstio_assert(false, "unsupported intrinsic"); return (R)0;
         }
      };
   }   

#define INTRINSICS(intrinsic_macro) \
intrinsic_macro(get_resource_limits) \
intrinsic_macro(set_resource_limits) \
intrinsic_macro(set_resource_limits2) \
intrinsic_macro(set_gas_limits) \
intrinsic_macro(set_proposed_producers) \
intrinsic_macro(get_blockchain_parameters_packed) \
intrinsic_macro(set_blockchain_parameters_packed) \
intrinsic_macro(is_privileged) \
intrinsic_macro(set_privileged) \
intrinsic_macro(get_active_producers) \
intrinsic_macro(db_idx64_store) \
intrinsic_macro(db_idx64_remove) \
intrinsic_macro(db_idx64_update) \
intrinsic_macro(db_idx64_find_primary) \
intrinsic_macro(db_idx64_find_secondary) \
intrinsic_macro(db_idx64_lowerbound) \
intrinsic_macro(db_idx64_upperbound) \
intrinsic_macro(db_idx64_end) \
intrinsic_macro(db_idx64_next) \
intrinsic_macro(db_idx64_previous) \
intrinsic_macro(db_idx128_store) \
intrinsic_macro(db_idx128_remove) \
intrinsic_macro(db_idx128_update) \
intrinsic_macro(db_idx128_find_primary) \
intrinsic_macro(db_idx128_find_secondary) \
intrinsic_macro(db_idx128_lowerbound) \
intrinsic_macro(db_idx128_upperbound) \
intrinsic_macro(db_idx128_end) \
intrinsic_macro(db_idx128_next) \
intrinsic_macro(db_idx128_previous) \
intrinsic_macro(db_idx256_store) \
intrinsic_macro(db_idx256_remove) \
intrinsic_macro(db_idx256_update) \
intrinsic_macro(db_idx256_find_primary) \
intrinsic_macro(db_idx256_find_secondary) \
intrinsic_macro(db_idx256_lowerbound) \
intrinsic_macro(db_idx256_upperbound) \
intrinsic_macro(db_idx256_end) \
intrinsic_macro(db_idx256_next) \
intrinsic_macro(db_idx256_previous) \
intrinsic_macro(db_idx_double_store) \
intrinsic_macro(db_idx_double_remove) \
intrinsic_macro(db_idx_double_update) \
intrinsic_macro(db_idx_double_find_primary) \
intrinsic_macro(db_idx_double_find_secondary) \
intrinsic_macro(db_idx_double_lowerbound) \
intrinsic_macro(db_idx_double_upperbound) \
intrinsic_macro(db_idx_double_end) \
intrinsic_macro(db_idx_double_next) \
intrinsic_macro(db_idx_double_previous) \
intrinsic_macro(db_idx_long_double_store) \
intrinsic_macro(db_idx_long_double_remove) \
intrinsic_macro(db_idx_long_double_update) \
intrinsic_macro(db_idx_long_double_find_primary) \
intrinsic_macro(db_idx_long_double_find_secondary) \
intrinsic_macro(db_idx_long_double_lowerbound) \
intrinsic_macro(db_idx_long_double_upperbound) \
intrinsic_macro(db_idx_long_double_end) \
intrinsic_macro(db_idx_long_double_next) \
intrinsic_macro(db_idx_long_double_previous) \
intrinsic_macro(db_store_i64) \
intrinsic_macro(db_update_i64) \
intrinsic_macro(db_remove_i64) \
intrinsic_macro(db_get_i64) \
intrinsic_macro(db_next_i64) \
intrinsic_macro(db_previous_i64) \
intrinsic_macro(db_find_i64) \
intrinsic_macro(db_lowerbound_i64) \
intrinsic_macro(db_upperbound_i64) \
intrinsic_macro(db_end_i64) \
intrinsic_macro(assert_recover_key) \
intrinsic_macro(recover_key) \
intrinsic_macro(assert_sha256) \
intrinsic_macro(assert_sha1) \
intrinsic_macro(assert_sha512) \
intrinsic_macro(assert_ripemd160) \
intrinsic_macro(sha1) \
intrinsic_macro(sha256) \
intrinsic_macro(sha512) \
intrinsic_macro(ripemd160) \
intrinsic_macro(check_transaction_authorization) \
intrinsic_macro(check_permission_authorization) \
intrinsic_macro(get_permission_last_used) \
intrinsic_macro(get_account_creation_time) \
intrinsic_macro(current_time) \
intrinsic_macro(publication_time) \
intrinsic_macro(read_action_data) \
intrinsic_macro(action_data_size) \
intrinsic_macro(current_receiver) \
intrinsic_macro(require_recipient) \
intrinsic_macro(require_auth) \
intrinsic_macro(require_auth2) \
intrinsic_macro(has_auth) \
intrinsic_macro(is_account) \
intrinsic_macro(prints) \
intrinsic_macro(prints_l) \
intrinsic_macro(printi) \
intrinsic_macro(printui) \
intrinsic_macro(printi128) \
intrinsic_macro(printui128) \
intrinsic_macro(printsf) \
intrinsic_macro(printdf) \
intrinsic_macro(printqf) \
intrinsic_macro(printn) \
intrinsic_macro(printhex) \
intrinsic_macro(read_transaction) \
intrinsic_macro(transaction_size) \
intrinsic_macro(expiration) \
intrinsic_macro(tapos_block_prefix) \
intrinsic_macro(tapos_block_num) \
intrinsic_macro(get_action) \
intrinsic_macro(send_inline) \
intrinsic_macro(send_context_free_inline) \
intrinsic_macro(send_deferred) \
intrinsic_macro(cancel_deferred) \
intrinsic_macro(get_context_free_data) 

#define CREATE_ENUM(name) \
   name,

#define GENERATE_TYPE_MAPPING(name) \
   struct __ ## name ## _types { \
      using deduced_full_ts = decltype(gstio::native::get_args_full(::name)); \
      using deduced_ts      = decltype(gstio::native::get_args(::name)); \
      using res_t           = decltype(std::apply(::name, deduced_ts{})); \
      static constexpr auto is = std::make_index_sequence<std::tuple_size<deduced_ts>::value>(); \
   };

#define GET_TYPE(name) \
   decltype(create_function<gstio::native::intrinsics::__ ## name ## _types::res_t, \
         gstio::native::intrinsics::__ ## name ## _types::deduced_full_ts>(gstio::native::intrinsics::__ ## name ## _types::is)),

#define REGISTER_INTRINSIC(name) \
   create_function<gstio::native::intrinsics::__ ## name ## _types::res_t, \
         gstio::native::intrinsics::__ ## name ## _types::deduced_full_ts>(gstio::native::intrinsics::__ ## name ## _types::is),

}} //ns gstio::native
