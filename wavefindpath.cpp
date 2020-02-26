extern "C" {
#include "sc_memory_headers.h"
#include "sc_helper.h"
#include "utils.h"
}

#include <stdio.h>
#include <unistd.h>
#include "model/Node.h"
#include "model/Edge.h"

using namespace std;

sc_memory_context *context;

sc_addr graph, rrel_arcs, rrel_nodes;
FILE *f;

Node* nodes;
Edge* edges;

void print_graph()
{
    printEl(context, graph, f);
    fprintf(f, "%d %d \n", graph.seg, graph.offset);
    fprintf(f, "\n----------------------\n");

    sc_iterator3 *it = sc_iterator3_f_a_a_new(context,
                       graph,
                       sc_type_arc_pos_const_perm,
                       0);

    while (SC_TRUE == sc_iterator3_next(it)) {
        sc_addr t_arc = sc_iterator3_value(it, 2);
        printEl(context, t_arc, f);
        fprintf(f, "\n");
    }
    sc_iterator3_free(it);
}

void run_test()
{;

    char gr[12] = "rootElement";
    //char gr[] = "graph";
    sc_helper_resolve_system_identifier(context, gr, &graph);
    print_graph();
}

int main()
{
    sc_memory_params params;
    sc_memory_params_clear(&params);
    params.repo_path = "/home/alexander/work/ostis/kb.bin";
    params.config_file = "/home/alexander/work/ostis/config/sc-web.ini";
    params.ext_path = "/home/alexander/work/ostis/sc-machine/bin/extensions";
    params.clear = SC_FALSE;
    sc_memory_initialize(&params);
    context = sc_memory_context_new(sc_access_lvl_make_max);
    f = fopen("/home/alexander/Desktop/KnowledgeDump.txt", "w");
    run_test();
    fclose(f);
    sc_memory_context_free(context);
    sc_memory_shutdown(SC_TRUE);

    return 0;
}
