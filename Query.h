#ifndef QUERY_H
#define	QUERY_H

#ifdef	__cplusplus
extern "C" {
#endif
/*Function Prototypes {*/
void entrants_pos(const struct Event_Time *starttimes,  
        const struct Event_Entrant *startentrants, 
        const struct Event_Course *startcourses, 
        const struct Event_Node *startnodes);

char *returntype(const struct Event_Node *nodes, 
        int node);

int no_checkpoints(const struct Event_Node *nodes, 
        const struct Event_Course *courses, 
        char coursetype);

struct Current_Compet *noderized(const struct Event_Time *starttimes, 
        const struct Event_Entrant *startentrants, 
        const struct Event_Course *startcourses, 
        const struct Event_Node *startnodes);

void queary_entrant(int entrant, 
        const struct Event_Course *courses,
        const struct Current_Compet *compets);

int timeinmins(char* intime);

void comp_sort(const struct Current_Compet *in);
/*} end of function prototypes*/

/*hold a simplified struct of node information for easy access*/
struct Completed_Nodes
{
    int node_complete;
    char time_arived[6];
    char type[3];
    struct Completed_Nodes *next_node;
};
/*same with the completed nodes we keep a striped down competitor with all the relivent information for the uses we need*/
struct Current_Compet
{
    int Compet_Num;
    int cur_time;
    char Course;
    char time_started[6];
    const struct Completed_Nodes *nodes;
    struct Current_Compet *next_compet;
};
/*really cut down competitor for use in working out who has completed specific sections of the course*/
struct Min_Compet
{
    int num;
    struct Min_Compet *next;
};

#ifdef	__cplusplus
}
#endif

#endif	/* QUERY_H */

