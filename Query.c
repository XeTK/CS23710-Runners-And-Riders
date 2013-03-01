#include "EventStructs.h"
#include "Query.h"
#include <stdlib.h>

struct Current_Compet *noderized(const struct Event_Time *starttimes,  
        const struct Event_Entrant *startentrants, 
        const struct Event_Course *startcourses, 
        const struct Event_Node *startnodes) 
{
    struct Event_Time *e_times;
    struct Event_Entrant *e_entrants;
    struct Event_Course *e_courses;
    struct Current_Compet *cur_compet;
    const struct Current_Compet *start_compet;
    cur_compet = malloc(sizeof(struct Current_Compet));
    start_compet = cur_compet;
    e_times = starttimes;
    while (1)
    {
        e_times = e_times->next_time;
        if (e_times == NULL)
            break;
        e_entrants = startentrants;
        while (1) 
        {
            e_entrants = e_entrants->next_entrant;
            if (e_entrants == NULL)
                break;            
            if (e_times->entrant_num == e_entrants->comp_num) 
            {
                e_courses = startcourses;
                while (1) 
                {
                    e_courses = e_courses->next_course;
                    if (e_courses == NULL)
                        break;
                    if (e_courses->ident == e_entrants->course) 
                    {
                        struct Event_Course_Node *e_c_nodes;
                        e_c_nodes = e_courses->head_node;
                        while (1) 
                        {
                            e_c_nodes = e_c_nodes->next_node;
                            if (e_c_nodes == NULL)
                                break;
                            if (e_c_nodes->node == e_times->node) 
                            { 
                                cur_compet = start_compet;
                                while (1)
                                {
                                    if (cur_compet->Compet_Num == e_entrants->comp_num)
                                    {
                                        struct Completed_Nodes *cn;
                                        cn = cur_compet->nodes;
                                        while(1)
                                        {
                                            if (cn->next_node == NULL)
                                            {
                                                struct Completed_Nodes *cna; 
                                                cna = malloc(sizeof(struct Completed_Nodes));
                                                cna->node_complete = e_times->node;
                                                strcpy(cna->type,returntype(startnodes,e_times->node));
                                                strcpy(cna->time_arived, e_times->time);
                                                cn->next_node = cna;
                                                break;
                                            }
                                            cn = cn->next_node;
                                        }
                                        break;
                                    }
                                    if (cur_compet->next_compet == NULL)
                                    {
                                        struct Current_Compet *cp;
                                        cp = malloc(sizeof(struct Current_Compet));
                                        cp->Compet_Num = e_entrants->comp_num;
                                        cp->Course = e_entrants->course;
                                        strcpy(cp->time_started,e_times->time);
                                        struct Completed_Nodes *cn;
                                        cn = malloc(sizeof(struct Completed_Nodes));
                                        cn->node_complete = e_c_nodes->node;
                                        strcpy(cn->time_arived,e_times->time);
                                        cp->nodes = cn;
                                        cur_compet->next_compet =cp;
                                        
                                        break;
                                    }
                                    
                                    cur_compet = cur_compet->next_compet;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return start_compet;
}

char *returntype(const struct Event_Node *nodes, int node)
{
    struct Event_Node *current;
    current = nodes;
    while(1)
    {
        current = current->next_node;
        if (current == NULL)
        {
            break;
        }
        if (current->node == node)
        {
            return current->node_type;
        }
        
    }
    return NULL;
}

int no_checkpoints(const struct Event_Node *nodes, const struct Event_Course *courses, char coursetype)
{
    int total = 0;
    struct Event_Course *first_course;
    first_course = courses;
    while(1)
    {
        first_course = first_course->next_course;
        if (first_course == NULL)
            break;
        if (first_course->ident == coursetype)
        {
            struct Event_Course_Node *node;
            node = first_course->head_node;
            while(1)
            {
                node = node->next_node;
                if (node == NULL)
                    break;
                struct Event_Node *c_node;
                c_node = nodes;
                while(1)
                {
                    c_node = c_node->next_node;
                    if (c_node == NULL)
                        break;
                    if (c_node->node == node->node)
                    {
                        if (c_node->node_type[0] == 'C'||c_node->node_type[1] == 'P')
                        {
                            total++;
                            break;
                        }
                    }
                }
            }
        }
    }
    return total -1;
}

void queary_entrant(int entrant, const struct Event_Course *courses,const struct Current_Compet *compets)
{
    struct Current_Compet *temp_compet;
    temp_compet = compets;
    while(1)
    {
        temp_compet = temp_compet->next_compet;
        if(temp_compet == NULL)
            break;
        struct Event_Course *e_c;
        e_c = courses;
        while (1)
        {
            e_c = e_c->next_course;
            if (e_c == NULL)
                break; 
            if (e_c->ident == temp_compet->Course)
            {
                int valid = 0;
                int nl = -1;
                const struct Completed_Nodes *ln;
                struct Event_Node *e_n;
                e_n = e_c->head_node;
                while(1)
                {
                    e_n = e_n->next_node;
                    if (e_n == NULL)
                        break;
                    struct Completed_Nodes *c_ns;
                    c_ns = temp_compet->nodes;
                    while(1)
                    {
                        c_ns = c_ns->next_node;
                        if (c_ns->next_node == NULL||c_ns == NULL)
                        {
                            if (c_ns->node_complete == e_n->node)
                            {
                                valid = 1;
                                ln = c_ns;
                            }
                            break;
                        }
                    }
                    if (valid == 1)
                        nl++;
                }
                temp_compet->cur_time = timeinmins(ln->time_arived) - timeinmins(temp_compet->time_started);
                if (temp_compet->Compet_Num == entrant)
                    printf("Competitor %i started at %s and was last seen at %i at %s with %i left to complete. Duration %i Minutes\n\n",
                            temp_compet->Compet_Num,temp_compet->time_started,ln->node_complete,ln->time_arived,nl,temp_compet->cur_time);
            }
        }      
    }
}

void entrants_pos(const struct Event_Time *starttimes,  const struct Event_Entrant *startentrants, const struct Event_Course *startcourses, const struct Event_Node *startnodes)
{
    const struct Current_Compet *compet;
    compet = noderized(starttimes, startentrants,startcourses,startnodes);
    struct Current_Compet *temp;
    temp = compet;
    const struct Min_Compet *ff, *fnf, *ns;
    struct Min_Compet *finished, *notfinished, *notstarted;
    finished = malloc(sizeof(struct Min_Compet));
    notfinished = malloc(sizeof(struct Min_Compet));
    notstarted = malloc(sizeof(struct Min_Compet));
    ns = notstarted;
    ff = finished;
    fnf = notfinished;
    while(1)
    {
        temp = temp->next_compet;
        if (temp == NULL)
            break;
        struct Completed_Nodes *cn;
        int completed = 0;
        cn = temp->nodes;
        while (1)
        {
            cn = cn->next_node;
            if (cn == NULL)
                break;
            completed++;
        }
        struct Min_Compet *cm;
        cm = malloc(sizeof(struct Min_Compet));
        cm->num = temp->Compet_Num;
        if (completed == no_checkpoints(startnodes,startcourses,temp->Course))
        {
            
            finished->next = cm;
            finished = finished->next;
        }
        else
        {
            notfinished->next = cm;
            notfinished = notfinished->next;
        }
    }
    struct Event_Entrant *ee;
    ee = startentrants;
    while (1)
    {
        ee = ee->next_entrant;
        if (ee == NULL)
            break;
        temp = compet;
        while(1)
        {
            temp = temp->next_compet;
            if (temp == NULL)
            {
                notstarted = ns;
                while(1)
                {
                    
                    if (notstarted->next == NULL)
                    {
                        struct Min_Compet *tempms;
                        tempms = malloc(sizeof(struct Min_Compet));
                        tempms->num = ee->comp_num;
                        notstarted->next = tempms;
                        break;
                    }
                    notstarted = notstarted->next;
                }
                break;
            }
            if (ee->comp_num == temp->Compet_Num)
                break;
        }

    }
    finished = ff;
    int i =0;
    printf("Competitors : ");
    while(1)
    {
        finished = finished->next;
        if (finished == NULL)
            break;
        printf("%i ",finished->num);
        i++;
    }
    printf("Have Finished, Total of Finished Competitors : %i\n",i);
    i =0;
    notfinished = fnf;
    printf("Competitors : ");
    while(1)
    {
        notfinished = notfinished->next;
        if (notfinished == NULL)
            break;
        printf("%i ",notfinished->num);
        i++;
    }
    printf("Have NOT Finished, Total of not finished Competitors : %i\n",i);
    i = 0;
    notstarted = ns;
    printf("Have Not Started : ");
    while(1)
    {
        notstarted = notstarted->next;
        if (notstarted == NULL)
            break;
        printf("%i ",notstarted->num);
        i++;
    }
    printf(",Totaling : %i\n",i);
}

int timeinmins(char* intime)
{
    char buffer[2];
    int mins = 0;
    int i;
    for (i = 0; i < 2;i++)
        buffer[i] = intime[i]; 
    mins = atoi(buffer) * 60;
    for (i = 0; i < 2;i++)
        buffer[i] = intime[i +3];
    mins += atoi(buffer);
    return mins;
}

void comp_sort(const struct Current_Compet *in)
{
    int max =0, last = 32000, i = 0;
    struct Current_Compet *cc;
    cc = in;
    while(1)
    {
        cc = cc->next_compet;
        if (cc == NULL)
        {
            if (max == 0||max == last)
                break;
            cc = in;
            while(1)
            {
                if (cc == NULL)
                    break;
                if (cc->cur_time == max)
                {
                    i++;
                    printf("%i : Competitor %i with a time of %i Minute\n",i,cc->Compet_Num,cc->cur_time);
                }
                cc = cc->next_compet;
            }
            cc = in;
            last = max;
            max = 0;
        }
        if (cc->cur_time >= max&&cc->cur_time < last)
            max = cc->cur_time;
    }
}