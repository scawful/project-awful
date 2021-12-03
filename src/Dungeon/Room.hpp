#ifndef Room_hpp
#define Room_hpp

class Room {
private:


public:
    int id, top, left, width, height;
    Room(int id, int top, int left, int width, int height);
    ~Room();
};

#endif