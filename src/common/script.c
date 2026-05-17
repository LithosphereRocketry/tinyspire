#include <stdlib.h>

#include "script.h"

struct script_line {
    script_action_t action;
    void* context; // owning
    struct script_line* tail; // owning
    script_flags_t flags;
};

void scr_destroy(script_t* script) {
    script_line_t* ptr = script->head;
    while(ptr) {
        script_line_t* tail = ptr->tail;
        if(ptr->flags & SCR_FLAGS_OWNS_CONTEXT) free(ptr->context);
        free(ptr);
        ptr = tail;
    }
    script->head = NULL;
    script->tail = NULL;
}

void scr_append(script_t* script, script_action_t action, void* context, script_flags_t flags) {
    script_line_t* line = malloc(sizeof(script_line_t));
    line->action = action;
    line->context = context;
    line->flags = flags;
    line->tail = NULL;

    if(script->tail) {
        script->tail->tail = line;
    } else {
        script->head = line;
    }
    script->tail = line;
}

void scr_advance(script_t* script) {
    script_line_t* line = script->head;
    if(script->tail == line) {
        script->head = NULL;
        script->tail = NULL;
    } else {
        script->head = line->tail;
    }
    line->action(script, line->context);
    if((line->flags & SCR_FLAGS_OWNS_CONTEXT) && line->context) free(line->context);
    free(line);
}