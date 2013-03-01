#include <stdlib.h>
#include "OutPut.h";
/*this class is dedicated to printing out relivent information*/
/*The method below prints out the main menu for the end user to see*/
void print_menu() 
{
    printf("1 : Load Files\n");
    printf("2 : Print Files\n");
    printf("3 : All Competitors Progress Competitors\n");
    printf("4 : Print Specific Competitors location\n");
    printf("5 : Print out the leaderboard\n");
    printf("6 : Add Time\n");
}
/*print out the events name and time*/
void print_event_name(struct Event_Name *e_name) 
{
    printf("%s\n", e_name->name);
    printf("%s\n", e_name->date);
    printf("%s\n", e_name->time);
}
/*print out nodes*/
void print_event_nodes(struct Event_Node *e_nodes) 
{
    /*we loop through all the nodes in a linked list*/
    while (1) 
    {
        e_nodes = e_nodes->next_node;
        /*when we hit the end we break the loop*/
        if (e_nodes == NULL)
            break;
        printf("Node Type : %s Node num : %i\n", e_nodes->node_type, e_nodes->node);
    }
}
/*print out all tracks*/
void print_event_tracks(struct Event_Track *e_tracks) 
{
    while (1) 
    {
        e_tracks = e_tracks->next_track;
        if (e_tracks == NULL)
            break;
        printf("Track no: %i | Start Node : %i | End Node : %i | Expected Time : %i \n", 
                e_tracks->number, e_tracks->start_node, e_tracks->end_node, e_tracks->expected_time);

    }
}
/*print out the event courses*/
void print_event_courses(struct Event_Course *e_courses) 
{
    while (1) 
    {
        e_courses = e_courses->next_course;
        if (e_courses == NULL)
            break;
        printf("Course Ident : %c | No of Nodes : %d | Nodes : ", 
                e_courses->ident, e_courses->node_num);
        /*getting the inner nodes*/
        struct Event_Course_Node *e_c_nodes;
        e_c_nodes = e_courses->head_node;
        while (1) 
        {
            e_c_nodes = e_c_nodes->next_node;
            if (e_c_nodes == NULL)
                break;
            printf("%d , ", e_c_nodes->node);
        }
        printf("\n");
    }
}
/*printing out the entrants of the event in same manner as mentioned in the above methods*/
void print_event_entrants(struct Event_Entrant *e_entrants) 
{
    while (1) 
    {
        e_entrants = e_entrants->next_entrant;
        if (e_entrants == NULL)
            break;
        printf("Entrant No : %i | Corse : %c | Name : %s\n", 
                e_entrants->comp_num, e_entrants->course, e_entrants->name);
    }
}
/*and again for the event times we print out the linked list by looping through it till we hit the end which is null*/
void print_event_times(struct Event_Time *e_times) 
{
    while (1) 
    {
        e_times = e_times->next_time;
        if (e_times == NULL)
            break;
        printf("Status : %c | Node no : %d | Entrant no : %d | Time : %s\n", 
                e_times->status, e_times->node, e_times->entrant_num, e_times->time);
    }
}