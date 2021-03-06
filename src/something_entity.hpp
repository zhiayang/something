#ifndef SOMETHING_ENTITY_H_
#define SOMETHING_ENTITY_H_

enum class Jump_State
{
    No_Jump = 0,
    Prepare,
    Jump
};

enum class Entity_State
{
    Ded = 0,
    Alive,
    Poof
};

enum class Alive_State
{
    Idle = 0,
    Walking
};

const size_t JUMP_SAMPLES_CAPACITY = 2;


struct Entity
{
    enum Direction
    {
        Right,
        Left
    };

    Entity_State state;
    Alive_State alive_state;
    Jump_State jump_state;
    // NOTE: indicates that the entity jump_state has transitioned
    // from Jump_State::Prepare to Jump_State::Jump and the force that
    // drives the entity up has been applied. That flag is used by the
    // collision system to know when to not cancel out the vertical
    // velocity which can accidentally cancel out the whole jump.
    bool has_jumped;

    Rectf texbox_local;
    Rectf hitbox_local;
    Vec2f pos;
    Vec2f vel;
    float cooldown_weapon;
    Vec2f gun_dir;
    int lives;
    SDL_Color flash_color;
    float flash_alpha;
    Direction walking_direction;

    Frame_Animat idle;
    Frame_Animat walking;
    Rubber_Animat poof_animat;
    Rubber_Animat prepare_for_jump_animat;
    Compose_Rubber_Animat<2> jump_animat;

    Sample_S16 jump_samples[JUMP_SAMPLES_CAPACITY];
    Sample_S16 shoot_sample;

    void kill();

    inline Rectf texbox_world() const
    {
        Rectf dstrect = {
            texbox_local.x + pos.x,
            texbox_local.y + pos.y,
            texbox_local.w,
            texbox_local.h
        };
        return dstrect;
    }

    inline Rectf hitbox_world() const
    {
        Rectf hitbox = {
            hitbox_local.x + pos.x, hitbox_local.y + pos.y,
            hitbox_local.w, hitbox_local.h
        };
        return hitbox;
    }

    void render(SDL_Renderer *renderer, Camera camera,
                SDL_Color shade = {0, 0, 0, 0}) const;
    void render_debug(SDL_Renderer *renderer, Camera camera) const;
    void update(float dt, Sample_Mixer *mixer);
    void point_gun_at(Vec2f target);
    void jump();
    void flash(SDL_Color color);
    void move(Direction direction);
    void stop();
};

Entity player_entity(Vec2f pos);
Entity enemy_entity(Vec2f pos);

#endif  // SOMETHING_ENTITY_H_
