#ifndef SOMETHING_COMMANDS_HPP_
#define SOMETHING_COMMANDS_HPP_

struct Game;

// TODO(#168): no command to set the values of the config variables
void command_quit(Game *game, String_View args);
void command_reset(Game *game, String_View args);
void command_spawn_enemy(Game *game, String_View args);
void command_close(Game *game, String_View args);

struct Command
{
    String_View name;
    void (*run)(Game *game, String_View args);
};

const Command commands[] = {
    {"quit"_sv, command_quit},
    {"reset"_sv, command_reset},
    {"restart"_sv, command_reset},
    {"spawn_enemy"_sv, command_spawn_enemy},
    {"close"_sv, command_close},
    {"claw"_sv, command_close},
};
const size_t commands_count = sizeof(commands) / sizeof(commands[0]);

#endif  // SOMETHING_COMMANDS_HPP_
