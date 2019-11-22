//
// Created by Igor Duric on 11/22/19.
//

#ifndef PATH_FINDING_MAP_CREATOR_MASTER_H
#define PATH_FINDING_MAP_CREATOR_MASTER_H

#include "Map_Creator_Worker.h"

class Map_Creator : public Runnable {
public: // Meta
    static Map_Creator* Get_Instance();

private: // Meta
    static Map_Creator* instance;

    class Map_Creator_List_Element {
    public:
        explicit Map_Creator_List_Element(Map_Creator_Worker* payload, Map_Creator_List_Element* next = nullptr) : payload(payload), next(next) {};
        Map_Creator_Worker* payload;
        Map_Creator_List_Element* next;
    };
public:
    Map_Creator(const Map_Creator&) = delete;
    Map_Creator(Map_Creator&&) = delete;

    explicit Map_Creator();

    void Set_End() { end = true; };
    void Create_Map(int, int, float, int) noexcept(false);

    void* run() override;

    ~Map_Creator() override;
private:
    Map_Creator_List_Element* head = nullptr;
    Map_Creator_List_Element* tail = nullptr;

    sem_t mutex;
    sem_t amount;
    bool end = false;
};


#endif //PATH_FINDING_MAP_CREATOR_MASTER_H
