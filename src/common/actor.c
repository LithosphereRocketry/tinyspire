#include "actor.h"

void action_swing(script_t* script, void* ctx) {
    actor_hurt_ctx_t* action = ctx;
    
}

void action_hurt(script_t* script, void* ctx) {
    actor_hurt_ctx_t* action = ctx;
    action->target->health -= action->damage;
}