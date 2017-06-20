/*
 * Copyright (c) 2015 Cryptonomex, Inc., and contributors.
 *
 * The MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#pragma once
#include <evolution/chain/protocol/base.hpp>

namespace evolution { namespace chain { 

  /**
    * @brief Create a delegate object, as a bid to hold a delegate position on the network.
    * @ingroup operations
    *
    * Accounts which wish to become delegates may use this operation to create a delegate object which stakeholders may
    * vote on to approve its position as a delegate.
    */
   struct delegate_create_operation : public base_operation
   {
      struct fee_parameters_type { uint64_t fee = 5000 * EVOLUTION_BLOCKCHAIN_PRECISION; };

      asset             fee;
      /// The account which owns the delegate. This account pays the fee for this operation.
      account_id_type   delegate_account;
      string            url;
      public_key_type   block_signing_key;

      account_id_type fee_payer()const { return delegate_account; }
      void            validate()const;
   };

  /**
    * @brief Update a delegate object's URL and block signing key.
    * @ingroup operations
    */
   struct delegate_update_operation : public base_operation
   {
      struct fee_parameters_type
      {
         share_type fee = 20 * EVOLUTION_BLOCKCHAIN_PRECISION;
      };

      asset             fee;
      /// The delegate object to update.
      delegate_id_type   delegate;
      /// The account which owns the delegate. This account pays the fee for this operation.
      account_id_type   delegate_account;
      /// The new URL.
      optional< string > new_url;
      /// The new block signing key.
      optional< public_key_type > new_signing_key;

      account_id_type fee_payer()const { return delegate_account; }
      void            validate()const;
   };

   /// TODO: delegate_resign_operation : public base_operation

} } // evolution::chain

FC_REFLECT( evolution::chain::delegate_create_operation::fee_parameters_type, (fee) )
FC_REFLECT( evolution::chain::delegate_create_operation, (fee)(delegate_account)(url)(block_signing_key) )

FC_REFLECT( evolution::chain::delegate_update_operation::fee_parameters_type, (fee) )
FC_REFLECT( evolution::chain::delegate_update_operation, (fee)(delegate)(delegate_account)(new_url)(new_signing_key) )
