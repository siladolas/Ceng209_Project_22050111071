#ifndef ROOM_H
#define ROOM_H

typedef struct Room {
    int id;
    char description[256];
    struct Room *up, *down, *left, *right;
    int trap;
} Room;

Room *create_room(const char *description, int trap);
void connect_rooms(Room *from, Room *to, const char *direction);
void describe_room(Room *room);
void free_room(Room *room);

#endif
