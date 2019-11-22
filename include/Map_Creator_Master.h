//
// Created by Igor Duric on 11/22/19.
//

#ifndef PATH_FINDING_MAP_CREATOR_MASTER_H
#define PATH_FINDING_MAP_CREATOR_MASTER_H

#include "Map_Creator.h"

class Map_Creator_Master : public Runnable {
public: // Meta
    static Map_Creator_Master* Get_Instance();

private: // Meta
    static Map_Creator_Master* instance;

    class Map_Creator_List_Element {
    public:
        explicit Map_Creator_List_Element(Map_Creator* payload, Map_Creator_List_Element* next = nullptr) : payload(payload), next(next) {};
        Map_Creator* payload;
        Map_Creator_List_Element* next;
    };
public:
    Map_Creator_Master(const Map_Creator_Master&) = delete;
    Map_Creator_Master(Map_Creator_Master&&) = delete;

    explicit Map_Creator_Master();

    void Set_End() { end = true; };
    void Create_Map(int, int, float, int) noexcept(false);

    void* run() override;

    ~Map_Creator_Master() override;
private:
    Map_Creator_List_Element* head = nullptr;
    Map_Creator_List_Element* tail = nullptr;

    sem_t mutex;
    sem_t amount;
    bool end = false;
};


#endif //PATH_FINDING_MAP_CREATOR_MASTER_H
