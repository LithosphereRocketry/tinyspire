#ifndef SCRIPT_H
#define SCRIPT_H

typedef struct script_line script_line_t;

typedef enum {
    SCR_FLAGS_OWNS_CONTEXT = 1 << 0
} script_flags_t;

typedef struct {
    script_line_t* head; // owning
    script_line_t* tail;
} script_t;

typedef void (*script_action_t)(script_t*, void*);

// does not free memory associated with script itself, so that it can live on
// the stack
void scr_destroy(script_t* script);

// takes ownership of action
void scr_append(script_t* script, script_action_t action, void* context, script_flags_t flags);

// Performs the first action of the script and destroys it
void scr_advance(script_t* script);

#endif