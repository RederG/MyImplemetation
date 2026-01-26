#include <stdio.h>
#include "../include/tool.h"
#include "../include/MyImplemetation/all_vectors.h"

int main(int argsi, char* argsc){
    Vector_controller(String, controller);
    Vector(String, names);

    controller.push("Optimus Prime", &names);
    controller.push("Bumblebee", &names);
    controller.push("Arcee", &names);
    controller.push("Elita One", &names);
    controller.push("Megatron", &names);
    controller.push("Starscream", &names);
    controller.push("Windblade", &names);
    controller.push("Primus", &names);
    controller.push("Megatronus Prime, the Fallen", &names);
    controller.push("Unicron", &names);

    unsigned int* index = nullptr;
    controller.search("Elita One", &index, &names);
    if(index != nullptr)
        printf("Elita One found at index %d\n\n", *index);
    else
        printf("Elita One not found\n\n");

    controller.fill(0, names.size, "Alpha Trion", &names);
    controller.get_next(nullptr);
    while(controller.get_next(&names))
        printf("%d => %s\n", controller.current_index(), controller.current_String());

    printf("\n");
    controller.resize(50, &names);
    controller.fill(15, 30, "Cybertron", &names);
    controller.get_next(nullptr);
    while(controller.get_next(&names))
        printf("%d => %s\n", controller.current_index(), controller.current_String());

    return 0;
}