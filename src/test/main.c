#include <stdlib.h>
#include <stdio.h>

#include "script.h"
#include "actor.h"


int main(int argc, char** argv) {
    script_t script = {
        NULL,
        NULL
    };

    actor_t player = {
        .health = 100,
        .armor = 0
    };


    actor_hurt_ctx_t* ctx1 = malloc(sizeof(actor_hurt_ctx_t));
    ctx1->source = NULL;
    ctx1->target = &player;
    ctx1->damage = 30;
    scr_append(&script, action_hurt, ctx1, 0);

    printf("%i\n", player.health);
    scr_advance(&script);
    printf("%i\n", player.health);
    scr_destroy(&script);
}