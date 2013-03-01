#include "EventStructs.h";
#include "FileReader.h";
#include <stdio.h>;
#include <stdlib.h>;

struct Event_Name *get_event_name(char txt_file[]) 
{
    FILE *file;
    file = fopen(txt_file, "rt");
    struct Event_Name *e_name;
    e_name = malloc(sizeof (struct Event_Name));
    char temp[80];
    fgets(temp, 80, file);
    sscanf(temp, "%80[0-9a-zA-Z ]s", e_name->name);
    fgets(temp, 80, file);
    sscanf(temp, "%80[0-9a-zA-Z ]s", e_name->date);
    fgets(temp, 80, file);
    sscanf(temp, "%6s", e_name->time);
    fclose(file);
    return e_name;
}

struct Event_Node *get_event_nodes(char txt_file[]) 
{
    FILE *file;
    char line[80];
    file = fopen(txt_file, "rt");
    struct Event_Node *e_node, *first_node, *previous_node;
    e_node = malloc(sizeof (struct Event_Node));
    first_node = e_node;
    while (fgets(line, 80, file) != NULL) 
    {
        previous_node = e_node;
        e_node = malloc(sizeof (struct Event_Node));
        sscanf(line, "%d %2s", &e_node->node, &e_node->node_type);
        previous_node->next_node = e_node;
    }
    fclose(file);
    return first_node;
}

struct Event_Track *get_event_tracks(char txt_file[]) 
{
    FILE *file;
    char line[80];
    file = fopen(txt_file, "rt");
    struct Event_Track *e_track, *first_track, *previous_track;
    e_track = malloc(sizeof (struct Event_Track));
    first_track = e_track;
    while (fgets(line, 80, file) != NULL) 
    {
        previous_track = e_track;
        e_track = malloc(sizeof (struct Event_Track));
        sscanf(line, "%d %d %d %d", &e_track->number, &e_track->start_node, &e_track->end_node, &e_track->expected_time);
        previous_track->next_track = e_track;
    }
    fclose(file);
    return first_track;
}

struct Event_Course *get_event_courses(char txt_file[])
{
    FILE *file;
    char line[80];
    file = fopen(txt_file, "rt");
    struct Event_Course *e_course, *first_course, *previous_course;
    e_course = malloc(sizeof(struct Event_Course));
    first_course = e_course;
    while(fgets(line, 80, file) != NULL)
    {
        previous_course = e_course;
        e_course = malloc(sizeof(struct Event_Course));
        sscanf(line, "%c %d", &e_course->ident, &e_course->node_num);
        
        struct Event_Course_Node *e_c_node, *first_c_node, *previous_c_node;
        e_c_node = malloc(sizeof (struct Event_Course_Node));
        first_c_node = e_c_node;
        int i , bufc, counts;
        char buffer[3];
        bufc = 0;
        counts = 0;
        for(i = 0; i < (sizeof(line) / sizeof(line[0]));i++)
        {
            if (line[i] == ' '||line[i] == NULL)
            {
                if (counts >= 2)
                {
                    previous_c_node = e_c_node;
                    e_c_node = malloc(sizeof (struct Event_Course_Node));
                    e_c_node->node = atoi(buffer);
                    previous_c_node->next_node = e_c_node;
                }
                bufc =0;
                counts++;
                buffer[0] = ' ';
                buffer[1] = ' ';
                buffer[2] = ' ';
                if (line[i] == NULL)
                    break;
            }
            else
            {
                buffer[bufc] = line[i];
                bufc++;
            }
        }
        e_course->head_node = first_c_node;
        previous_course->next_course = e_course;
    }
    fclose(file);
    return first_course;
}

struct Event_Entrant *get_event_entrants(char txt_file[]) 
{
    FILE *file;
    char line[80];
    file = fopen(txt_file, "rt");
    struct Event_Entrant *e_entrant, *first_entrant, *previous_entrant;
    e_entrant = malloc(sizeof (struct Event_Entrant));
    first_entrant = e_entrant;
    while (fgets(line, 80, file) != NULL) 
    {
        previous_entrant = e_entrant;
        e_entrant = malloc(sizeof (struct Event_Entrant));
        sscanf(line, "%d %c %50[0-9a-zA-Z ]s", &e_entrant->comp_num, &e_entrant->course, &e_entrant->name);
        previous_entrant->next_entrant = e_entrant;
    }
    fclose(file);
    return first_entrant;
}

struct Event_Time *get_event_times(char txt_file[]) 
{
    FILE *file;
    char line[80];
    file = fopen(txt_file, "rt");
    struct Event_Time *e_time, *first_time, *previous_time;
    e_time = malloc(sizeof (struct Event_Time));
    first_time = e_time;
    while (fgets(line, 80, file) != NULL) 
    {
        previous_time = e_time;
        e_time = malloc(sizeof(struct Event_Time));
        sscanf(line, "%c %d %d %5s", &e_time->status, &e_time->node, &e_time->entrant_num, &e_time->time);
        previous_time->next_time = e_time;
    }
    fclose(file);
    return first_time;
}
