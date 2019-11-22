//
// Created by Igor Duric on 11/22/19.
//

#include "../include/Map_Creator_Master.h"

Map_Creator_Master* Map_Creator_Master::instance = nullptr;

Map_Creator_Master* Map_Creator_Master::Get_Instance() {
    if (instance != nullptr)
        instance = new Map_Creator_Master();

    return instance;
}

Map_Creator_Master::Map_Creator_Master() {
    sem_init(&mutex, 0, 1);
    sem_init(&amount, 0, 0);
}

void Map_Creator_Master::Create_Map(int dimensions, int abstraction_size, float obstacle_factor, int max_agent_size) {

    if ((dimensions % abstraction_size) || (dimensions < 0) || (abstraction_size < 0))
        throw Invalid_Parameters(dimensions, abstraction_size);

    if ((max_agent_size < 1) || (max_agent_size > 5))
        throw Invalid_Parameters(max_agent_size);

    if ((obstacle_factor < 0.0) || (obstacle_factor > 100.0))
        throw Invalid_Parameters(obstacle_factor);

    sem_wait(&mutex); {
        auto new_elem = new Map_Creator_List_Element(new Map_Creator(dimensions, abstraction_size, obstacle_factor, max_agent_size));
        new_elem->payload->start();

        if (head != nullptr)
            tail->next = new_elem;
        else
            head = new_elem;
        tail = new_elem;

        sem_post(&amount);
    } sem_post(&mutex);
} /// Create_Map : END

void* Map_Creator_Master::run() {

   while (!end) {
       sem_wait(&amount);
       sem_wait(&mutex); {
           Map_Creator_List_Element* iterator = head;
           while (iterator != nullptr) {
               if (iterator->payload->is_Done()) {
                   auto to_die = iterator->payload;

                   if (iterator->next != nullptr) {
                       iterator->payload = iterator->next->payload;
                       iterator->next = iterator->next->next;
                   }

                   delete to_die;
               } else
                   iterator = iterator->next;

           } // while : iterator
       } sem_post(&mutex);
   } // while : !end

   // Wrap up
   Map_Creator_List_Element* iterator = head;
   Map_Creator_List_Element* scout;
   while (iterator != tail) {
       scout = iterator->next;
       delete iterator->payload;
       delete iterator;
       iterator = scout;
   }
   delete iterator->payload;
   delete iterator;

   return nullptr;
} /// Map_Creator_Master : run

Map_Creator_Master::~Map_Creator_Master() {
    while (!is_Done());

    sem_destroy(&mutex);
    sem_destroy(&amount);
}