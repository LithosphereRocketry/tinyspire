#ifndef ACTOR_H
#define ACTOR_H

#include "script.h"

typedef struct actor {
    int health;
    int armor;
    struct {
        int vulnerable;
    } base_effects;
} actor_t;

typedef struct {
    actor_t* source;
    actor_t* target;
    int damage;
} actor_hurt_ctx_t;
void action_hurt(script_t* script, void* ctx);

#endif