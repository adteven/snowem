/*
 * (C) Copyright 2017 Jackie Dinh <jackiedinh8@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include <assert.h>

#include "core/mempool.h"
#include "ice_component.h"

void
snw_component_mempool_init(snw_ice_context_t *ctx) {

   if (!ctx) return;

   ctx->component_mempool = snw_mempool_create(
         sizeof(snw_ice_component_t),sizeof(snw_ice_component_t)*1024,1);
   assert(ctx->component_mempool!=NULL);

   return;
}

snw_ice_component_t* 
snw_component_allocate(snw_ice_context_t *ctx) {
   snw_ice_component_t* component;

   if (!ctx->component_mempool)
      return 0;
   
   component = (snw_ice_component_t*) snw_mempool_allocate(ctx->component_mempool); 
   if (!component)
      return NULL;
   memset(component,0,sizeof(*component));
	 TAILQ_INIT(&component->remote_candidates);

   return component;
}

void 
snw_component_deallocate(snw_ice_context_t *ctx, snw_ice_component_t* p) {

   if (!ctx->component_mempool)
      return;

   snw_mempool_free(ctx->component_mempool, p);

   return;
}

snw_ice_component_t* 
snw_component_find(ice_component_head_t *head, uint32_t id) {
   snw_ice_component_t *s = 0;

   if ( head == NULL )
      return NULL;
   
   LIST_FOREACH(s,head,list) {
      if (s->id == id)
         return s;
   }

   return NULL;
}

void
snw_component_insert(ice_component_head_t *head, snw_ice_component_t *item) {
   
   if ( head == NULL || item == NULL )
      return;

   LIST_INSERT_HEAD(head,item,list);
   return;
}


