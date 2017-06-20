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
#include <evolution/chain/delegate_evaluator.hpp>
#include <evolution/chain/delegate_object.hpp>
#include <evolution/chain/committee_member_object.hpp>
#include <evolution/chain/account_object.hpp>
#include <evolution/chain/database.hpp>
#include <evolution/chain/protocol/vote.hpp>

namespace evolution { namespace chain {

void_result delegate_create_evaluator::do_evaluate( const delegate_create_operation& op )
{ try {
   FC_ASSERT(db().get(op.delegate_account).is_lifetime_member());
   return void_result();
} FC_CAPTURE_AND_RETHROW( (op) ) }

object_id_type delegate_create_evaluator::do_apply( const delegate_create_operation& op )
{ try {
   vote_id_type vote_id;
   db().modify(db().get_global_properties(), [&vote_id](global_property_object& p) {
      vote_id = get_next_vote_id(p, vote_id_type::delegate);
   });

   const auto& new_delegate_object = db().create<delegate_object>( [&]( delegate_object& obj ){
         obj.delegate_account  = op.delegate_account;
         obj.signing_key      = op.block_signing_key;
         obj.vote_id          = vote_id;
         obj.url              = op.url;
   });
   return new_delegate_object.id;
} FC_CAPTURE_AND_RETHROW( (op) ) }

void_result delegate_update_evaluator::do_evaluate( const delegate_update_operation& op )
{ try {
   FC_ASSERT(db().get(op.delegate).delegate_account == op.delegate_account);
   return void_result();
} FC_CAPTURE_AND_RETHROW( (op) ) }

void_result delegate_update_evaluator::do_apply( const delegate_update_operation& op )
{ try {
   database& _db = db();
   _db.modify(
      _db.get(op.delegate),
      [&]( delegate_object& wit )
      {
         if( op.new_url.valid() )
            wit.url = *op.new_url;
         if( op.new_signing_key.valid() )
            wit.signing_key = *op.new_signing_key;
      });
   return void_result();
} FC_CAPTURE_AND_RETHROW( (op) ) }

} } // evolution::chain
